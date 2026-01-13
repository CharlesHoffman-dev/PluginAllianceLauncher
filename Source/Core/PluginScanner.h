/*
  ==============================================================================
    PluginScanner.h
    Plugin Alliance Launcher - Background Plugin Scanner
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Utils/PAIdentifier.h"

namespace PALauncher
{

class PluginScanner : public juce::ChangeBroadcaster,
                      private juce::Thread
{
public:
    PluginScanner();
    ~PluginScanner() override;

    // Start scanning for plugins (full scan or targeted)
    void startScan(bool fullScan = false);
    void stopScan();
    bool isScanning() const { return isThreadRunning(); }

    // Get scan progress (0.0 to 1.0)
    float getProgress() const { return scanProgress.load(); }

    // Get scanned plugins (after scan completes)
    juce::Array<juce::PluginDescription> getScannedPlugins() const;

    // Get scan status message
    juce::String getStatusMessage() const;

private:
    void run() override;
    void scanFormat(juce::AudioPluginFormat& format);
    void targetedScan();  // Fast scan - only PA-matching plugins
    void fullSystemScan(); // Slow scan - all plugins

    bool matchesPAPattern(const juce::String& filename) const;
    juce::StringArray getPAFilenamePatterns() const;

    juce::AudioPluginFormatManager formatManager;
    juce::KnownPluginList knownPlugins;
    PAIdentifier paIdentifier;

    juce::Array<juce::PluginDescription> scannedPlugins;
    std::atomic<float> scanProgress { 0.0f };
    juce::String statusMessage;
    bool performFullScan = false;

    mutable juce::CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginScanner)
};

} // namespace PALauncher
