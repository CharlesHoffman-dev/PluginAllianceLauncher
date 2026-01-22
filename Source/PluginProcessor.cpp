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
// ChainSlot implementation
//==============================================================================

bool ChainSlot::hasPlugin() const
{
    return hostA.hasLoadedPlugin() || hostB.hasLoadedPlugin();
}

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
    customName.clear();
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
    // If we have a custom name (e.g., from chain slots), use that
    if (customName.isNotEmpty())
        return customName.substring(0, maximumStringLength);

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
    // Prepare all chain slots
    for (auto& slot : chainSlots)
    {
        slot.hostA.prepareToPlay(sampleRate, samplesPerBlock);
        slot.hostB.prepareToPlay(sampleRate, samplesPerBlock);
    }
}

void PluginAllianceLauncherProcessor::releaseResources()
{
    juce::ScopedLock lock(pluginLock);
    // Release all chain slots
    for (auto& slot : chainSlots)
    {
        slot.hostA.releaseResources();
        slot.hostB.releaseResources();
    }
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
        // Route audio through all chain slots serially
        for (int i = 0; i < kMaxChainSlots; ++i)
        {
            // Skip bypassed slots
            if (chainSlots[i].bypassed)
                continue;

            auto& activeHost = chainSlots[i].getActiveHost();

            if (activeHost.hasLoadedPlugin())
            {
                // Forward playhead/transport info to hosted plugin
                // This is essential for plugins like MetricAB that have internal playback
                if (auto* hostedPlugin = activeHost.getLoadedPlugin())
                    hostedPlugin->setPlayHead(getPlayHead());

                activeHost.processBlock(buffer, midiMessages);
            }
        }
        pluginLock.exit();
    }
    // If lock not acquired or no plugin loaded, audio passes through unchanged
}

double PluginAllianceLauncherProcessor::getTailLengthSeconds() const
{
    juce::ScopedLock lock(pluginLock);

    // Return the maximum tail length from all active, non-bypassed slots
    double maxTail = 0.0;

    for (int i = 0; i < kMaxChainSlots; ++i)
    {
        if (chainSlots[i].bypassed)
            continue;

        const auto& activeHost = chainSlots[i].getActiveHost();

        if (activeHost.hasLoadedPlugin())
        {
            maxTail = juce::jmax(maxTail, activeHost.getTailLengthSeconds());
        }
    }

    return maxTail;
}

//==============================================================================
// Chain slot management methods
//==============================================================================

ChainSlot& PluginAllianceLauncherProcessor::getChainSlot(int index)
{
    jassert(index >= 0 && index < kMaxChainSlots);
    return chainSlots[index];
}

const ChainSlot& PluginAllianceLauncherProcessor::getChainSlot(int index) const
{
    jassert(index >= 0 && index < kMaxChainSlots);
    return chainSlots[index];
}

void PluginAllianceLauncherProcessor::setCurrentSelectedSlot(int index)
{
    jassert(index >= 0 && index < kMaxChainSlots);
    if (currentSelectedSlot != index)
    {
        currentSelectedSlot = index;
    }
}

void PluginAllianceLauncherProcessor::setSlotActiveAB(int slotIndex, ABSlot slot)
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);

    if (chainSlots[slotIndex].activeSlot == slot)
        return;

    chainSlots[slotIndex].activeSlot = slot;

    // Update parameter distribution if this affects the active hosts
    updateParameterDistribution();

    // Notify host that parameter info may have changed
    updateHostDisplay(ChangeDetails().withParameterInfoChanged(true));
}

ABSlot PluginAllianceLauncherProcessor::getSlotActiveAB(int slotIndex) const
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);
    return chainSlots[slotIndex].activeSlot;
}

void PluginAllianceLauncherProcessor::bypassSlot(int slotIndex, bool bypass)
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);
    chainSlots[slotIndex].bypassed = bypass;
}

bool PluginAllianceLauncherProcessor::isSlotBypassed(int slotIndex) const
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);
    return chainSlots[slotIndex].bypassed;
}

bool PluginAllianceLauncherProcessor::loadPluginToSlot(int slotIndex, ABSlot abSlot, const juce::PluginDescription& desc)
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);

    PluginHost& targetHost = (abSlot == ABSlot::A) ? chainSlots[slotIndex].hostA : chainSlots[slotIndex].hostB;

    // Unlink parameters before loading
    unlinkAllParameters();

    bool success = false;
    {
        juce::ScopedLock lock(pluginLock);
        success = targetHost.loadPlugin(desc, currentSampleRate, currentBlockSize);
    }

    if (success)
    {
        pluginDatabase.addToRecent(desc);

        // Update parameter distribution to include new plugin
        updateParameterDistribution();

        // Notify host that parameter info has changed
        updateHostDisplay(ChangeDetails().withParameterInfoChanged(true));
    }

    return success;
}

