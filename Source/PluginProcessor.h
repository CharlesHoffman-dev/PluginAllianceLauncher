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
#include "Core/LUFSAnalyzer.h"
#include "Utils/SettingsManager.h"

namespace PALauncher
{

// Forward declaration
class PluginHost;

// A/B slot selection for comparing two plugins
enum class ABSlot { A, B };

// ChainSlot represents a single slot in the plugin chain
// Each slot has its own A/B hosts for comparison
struct ChainSlot {
    PluginHost hostA;
    PluginHost hostB;
    ABSlot activeSlot = ABSlot::A;
    bool bypassed = false;

    // Auto-gain (LUFS matching)
    bool autoGainEnabled = false;
    LUFSAnalyzer lufsAnalyzer;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedGain { 1.0f };
    float currentCorrectionDb = 0.0f;  // For UI display

    PluginHost& getActiveHost() {
        return (activeSlot == ABSlot::A) ? hostA : hostB;
    }

    const PluginHost& getActiveHost() const {
        return (activeSlot == ABSlot::A) ? hostA : hostB;
    }

    bool hasPlugin() const;

    // Swap plugin contents and tied per-slot toggles with another slot. The LUFS
    // analyzer / smoothed gain / correction-dB stay with their slot; they're
    // running statistics that re-converge in a beat or two on whatever plugin
    // now sits there. Caller must hold the processor's pluginLock.
    void swap(ChainSlot& other) noexcept;
};

// Number of parameter slots to expose to the host DAW
static constexpr int kMaxParameters = 256;

// Maximum number of chain slots
static constexpr int kMaxChainSlots = 8;

// Custom parameter class that forwards to hosted plugin
class HostedPluginParameter : public juce::AudioProcessorParameter,
                               public juce::AudioProcessorParameter::Listener
{
public:
    HostedPluginParameter(int index);
    ~HostedPluginParameter() override;

    // Link to a hosted plugin's parameter
    void linkToParameter(juce::AudioProcessorParameter* param);
    void unlink();
    bool isLinked() const { return linkedParam != nullptr; }

    // Custom parameter naming (for chain slots)
    void setName(const juce::String& newName) { customName = newName; }

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
    bool isAutomatable() const override { return true; }
    bool isMetaParameter() const override { return false; }

    // AudioProcessorParameter::Listener - forward changes from hosted plugin to DAW
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;

private:
    int paramIndex;
    juce::AudioProcessorParameter* linkedParam = nullptr;
    float cachedValue = 0.0f;
    bool isForwardingChange = false;  // Prevent feedback loops
    juce::String customName;  // Custom name for chain slots (e.g., "Slot 0 - Gain")
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

    // Chain state for preset management
    std::unique_ptr<juce::XmlElement> getChainState() const;
    void setChainState(const juce::XmlElement& chainState);

    // Plugin hosting
    PluginDatabase& getPluginDatabase() { return pluginDatabase; }
    PluginScanner& getPluginScanner() { return pluginScanner; }
    SettingsManager& getSettingsManager() { return settingsManager; }

    // Chain slot management
    void setCurrentSelectedSlot(int index);
    int getCurrentSelectedSlot() const { return currentSelectedSlot; }

    // Per-slot A/B management
    void setSlotActiveAB(int slotIndex, ABSlot slot);
    ABSlot getSlotActiveAB(int slotIndex) const;

    // Bypass management
    void bypassSlot(int slotIndex, bool bypass);
    bool isSlotBypassed(int slotIndex) const;

    // Auto-gain (LUFS matching)
    void setSlotAutoGain(int slotIndex, bool enabled);
    bool isSlotAutoGainEnabled(int slotIndex) const;
    float getSlotCorrectionDb(int slotIndex) const;

    // Plugin loading/unloading
    bool loadPluginToSlot(int slotIndex, ABSlot abSlot, const juce::PluginDescription& desc);
    void unloadPluginFromSlot(int slotIndex);
    bool hasPluginInSlot(int slotIndex) const;

    // Chain management
    void removeAndCompactSlot(int slotIndex);
    void reorderSlots(int fromIndex, int toIndex);
    int getLoadedSlotCount() const;

    // Get direct access to chain slots
    ChainSlot& getChainSlot(int index);
    const ChainSlot& getChainSlot(int index) const;

    // Legacy A/B slot management (for backwards compatibility)
    void setActiveSlot(ABSlot slot) { setSlotActiveAB(currentSelectedSlot, slot); }
    ABSlot getActiveSlot() const { return getSlotActiveAB(currentSelectedSlot); }
    PluginHost& getActivePluginHost();
    PluginHost& getPluginHost(ABSlot slot);
    bool loadPluginToSlot(ABSlot slot, const juce::PluginDescription& desc);
    void unloadPluginFromSlot(ABSlot slot);
    bool hasPluginInSlot(ABSlot slot) const;

    // Legacy API - operates on active slot
    PluginHost& getPluginHost() { return getActivePluginHost(); }
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
    void updateParameterDistribution();

private:
    // Chain of plugin slots (each slot has its own A/B hosts)
    std::array<ChainSlot, kMaxChainSlots> chainSlots;
    int currentSelectedSlot = 0;  // Which slot is currently selected in UI

    PluginDatabase pluginDatabase;
    PluginScanner pluginScanner;
    SettingsManager settingsManager;

    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    juce::CriticalSection pluginLock;

    // Parameter slots for hosted plugin parameters.
    // Non-owning: the AudioProcessor base class owns these via parameterTree
    // (addParameter() wraps the pointer in a unique_ptr inside parameterTree).
    // Storing them here as raw pointers gives us O(1) lookup without double-ownership.
    juce::Array<HostedPluginParameter*> hostedParameters;
    bool isUpdatingParameters = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginAllianceLauncherProcessor)
};

} // namespace PALauncher
