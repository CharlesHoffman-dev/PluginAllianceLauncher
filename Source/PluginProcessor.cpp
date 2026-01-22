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

//==============================================================================
// HostedPluginParameter implementation
//==============================================================================

HostedPluginParameter::HostedPluginParameter(int index)
    : paramIndex(index)
{
}

HostedPluginParameter::~HostedPluginParameter()
{
    // Make sure we're removed as a listener
    if (linkedParam != nullptr)
        linkedParam->removeListener(this);
}

void HostedPluginParameter::linkToParameter(juce::AudioProcessorParameter* param)
{
    // Remove listener from old parameter
    if (linkedParam != nullptr)
        linkedParam->removeListener(this);

    linkedParam = param;

    if (linkedParam != nullptr)
    {
        cachedValue = linkedParam->getValue();
        // Add ourselves as listener to get notified of changes
        linkedParam->addListener(this);
    }
}

void HostedPluginParameter::unlink()
{
    // Remove listener before unlinking
    if (linkedParam != nullptr)
        linkedParam->removeListener(this);

    linkedParam = nullptr;
    cachedValue = 0.0f;
}

float HostedPluginParameter::getValue() const
{
    auto* param = linkedParam;  // Local copy for thread safety
    if (param != nullptr)
        return param->getValue();
    return cachedValue;
}

void HostedPluginParameter::setValue(float newValue)
{
    cachedValue = newValue;
    auto* param = linkedParam;  // Local copy for thread safety
    if (param != nullptr && !isForwardingChange)
    {
        // Prevent feedback: when DAW sets value, don't re-notify DAW
        isForwardingChange = true;
        param->setValue(newValue);
        isForwardingChange = false;
    }
}

float HostedPluginParameter::getDefaultValue() const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->getDefaultValue();
    return 0.0f;
}

juce::String HostedPluginParameter::getName(int maximumStringLength) const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->getName(maximumStringLength);
    return "Param " + juce::String(paramIndex + 1);
}

juce::String HostedPluginParameter::getLabel() const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->getLabel();
    return {};
}

float HostedPluginParameter::getValueForText(const juce::String& text) const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->getValueForText(text);
    return text.getFloatValue();
}

juce::String HostedPluginParameter::getText(float value, int maximumStringLength) const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->getText(value, maximumStringLength);
    return juce::String(value, 2);
}

int HostedPluginParameter::getNumSteps() const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->getNumSteps();
    return AudioProcessorParameter::getNumSteps();
}

bool HostedPluginParameter::isDiscrete() const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->isDiscrete();
    return false;
}

bool HostedPluginParameter::isBoolean() const
{
    auto* param = linkedParam;
    if (param != nullptr)
        return param->isBoolean();
    return false;
}

void HostedPluginParameter::parameterValueChanged(int /*parameterIndex*/, float newValue)
{
    // Called when the hosted plugin's parameter changes (e.g., user clicks in plugin GUI)
    // Forward this change to our listeners (including the DAW like Ableton)
    if (!isForwardingChange)
    {
        isForwardingChange = true;
        cachedValue = newValue;
        // This notifies Ableton that this parameter changed - essential for Configure mode
        sendValueChangedMessageToListeners(newValue);
        isForwardingChange = false;
    }
}

void HostedPluginParameter::parameterGestureChanged(int /*parameterIndex*/, bool gestureIsStarting)
{
    // Forward gesture changes to DAW (for automation recording)
    if (gestureIsStarting)
        beginChangeGesture();
    else
        endChangeGesture();
}

//==============================================================================
// PluginAllianceLauncherProcessor implementation
//==============================================================================

PluginAllianceLauncherProcessor::PluginAllianceLauncherProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withInput("Sidechain", juce::AudioChannelSet::stereo(), false)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    // Create parameter slots
    for (int i = 0; i < kMaxParameters; ++i)
    {
        auto* param = new HostedPluginParameter(i);
        hostedParameters.add(param);
        addParameter(param);
    }

    // Load all plugins from embedded database first
    pluginDatabase.loadAllPluginsFromDatabase();

    // Then load saved state (favorites, recent, etc.)
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
    pluginHostA.prepareToPlay(sampleRate, samplesPerBlock);
    pluginHostB.prepareToPlay(sampleRate, samplesPerBlock);
}

void PluginAllianceLauncherProcessor::releaseResources()
{
    juce::ScopedLock lock(pluginLock);
    pluginHostA.releaseResources();
    pluginHostB.releaseResources();
}

bool PluginAllianceLauncherProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // Main output must be stereo
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // Main input must be stereo
    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // Sidechain can be disabled (empty) or stereo
    auto sidechain = layouts.getChannelSet(true, 1);
    if (!sidechain.isDisabled() && sidechain != juce::AudioChannelSet::stereo())
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

    // Try to acquire lock without blocking - if we can't get it (plugin is loading),
    // just pass audio through unchanged to avoid glitches
    if (pluginLock.tryEnter())
    {
        // Route audio through the active slot only
        PluginHost& activeHost = (activeSlot == ABSlot::A) ? pluginHostA : pluginHostB;

        if (activeHost.hasLoadedPlugin())
        {
            // Forward playhead/transport info to hosted plugin
            // This is essential for plugins like MetricAB that have internal playback
            if (auto* hostedPlugin = activeHost.getLoadedPlugin())
                hostedPlugin->setPlayHead(getPlayHead());

            activeHost.processBlock(buffer, midiMessages);
        }
        pluginLock.exit();
    }
    // If lock not acquired or no plugin loaded, audio passes through unchanged
}

