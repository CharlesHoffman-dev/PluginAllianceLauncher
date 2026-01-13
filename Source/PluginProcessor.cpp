/*
  ==============================================================================
    PluginProcessor.cpp
    Plugin Alliance Launcher - Main Audio Processor Implementation
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace PALauncher
{

PluginAllianceLauncherProcessor::PluginAllianceLauncherProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    // Initialize plugin database from saved state
    pluginDatabase.loadFromDisk();

    // Listen for scanner updates
    pluginScanner.addChangeListener(this);
}

PluginAllianceLauncherProcessor::~PluginAllianceLauncherProcessor()
{
    pluginScanner.removeChangeListener(this);
    unloadPlugin();
}

void PluginAllianceLauncherProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;

    juce::ScopedLock lock(pluginLock);
    pluginHost.prepareToPlay(sampleRate, samplesPerBlock);
}

void PluginAllianceLauncherProcessor::releaseResources()
{
    juce::ScopedLock lock(pluginLock);
    pluginHost.releaseResources();
}

bool PluginAllianceLauncherProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Support stereo in/out
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void PluginAllianceLauncherProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear unused output channels
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Process through hosted plugin if loaded
    juce::ScopedLock lock(pluginLock);

    if (pluginHost.hasLoadedPlugin())
    {
        pluginHost.processBlock(buffer, midiMessages);
    }
    // If no plugin loaded, audio passes through unchanged
}

double PluginAllianceLauncherProcessor::getTailLengthSeconds() const
{
    juce::ScopedLock lock(pluginLock);

    if (pluginHost.hasLoadedPlugin())
        return pluginHost.getTailLengthSeconds();

    return 0.0;
}

bool PluginAllianceLauncherProcessor::loadPlugin(const juce::PluginDescription& desc)
{
    juce::ScopedLock lock(pluginLock);

    bool success = pluginHost.loadPlugin(desc, currentSampleRate, currentBlockSize);

    if (success)
    {
        pluginDatabase.addToRecent(desc);
    }

    return success;
}

void PluginAllianceLauncherProcessor::unloadPlugin()
{
    juce::ScopedLock lock(pluginLock);
    pluginHost.unloadPlugin();
}

bool PluginAllianceLauncherProcessor::hasLoadedPlugin() const
{
    return pluginHost.hasLoadedPlugin();
}

juce::String PluginAllianceLauncherProcessor::getLoadedPluginName() const
{
    return pluginHost.getLoadedPluginName();
}

void PluginAllianceLauncherProcessor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &pluginScanner)
    {
        // Scanner finished, update database
        auto scannedPlugins = pluginScanner.getScannedPlugins();
        pluginDatabase.updatePlugins(scannedPlugins);
        pluginDatabase.saveToDisk();
    }
}

void PluginAllianceLauncherProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Create XML state
    auto state = std::make_unique<juce::XmlElement>("PALauncherState");

    // Save loaded plugin info
    if (pluginHost.hasLoadedPlugin())
    {
        auto pluginState = std::make_unique<juce::XmlElement>("LoadedPlugin");

        auto desc = pluginHost.getLoadedPluginDescription();
        if (desc != nullptr)
        {
            pluginState->setAttribute("name", desc->name);
            pluginState->setAttribute("pluginFormatName", desc->pluginFormatName);
            pluginState->setAttribute("fileOrIdentifier", desc->fileOrIdentifier);
            pluginState->setAttribute("uid", juce::String(desc->uniqueId));

            // Save hosted plugin state
            juce::MemoryBlock hostedState;
            pluginHost.getPluginState(hostedState);

            if (hostedState.getSize() > 0)
            {
                pluginState->setAttribute("state", hostedState.toBase64Encoding());
            }
        }

        state->addChildElement(pluginState.release());
    }

    // Save UI state
    auto uiState = std::make_unique<juce::XmlElement>("UIState");
    // Add UI state attributes here
    state->addChildElement(uiState.release());

    copyXmlToBinary(*state, destData);
}

void PluginAllianceLauncherProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto xmlState = getXmlFromBinary(data, sizeInBytes);

    if (xmlState != nullptr && xmlState->hasTagName("PALauncherState"))
    {
        // Restore loaded plugin
        if (auto* pluginElement = xmlState->getChildByName("LoadedPlugin"))
        {
            juce::PluginDescription desc;
            desc.name = pluginElement->getStringAttribute("name");
            desc.pluginFormatName = pluginElement->getStringAttribute("pluginFormatName");
            desc.fileOrIdentifier = pluginElement->getStringAttribute("fileOrIdentifier");
            desc.uniqueId = pluginElement->getStringAttribute("uid").getIntValue();

            // Try to load the plugin
            if (loadPlugin(desc))
            {
                // Restore hosted plugin state
                auto stateStr = pluginElement->getStringAttribute("state");
                if (stateStr.isNotEmpty())
                {
                    juce::MemoryBlock hostedState;
                    hostedState.fromBase64Encoding(stateStr);
                    pluginHost.setPluginState(hostedState);
                }
            }
        }
    }
}

juce::AudioProcessorEditor* PluginAllianceLauncherProcessor::createEditor()
{
    return new PluginAllianceLauncherEditor(*this);
}

} // namespace PALauncher

// This creates new instances of the plugin - required by JUCE
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PALauncher::PluginAllianceLauncherProcessor();
}
