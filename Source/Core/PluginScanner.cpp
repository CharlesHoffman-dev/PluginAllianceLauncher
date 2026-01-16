/*
  ==============================================================================
    PluginScanner.cpp
    Plugin Alliance Launcher - Background Plugin Scanner Implementation
  ==============================================================================
*/

#include "PluginScanner.h"

namespace PALauncher
{

PluginScanner::PluginScanner()
    : Thread("PA Plugin Scanner")
{
    formatManager.addDefaultFormats();
}

PluginScanner::~PluginScanner()
{
    stopScan();
}

void PluginScanner::startScan(bool fullScan)
{
    if (!isThreadRunning())
    {
        {
            juce::ScopedLock scopedLock(lock);
            scannedPlugins.clear();
            scanProgress = 0.0f;
            statusMessage = "Starting scan...";
            performFullScan = fullScan;
        }
        startThread();
    }
}

void PluginScanner::stopScan()
{
    if (isThreadRunning())
    {
        signalThreadShouldExit();
        waitForThreadToExit(5000);
    }
}

juce::Array<juce::PluginDescription> PluginScanner::getScannedPlugins() const
{
    juce::ScopedLock scopedLock(lock);
    return scannedPlugins;
}

juce::String PluginScanner::getStatusMessage() const
{
    juce::ScopedLock scopedLock(lock);
    return statusMessage;
}

void PluginScanner::run()
{
    if (performFullScan)
    {
        fullSystemScan();
    }
    else
    {
        targetedScan();
    }

    if (!threadShouldExit())
    {
        {
            juce::ScopedLock scopedLock(lock);
            statusMessage = "Scan complete. Found " + juce::String(scannedPlugins.size()) + " Plugin Alliance plugins.";
        }
        scanProgress = 1.0f;

        // Notify listeners that scan is complete
        sendChangeMessage();
    }
}

juce::StringArray PluginScanner::getPAFilenamePatterns() const
{
    return juce::StringArray {
        // Brainworx patterns
        "bx_*",

        // Plugin Alliance branded
        "*Plugin Alliance*",

        // Partner brands
        "Ampeg*",
        "Diezel*",
        "ENGL*",
        "Friedman*",
        "Fuchs*",
        "Suhr*",
        "Chandler*",
        "Lindell*",
        "elysia*",
        "Elysia*",
        "SPL*",
        "Millennia*",
        "Shadow Hills*",
        "ShadowHills*",
        "Vertigo*",
        "Purple Audio*",
        "PurpleAudio*",
        "Dangerous*",
        "Black Box*",
        "BlackBox*",
        "Maag*",
        "AMEK*",
        "Bettermaker*",
        "Looptrotter*",
        "NEOLD*",
        "Unfiltered*",
        "ADPTR*",
        "Kirchhoff*",
        "HUM*",
        "HEARS*",
        "Noveltech*",
        "fiedler*",
        "Knif*",
        "TOMO*",
        "ACME*",
        "DS Audio*",
        "DSAudio*",
        "A-DA*",
        "ADA*",
        "THX*",
        "Gallien*",
        "GallienKrueger*",
        "Three-Body*",
        "ThreeBody*",
        "ProAudioDSP*",
        "MC77*",
        "Focusrite*SC*"
    };
}

bool PluginScanner::matchesPAPattern(const juce::String& filename) const
{
    auto patterns = getPAFilenamePatterns();
    auto filenameLower = filename.toLowerCase();

    for (const auto& pattern : patterns)
    {
        auto patternLower = pattern.toLowerCase();

        // Simple wildcard matching
        if (patternLower.startsWith("*") && patternLower.endsWith("*"))
        {
            // *text* - contains
            auto searchText = patternLower.substring(1, patternLower.length() - 1);
            if (filenameLower.contains(searchText))
                return true;
        }
        else if (patternLower.endsWith("*"))
        {
            // text* - starts with
            auto searchText = patternLower.substring(0, patternLower.length() - 1);
            if (filenameLower.startsWith(searchText))
                return true;
        }
        else if (patternLower.startsWith("*"))
        {
            // *text - ends with
            auto searchText = patternLower.substring(1);
            if (filenameLower.endsWith(searchText))
                return true;
        }
        else
        {
            // Exact match
            if (filenameLower == patternLower)
                return true;
        }
    }

    return false;
}

void PluginScanner::targetedScan()
{
    {
        juce::ScopedLock scopedLock(lock);
        statusMessage = "Searching for VST3 plugins...";
    }

    // Get VST3 search paths
    juce::FileSearchPath vst3Paths;

#if JUCE_WINDOWS
    vst3Paths.add(juce::File("C:\\Program Files\\Common Files\\VST3"));
    vst3Paths.add(juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
                  .getParentDirectory().getChildFile("Local\\Programs\\Common\\VST3"));
#elif JUCE_MAC
    vst3Paths.add(juce::File("/Library/Audio/Plug-Ins/VST3"));
    vst3Paths.add(juce::File::getSpecialLocation(juce::File::userHomeDirectory)
                  .getChildFile("Library/Audio/Plug-Ins/VST3"));
#endif

    // Find all .vst3 files (both single files AND directory bundles)
    juce::Array<juce::File> allVst3Files;

    for (int i = 0; i < vst3Paths.getNumPaths(); ++i)
    {
        auto searchDir = vst3Paths[i];
        if (!searchDir.isDirectory())
            continue;

        // Find .vst3 directories (bundles)
        auto vst3Dirs = searchDir.findChildFiles(juce::File::findDirectories, false, "*.vst3");
        allVst3Files.addArray(vst3Dirs);

        // Find .vst3 files (single-file plugins)
        auto vst3Files = searchDir.findChildFiles(juce::File::findFiles, false, "*.vst3");
        allVst3Files.addArray(vst3Files);
    }

    {
        juce::ScopedLock scopedLock(lock);
        statusMessage = "Found " + juce::String(allVst3Files.size()) + " VST3 files to scan...";
    }

    if (allVst3Files.isEmpty())
    {
        juce::ScopedLock scopedLock(lock);
        statusMessage = "No VST3 plugins found in search paths.";
        return;
    }

    // Find VST3 format
    juce::AudioPluginFormat* vst3Format = nullptr;
    for (int i = 0; i < formatManager.getNumFormats(); ++i)
    {
        if (formatManager.getFormat(i)->getName() == "VST3")
        {
            vst3Format = formatManager.getFormat(i);
            break;
        }
    }

    if (vst3Format == nullptr)
    {
        juce::ScopedLock scopedLock(lock);
        statusMessage = "ERROR: VST3 format not available!";
        return;
    }

    // Only scan plugins that match known PA filename patterns
    // This avoids scanning non-PA plugins which can freeze or hang
    juce::Array<juce::File> paPlugins;

    for (const auto& file : allVst3Files)
    {
        auto filename = file.getFileNameWithoutExtension();

        // IMPORTANT: Skip our own launcher plugin to avoid recursive loading crash
        if (filename.containsIgnoreCase("Plugin Alliance Launcher") ||
            filename.containsIgnoreCase("PALauncher") ||
            filename.containsIgnoreCase("PA Launcher"))
            continue;

        // Also skip Spacelab plugins (discontinued)
        if (filename.containsIgnoreCase("Spacelab"))
            continue;

        if (matchesPAPattern(filename))
            paPlugins.add(file);
    }

    {
        juce::ScopedLock scopedLock(lock);
        statusMessage = "Found " + juce::String(paPlugins.size()) + " Plugin Alliance plugins to scan...";
    }

    if (paPlugins.isEmpty())
    {
        juce::ScopedLock scopedLock(lock);
        statusMessage = "No Plugin Alliance plugins found.";
        return;
    }

    int scannedCount = 0;
    int totalCount = paPlugins.size();
    int foundCount = 0;

    for (const auto& pluginFile : paPlugins)
    {
        if (threadShouldExit())
            return;

        {
            juce::ScopedLock scopedLock(lock);
            statusMessage = "Scanning: " + pluginFile.getFileNameWithoutExtension();
            scanProgress = static_cast<float>(scannedCount) / static_cast<float>(totalCount);
        }

        juce::OwnedArray<juce::PluginDescription> foundPlugins;
        vst3Format->findAllTypesForFile(foundPlugins, pluginFile.getFullPathName());

        for (auto* desc : foundPlugins)
        {
            if (desc != nullptr && paIdentifier.isPluginAlliancePlugin(*desc))
            {
                juce::ScopedLock scopedLock(lock);
                scannedPlugins.add(*desc);
                foundCount++;
            }
        }

        scannedCount++;
    }
}

void PluginScanner::fullSystemScan()
{
    // Original full scan implementation
    auto numFormats = formatManager.getNumFormats();

    for (int i = 0; i < numFormats && !threadShouldExit(); ++i)
    {
        auto* format = formatManager.getFormat(i);
        if (format != nullptr)
        {
            {
                juce::ScopedLock scopedLock(lock);
                statusMessage = "Scanning " + format->getName() + " plugins...";
            }

            scanFormat(*format);

            scanProgress = (float)(i + 1) / (float)numFormats;
        }
    }
}

void PluginScanner::scanFormat(juce::AudioPluginFormat& format)
{
    // Get default search paths for this format
    auto searchPaths = format.getDefaultLocationsToSearch();

    juce::PluginDirectoryScanner scanner(
        knownPlugins,
        format,
        searchPaths,
        true,  // Recursive
        juce::File()  // Dead plugins file (not used)
    );

    juce::String pluginBeingScanned;

    while (!threadShouldExit())
    {
        if (!scanner.scanNextFile(true, pluginBeingScanned))
            break;

        {
            juce::ScopedLock scopedLock(lock);
            statusMessage = "Scanning: " + pluginBeingScanned;
        }
    }

    // Filter for Plugin Alliance plugins only
    auto allPlugins = knownPlugins.getTypes();

    for (const auto& desc : allPlugins)
    {
        if (paIdentifier.isPluginAlliancePlugin(desc))
        {
            juce::ScopedLock scopedLock(lock);
            scannedPlugins.add(desc);
        }
    }
}

} // namespace PALauncher