double PluginAllianceLauncherProcessor::getTailLengthSeconds() const
{
    juce::ScopedLock lock(pluginLock);

    const PluginHost& activeHost = (activeSlot == ABSlot::A) ? pluginHostA : pluginHostB;

    if (activeHost.hasLoadedPlugin())
        return activeHost.getTailLengthSeconds();

    return 0.0;
}

// A/B slot management methods
PluginHost& PluginAllianceLauncherProcessor::getActivePluginHost()
{
    return (activeSlot == ABSlot::A) ? pluginHostA : pluginHostB;
}

PluginHost& PluginAllianceLauncherProcessor::getPluginHost(ABSlot slot)
{
    return (slot == ABSlot::A) ? pluginHostA : pluginHostB;
}

void PluginAllianceLauncherProcessor::setActiveSlot(ABSlot slot)
{
    if (activeSlot == slot)
        return;

    // Unlink parameters from old slot
    for (auto* param : hostedParameters)
        param->unlink();

    activeSlot = slot;

    // Link parameters to new active slot
    PluginHost& newActiveHost = getActivePluginHost();
    if (newActiveHost.hasLoadedPlugin())
    {
        auto* loadedPlugin = newActiveHost.getLoadedPlugin();
        if (loadedPlugin != nullptr)
        {
            auto& params = loadedPlugin->getParameters();
            int numParams = juce::jmin(static_cast<int>(params.size()), kMaxParameters);

            for (int i = 0; i < numParams; ++i)
            {
                if (auto* param = params[i])
                    hostedParameters[i]->linkToParameter(param);
            }
        }
    }

    // Notify host that parameter info has changed
    updateHostDisplay(ChangeDetails()
        .withParameterInfoChanged(true));
}

bool PluginAllianceLauncherProcessor::loadPluginToSlot(ABSlot slot, const juce::PluginDescription& desc)
{
    PluginHost& targetHost = getPluginHost(slot);

    // If loading to active slot, unlink parameters first
    if (slot == activeSlot)
    {
        for (auto* param : hostedParameters)
            param->unlink();
    }

    bool success = false;
    {
        juce::ScopedLock lock(pluginLock);
        success = targetHost.loadPlugin(desc, currentSampleRate, currentBlockSize);
    }

    if (success)
    {
        pluginDatabase.addToRecent(desc);

        // If this is the active slot, sync parameters
        if (slot == activeSlot)
        {
            auto* loadedPlugin = targetHost.getLoadedPlugin();
            if (loadedPlugin != nullptr)
            {
                auto& params = loadedPlugin->getParameters();
                int numParams = juce::jmin(static_cast<int>(params.size()), kMaxParameters);

                for (int i = 0; i < numParams; ++i)
                {
                    if (auto* param = params[i])
                        hostedParameters[i]->linkToParameter(param);
                }

                // Notify host (e.g., Ableton) that parameter info has changed
                updateHostDisplay(ChangeDetails()
                    .withParameterInfoChanged(true));
            }
        }
    }

    return success;
}

void PluginAllianceLauncherProcessor::unloadPluginFromSlot(ABSlot slot)
{
    // If unloading from active slot, unlink parameters first
    if (slot == activeSlot)
    {
        for (auto* param : hostedParameters)
            param->unlink();
    }

    {
        juce::ScopedLock lock(pluginLock);
        getPluginHost(slot).unloadPlugin();
    }

    // If this was the active slot, notify host that parameter info has changed
    if (slot == activeSlot)
    {
        updateHostDisplay(ChangeDetails()
            .withParameterInfoChanged(true));
    }
}

bool PluginAllianceLauncherProcessor::hasPluginInSlot(ABSlot slot) const
{
    const PluginHost& host = (slot == ABSlot::A) ? pluginHostA : pluginHostB;
    return host.hasLoadedPlugin();
}

// Legacy API - operates on active slot
bool PluginAllianceLauncherProcessor::loadPlugin(const juce::PluginDescription& desc)
{
    return loadPluginToSlot(activeSlot, desc);
}

void PluginAllianceLauncherProcessor::unloadPlugin()
{
    unloadPluginFromSlot(activeSlot);
}

bool PluginAllianceLauncherProcessor::hasLoadedPlugin() const
{
    return hasPluginInSlot(activeSlot);
}

juce::String PluginAllianceLauncherProcessor::getLoadedPluginName() const
{
    const PluginHost& host = (activeSlot == ABSlot::A) ? pluginHostA : pluginHostB;
    return host.getLoadedPluginName();
}

