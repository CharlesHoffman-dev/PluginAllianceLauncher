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

// Number of parameter slots to expose to the host DAW
static constexpr int kMaxParameters = 256;

// Custom parameter class that forwards to hosted plugin
class HostedPluginParameter : public juce::AudioProcessorParameter
{
public:
    HostedPluginParameter(int index);

    // Link to a hosted plugin's parameter
    void linkToParameter(juce::AudioProcessorParameter* param);
    void unlink();
    bool isLinked() const { return linkedParam != nullptr; }

    // AudioProcessorParameter interface
    float getValue() const override;
    void setValue(float newValue) override;
    float getDefaultValue() const override;
    juce::String getName(int maximumStringLength) const override;
    juce::String getLabel() const override;
    float getValueForText(const juce::String& text) const override;
    juce::String getText(float value, int maximumStringLength) const override;
    int getNumSteps() const override;
    bool isDiscrete() const override;
    bool isBoolean() const override;
    bool isAutomatable() const override { return isLinked(); }
    bool isMetaParameter() const override { return false; }

private:
    int paramIndex;
    juce::AudioProcessorParameter* linkedParam = nullptr;
    float cachedValue = 0.0f;
};

class PluginAllianceLauncherProcessor : public juce::AudioProcessor,
                                         public juce::ChangeListener,
                                         public juce::AudioProcessorParameter::Listener
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

    // AudioProcessorParameter::Listener
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;

    // Parameter management
    void syncParametersFromHostedPlugin();
    void unlinkAllParameters();

private:
    PluginHost pluginHost;
    PluginDatabase pluginDatabase;
    PluginScanner pluginScanner;

    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    juce::CriticalSection pluginLock;

    // Parameter slots for hosted plugin parameters
    juce::OwnedArray<HostedPluginParameter> hostedParameters;
    bool isUpdatingParameters = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginAllianceLauncherProcessor)
};

} // namespace PALauncher
