/*
  ==============================================================================
    PluginProcessor.h
    Plugin Alliance Launcher - Main Audio Processor
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Core/PluginHost.h"
#include "Core/PluginDatabase.h"
#include "Core/PluginScanner.h"

namespace PALauncher
{

class PluginAllianceLauncherProcessor : public juce::AudioProcessor,
                                         public juce::ChangeListener
{
public:
    PluginAllianceLauncherProcessor();
    ~PluginAllianceLauncherProcessor() override;

    // AudioProcessor interface
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return true; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override;

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    // Plugin hosting
    PluginHost& getPluginHost() { return pluginHost; }
    PluginDatabase& getPluginDatabase() { return pluginDatabase; }
    PluginScanner& getPluginScanner() { return pluginScanner; }

    // Load a plugin by its description
    bool loadPlugin(const juce::PluginDescription& desc);
    void unloadPlugin();
    bool hasLoadedPlugin() const;
    juce::String getLoadedPluginName() const;

    // ChangeListener
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    PluginHost pluginHost;
    PluginDatabase pluginDatabase;
    PluginScanner pluginScanner;

    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    juce::CriticalSection pluginLock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginAllianceLauncherProcessor)
};

} // namespace PALauncher
