/*
  ==============================================================================
    PluginHost.h
    Plugin Alliance Launcher - Plugin Hosting/Wrapping
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

class PluginHost
{
public:
    PluginHost();
    ~PluginHost();

    // Plugin loading
    bool loadPlugin(const juce::PluginDescription& description,
                    double sampleRate, int blockSize);
    void unloadPlugin();
    bool hasLoadedPlugin() const;

    // Plugin info
    juce::String getLoadedPluginName() const;
    const juce::PluginDescription* getLoadedPluginDescription() const;

    // Audio processing
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    double getTailLengthSeconds() const;

    // State management
    void getPluginState(juce::MemoryBlock& destData) const;
    void setPluginState(const juce::MemoryBlock& data);

    // Editor
    bool hasEditor() const;
    juce::AudioProcessorEditor* createEditor();

    // Parameter access
    juce::AudioPluginInstance* getLoadedPlugin() { return loadedPlugin.get(); }
    const juce::AudioPluginInstance* getLoadedPlugin() const { return loadedPlugin.get(); }

    // Sidechain support
    bool supportsSidechain() const { return hasSidechain; }

    // Bypass
    void setBypassed(bool shouldBypass) { bypassed = shouldBypass; }
    bool isBypassed() const { return bypassed; }

    // Move the loaded plugin (and its tied state) between hosts. Caller must hold
    // the processor's pluginLock so the audio thread is excluded for the swap.
    // Sample-rate / block-size and working buffers stay with the host since both
    // hosts are prepared in the same processor context.
    void swap(PluginHost& other) noexcept;

private:
    juce::AudioPluginFormatManager formatManager;
    std::unique_ptr<juce::AudioPluginInstance> loadedPlugin;
    juce::PluginDescription loadedDescription;

    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;
    bool isPrepared = false;
    bool hasSidechain = false;
    bool bypassed = false;

    // Temporary buffer for channel count adaptation
    juce::AudioBuffer<float> tempBuffer;

    mutable juce::CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginHost)
};

} // namespace PALauncher