void PluginAllianceLauncherProcessor::unloadPluginFromSlot(int slotIndex)
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);

    // Unlink parameters first
    unlinkAllParameters();

    {
        juce::ScopedLock lock(pluginLock);
        chainSlots[slotIndex].hostA.unloadPlugin();
        chainSlots[slotIndex].hostB.unloadPlugin();
    }

    // Update parameter distribution
    updateParameterDistribution();

    // Notify host that parameter info has changed
    updateHostDisplay(ChangeDetails().withParameterInfoChanged(true));
}

bool PluginAllianceLauncherProcessor::hasPluginInSlot(int slotIndex) const
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);
    return chainSlots[slotIndex].hasPlugin();
}

void PluginAllianceLauncherProcessor::removeAndCompactSlot(int slotIndex)
{
    jassert(slotIndex >= 0 && slotIndex < kMaxChainSlots);

    // Simply unload both A and B hosts
    // The chain view will handle not showing empty slots
    unloadPluginFromSlot(slotIndex);

    // If the removed slot was selected, select the first available slot
    if (currentSelectedSlot == slotIndex)
    {
        // Find first slot with a plugin
        currentSelectedSlot = 0;
        for (int i = 0; i < kMaxChainSlots; ++i)
        {
            if (chainSlots[i].hasPlugin())
            {
                currentSelectedSlot = i;
                break;
            }
        }
    }

    // Update parameter distribution
    updateParameterDistribution();
}

void PluginAllianceLauncherProcessor::reorderSlots(int fromIndex, int toIndex)
{
    jassert(fromIndex >= 0 && fromIndex < kMaxChainSlots);
    jassert(toIndex >= 0 && toIndex < kMaxChainSlots);

    if (fromIndex == toIndex)
        return;

    // TODO: Implement reordering without using assignment operator
    // For now, reordering is disabled since PluginHost doesn't support assignment
    // This would require manually swapping plugin states and parameters
    DBG("Reordering not yet implemented");

    // Update parameter distribution after reorder
    // updateParameterDistribution();
}

int PluginAllianceLauncherProcessor::getLoadedSlotCount() const
{
    int count = 0;
    for (const auto& slot : chainSlots)
    {
        if (slot.hasPlugin())
            count++;
    }
    return count;
}

//==============================================================================
// Legacy A/B slot management methods (for backwards compatibility)
//==============================================================================

PluginHost& PluginAllianceLauncherProcessor::getActivePluginHost()
{
    return chainSlots[currentSelectedSlot].getActiveHost();
}

PluginHost& PluginAllianceLauncherProcessor::getPluginHost(ABSlot slot)
{
    return (slot == ABSlot::A) ? chainSlots[currentSelectedSlot].hostA : chainSlots[currentSelectedSlot].hostB;
}

bool PluginAllianceLauncherProcessor::loadPluginToSlot(ABSlot slot, const juce::PluginDescription& desc)
{
    return loadPluginToSlot(currentSelectedSlot, slot, desc);
}

void PluginAllianceLauncherProcessor::unloadPluginFromSlot(ABSlot slot)
{
    // This now only unloads the specified A or B host in the current slot
    PluginHost& targetHost = getPluginHost(slot);

    unlinkAllParameters();

    {
        juce::ScopedLock lock(pluginLock);
        targetHost.unloadPlugin();
    }

    updateParameterDistribution();
    updateHostDisplay(ChangeDetails().withParameterInfoChanged(true));
}

bool PluginAllianceLauncherProcessor::hasPluginInSlot(ABSlot slot) const
{
    const PluginHost& host = (slot == ABSlot::A) ? chainSlots[currentSelectedSlot].hostA : chainSlots[currentSelectedSlot].hostB;
    return host.hasLoadedPlugin();
}

// Legacy API - operates on current selected slot
bool PluginAllianceLauncherProcessor::loadPlugin(const juce::PluginDescription& desc)
{
    // Find next available slot
    for (int i = 0; i < kMaxChainSlots; ++i)
    {
        if (!chainSlots[i].hasPlugin())
            return loadPluginToSlot(i, chainSlots[i].activeSlot, desc);
    }
    return false;  // Chain is full
}

void PluginAllianceLauncherProcessor::unloadPlugin()
{
    unloadPluginFromSlot(currentSelectedSlot);
}

bool PluginAllianceLauncherProcessor::hasLoadedPlugin() const
{
    return hasPluginInSlot(chainSlots[currentSelectedSlot].activeSlot);
}