void PluginAllianceLauncherProcessor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &pluginScanner)
    {
        // Scanner finished, update database
        auto scannedPlugins = pluginScanner.getScannedPlugins();
        pluginDatabase.updateInstalledPlugins(scannedPlugins);
        pluginDatabase.saveToDisk();
    }
}

void PluginAllianceLauncherProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Create XML state
    auto state = std::make_unique<juce::XmlElement>("PALauncherState");

    // Save active slot
    state->setAttribute("activeSlot", activeSlot == ABSlot::A ? "A" : "B");

    // Helper lambda to save a slot's state
    auto saveSlotState = [](PluginHost& host, const juce::String& elementName) -> std::unique_ptr<juce::XmlElement>
    {
        if (!host.hasLoadedPlugin())
            return nullptr;

        auto pluginState = std::make_unique<juce::XmlElement>(elementName);

        auto desc = host.getLoadedPluginDescription();
        if (desc != nullptr)
        {
            pluginState->setAttribute("name", desc->name);
            pluginState->setAttribute("pluginFormatName", desc->pluginFormatName);
            pluginState->setAttribute("fileOrIdentifier", desc->fileOrIdentifier);
            pluginState->setAttribute("uid", juce::String(desc->uniqueId));

            // Save hosted plugin state
            juce::MemoryBlock hostedState;
            host.getPluginState(hostedState);

            if (hostedState.getSize() > 0)
            {
                pluginState->setAttribute("state", hostedState.toBase64Encoding());
            }
        }

        return pluginState;
    };

    // Save slot A
    if (auto slotAState = saveSlotState(pluginHostA, "SlotA"))
        state->addChildElement(slotAState.release());

    // Save slot B
    if (auto slotBState = saveSlotState(pluginHostB, "SlotB"))
        state->addChildElement(slotBState.release());

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
        // Helper lambda to restore a slot from XML
        auto restoreSlotState = [this](juce::XmlElement* pluginElement, ABSlot slot, PluginHost& host)
        {
            if (pluginElement == nullptr)
                return;

            juce::PluginDescription desc;
            desc.name = pluginElement->getStringAttribute("name");
            desc.pluginFormatName = pluginElement->getStringAttribute("pluginFormatName");
            desc.fileOrIdentifier = pluginElement->getStringAttribute("fileOrIdentifier");
            desc.uniqueId = pluginElement->getStringAttribute("uid").getIntValue();

            // Try to load the plugin
            if (loadPluginToSlot(slot, desc))
            {
                // Restore hosted plugin state
                auto stateStr = pluginElement->getStringAttribute("state");
                if (stateStr.isNotEmpty())
                {
                    juce::MemoryBlock hostedState;
                    hostedState.fromBase64Encoding(stateStr);
                    host.setPluginState(hostedState);
                }
            }
        };

        // Restore slot A (check both old "LoadedPlugin" format and new "SlotA" format)
        if (auto* slotAElement = xmlState->getChildByName("SlotA"))
            restoreSlotState(slotAElement, ABSlot::A, pluginHostA);
        else if (auto* legacyElement = xmlState->getChildByName("LoadedPlugin"))
            restoreSlotState(legacyElement, ABSlot::A, pluginHostA);

        // Restore slot B
        if (auto* slotBElement = xmlState->getChildByName("SlotB"))
            restoreSlotState(slotBElement, ABSlot::B, pluginHostB);

        // Restore active slot
        auto activeSlotStr = xmlState->getStringAttribute("activeSlot", "A");
        ABSlot savedActiveSlot = (activeSlotStr == "B") ? ABSlot::B : ABSlot::A;

        // Only switch to B if B actually has a plugin loaded
        if (savedActiveSlot == ABSlot::B && hasPluginInSlot(ABSlot::B))
            setActiveSlot(ABSlot::B);
        else
            setActiveSlot(ABSlot::A);
    }
}

void PluginAllianceLauncherProcessor::syncParametersFromHostedPlugin()
{
    PluginHost& activeHost = getActivePluginHost();
    auto* loadedPlugin = activeHost.getLoadedPlugin();
    if (loadedPlugin == nullptr)
        return;

    juce::ScopedLock lock(pluginLock);

    auto& params = loadedPlugin->getParameters();
    int numParams = juce::jmin(static_cast<int>(params.size()), kMaxParameters);

    for (int i = 0; i < numParams; ++i)
    {
        if (auto* param = params[i])
        {
            hostedParameters[i]->linkToParameter(param);
        }
    }

    // Unlink remaining slots
    for (int i = numParams; i < kMaxParameters; ++i)
    {
        hostedParameters[i]->unlink();
    }
}

void PluginAllianceLauncherProcessor::unlinkAllParameters()
{
    juce::ScopedLock lock(pluginLock);

    // Unlink all parameter slots
    for (auto* param : hostedParameters)
    {
        param->unlink();
    }
}

void PluginAllianceLauncherProcessor::parameterValueChanged(int, float)
{
    // Not used - parameter forwarding is handled directly through linkToParameter
}

void PluginAllianceLauncherProcessor::parameterGestureChanged(int, bool)
{
    // Not used - gesture forwarding is handled directly through linkToParameter
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