juce::String PluginAllianceLauncherProcessor::getLoadedPluginName() const
{
    const auto& host = chainSlots[currentSelectedSlot].getActiveHost();
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
    // Get chain state (includes all slots)
    auto chainState = getChainState();

    // Add UI state
    auto uiState = std::make_unique<juce::XmlElement>("UIState");
    // Add UI state attributes here
    chainState->addChildElement(uiState.release());

    copyXmlToBinary(*chainState, destData);
}

void PluginAllianceLauncherProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto xmlState = getXmlFromBinary(data, sizeInBytes);

    if (xmlState == nullptr)
        return;

    // Check if this is the new chain format
    if (xmlState->hasTagName("PALauncherChain"))
    {
        // New format - restore chain state directly
        setChainState(*xmlState);
    }
    else if (xmlState->hasTagName("PALauncherState"))
    {
        // Check if this has chain slots (newer old format) or single A/B (oldest format)
        if (xmlState->getChildByName("ChainSlot") != nullptr)
        {
            // Has chain slots - restore as chain
            setChainState(*xmlState);
        }
        else
        {
            // Old A/B format - migrate to slot 0
            auto restoreLegacySlot = [this](juce::XmlElement* pluginElement, ABSlot abSlot)
            {
                if (pluginElement == nullptr)
                    return;

                juce::PluginDescription desc;
                desc.name = pluginElement->getStringAttribute("name");
                desc.pluginFormatName = pluginElement->getStringAttribute("pluginFormatName");
                desc.fileOrIdentifier = pluginElement->getStringAttribute("fileOrIdentifier");
                desc.uniqueId = pluginElement->getStringAttribute("uid").getIntValue();

                // Load to slot 0
                if (loadPluginToSlot(0, abSlot, desc))
                {
                    // Restore plugin state
                    auto stateStr = pluginElement->getStringAttribute("state");
                    if (stateStr.isNotEmpty())
                    {
                        juce::MemoryBlock hostedState;
                        hostedState.fromBase64Encoding(stateStr);

                        PluginHost& host = (abSlot == ABSlot::A) ? chainSlots[0].hostA : chainSlots[0].hostB;
                        host.setPluginState(hostedState);
                    }
                }
            };

            // Migrate old SlotA/SlotB or LoadedPlugin to slot 0
            if (auto* slotAElement = xmlState->getChildByName("SlotA"))
                restoreLegacySlot(slotAElement, ABSlot::A);
            else if (auto* legacyElement = xmlState->getChildByName("LoadedPlugin"))
                restoreLegacySlot(legacyElement, ABSlot::A);

            if (auto* slotBElement = xmlState->getChildByName("SlotB"))
                restoreLegacySlot(slotBElement, ABSlot::B);

            // Restore active slot
            auto activeSlotStr = xmlState->getStringAttribute("activeSlot", "A");
            chainSlots[0].activeSlot = (activeSlotStr == "B") ? ABSlot::B : ABSlot::A;

            currentSelectedSlot = 0;

            // Update parameters
            updateParameterDistribution();
        }
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

void PluginAllianceLauncherProcessor::updateParameterDistribution()
{
    juce::ScopedLock lock(pluginLock);

    // First, unlink all parameters
    for (auto* param : hostedParameters)
        param->unlink();

    // Count how many slots have plugins loaded
    int numLoadedSlots = 0;
    for (const auto& slot : chainSlots)
    {
        if (slot.hasPlugin())
            numLoadedSlots++;
    }

    if (numLoadedSlots == 0)
        return;

    // Distribute parameters evenly across loaded slots
    int paramsPerSlot = kMaxParameters / numLoadedSlots;
    int paramIndex = 0;

    for (int slotIdx = 0; slotIdx < kMaxChainSlots && paramIndex < kMaxParameters; ++slotIdx)
    {
        if (!chainSlots[slotIdx].hasPlugin())
            continue;

        auto& activeHost = chainSlots[slotIdx].getActiveHost();
        auto* plugin = activeHost.getLoadedPlugin();

        if (plugin == nullptr)
            continue;

        auto& pluginParams = plugin->getParameters();

        int numToExpose = juce::jmin(paramsPerSlot, static_cast<int>(pluginParams.size()));

        for (int p = 0; p < numToExpose && paramIndex < kMaxParameters; ++p)
        {
            if (auto* param = pluginParams[p])
            {
                hostedParameters[paramIndex]->linkToParameter(param);
                // Set parameter name with slot prefix for DAW visibility
                hostedParameters[paramIndex]->setName("Slot " + juce::String(slotIdx) + " - " + param->getName(32));
                paramIndex++;
            }
        }
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

//==============================================================================
// Chain state management for presets
//==============================================================================

std::unique_ptr<juce::XmlElement> PluginAllianceLauncherProcessor::getChainState() const
{
    auto chainState = std::make_unique<juce::XmlElement>("PALauncherChain");
    chainState->setAttribute("currentSelectedSlot", currentSelectedSlot);

    // Helper lambda to save a plugin host's state
    auto saveHostState = [](const PluginHost& host, const juce::String& elementName) -> std::unique_ptr<juce::XmlElement>
    {
        if (!host.hasLoadedPlugin())
            return nullptr;

        auto hostState = std::make_unique<juce::XmlElement>(elementName);

        auto desc = host.getLoadedPluginDescription();
        if (desc != nullptr)
        {
            hostState->setAttribute("name", desc->name);
            hostState->setAttribute("pluginFormatName", desc->pluginFormatName);
            hostState->setAttribute("fileOrIdentifier", desc->fileOrIdentifier);
            hostState->setAttribute("uid", juce::String(desc->uniqueId));

            // Save hosted plugin state
            juce::MemoryBlock hostedState;
            host.getPluginState(hostedState);

            if (hostedState.getSize() > 0)
            {
                hostState->setAttribute("state", hostedState.toBase64Encoding());
            }
        }

        return hostState;
    };

    // Save all chain slots
    for (int i = 0; i < kMaxChainSlots; ++i)
    {
        if (!chainSlots[i].hasPlugin())
            continue;  // Skip empty slots

        auto slotElement = std::make_unique<juce::XmlElement>("ChainSlot");
        slotElement->setAttribute("index", i);
        slotElement->setAttribute("activeSlot", chainSlots[i].activeSlot == ABSlot::A ? "A" : "B");
        slotElement->setAttribute("bypassed", chainSlots[i].bypassed);

        // Save host A
        if (auto hostAState = saveHostState(chainSlots[i].hostA, "PluginA"))
            slotElement->addChildElement(hostAState.release());

        // Save host B
        if (auto hostBState = saveHostState(chainSlots[i].hostB, "PluginB"))
            slotElement->addChildElement(hostBState.release());

        chainState->addChildElement(slotElement.release());
    }

    return chainState;
}

void PluginAllianceLauncherProcessor::setChainState(const juce::XmlElement& chainState)
{
    if (!chainState.hasTagName("PALauncherChain") && !chainState.hasTagName("PALauncherState"))
        return;

    // Helper lambda to restore a plugin host from XML
    auto restoreHostState = [this](juce::XmlElement* hostElement, int slotIndex, ABSlot abSlot)
    {
        if (hostElement == nullptr)
            return false;

        juce::PluginDescription desc;
        desc.name = hostElement->getStringAttribute("name");
        desc.pluginFormatName = hostElement->getStringAttribute("pluginFormatName");
        desc.fileOrIdentifier = hostElement->getStringAttribute("fileOrIdentifier");
        desc.uniqueId = hostElement->getStringAttribute("uid").getIntValue();

        // Try to load the plugin
        if (loadPluginToSlot(slotIndex, abSlot, desc))
        {
            // Restore hosted plugin state
            auto stateStr = hostElement->getStringAttribute("state");
            if (stateStr.isNotEmpty())
            {
                juce::MemoryBlock hostedState;
                hostedState.fromBase64Encoding(stateStr);

                PluginHost& host = (abSlot == ABSlot::A) ? chainSlots[slotIndex].hostA : chainSlots[slotIndex].hostB;
                host.setPluginState(hostedState);
            }
            return true;
        }

        return false;
    };

    // Clear current chain
    for (int i = 0; i < kMaxChainSlots; ++i)
        unloadPluginFromSlot(i);

    // Restore chain slots
    for (auto* slotElement : chainState.getChildWithTagNameIterator("ChainSlot"))
    {
        int slotIndex = slotElement->getIntAttribute("index", 0);
        if (slotIndex < 0 || slotIndex >= kMaxChainSlots)
            continue;

        // Restore active slot (A or B)
        auto activeSlotStr = slotElement->getStringAttribute("activeSlot", "A");
        chainSlots[slotIndex].activeSlot = (activeSlotStr == "B") ? ABSlot::B : ABSlot::A;

        // Restore bypass state
        chainSlots[slotIndex].bypassed = slotElement->getBoolAttribute("bypassed", false);

        // Restore plugins
        if (auto* pluginAElement = slotElement->getChildByName("PluginA"))
            restoreHostState(pluginAElement, slotIndex, ABSlot::A);

        if (auto* pluginBElement = slotElement->getChildByName("PluginB"))
            restoreHostState(pluginBElement, slotIndex, ABSlot::B);
    }

    // Restore selected slot
    currentSelectedSlot = chainState.getIntAttribute("currentSelectedSlot", 0);
    if (currentSelectedSlot >= kMaxChainSlots)
        currentSelectedSlot = 0;

    // Update parameter distribution
    updateParameterDistribution();
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
