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

void HostedPluginParameter::linkToParameter(juce::AudioProcessorParameter* param)
{
    linkedParam = param;
    if (linkedParam != nullptr)
        cachedValue = linkedParam->getValue();
}

void HostedPluginParameter::unlink()
{
    linkedParam = nullptr;
    cachedValue = 0.0f;
}

float HostedPluginParameter::getValue() const
{
    if (linkedParam != nullptr)
        return linkedParam->getValue();
    return cachedValue;
}

void HostedPluginParameter::setValue(float newValue)
{
    cachedValue = newValue;
    if (linkedParam != nullptr)
        linkedParam->setValue(newValue);
}

float HostedPluginParameter::getDefaultValue() const
{
    if (linkedParam != nullptr)
        return linkedParam->getDefaultValue();
    return 0.0f;
}

juce::String HostedPluginParameter::getName(int maximumStringLength) const
{
    if (linkedParam != nullptr)
        return linkedParam->getName(maximumStringLength);
    return "Param " + juce::String(paramIndex + 1);
}

juce::String HostedPluginParameter::getLabel() const
{
    if (linkedParam != nullptr)
        return linkedParam->getLabel();
    return {};
}

float HostedPluginParameter::getValueForText(const juce::String& text) const
{
    if (linkedParam != nullptr)
        return linkedParam->getValueForText(text);
    return text.getFloatValue();
}

juce::String HostedPluginParameter::getText(float value, int maximumStringLength) const
{
    if (linkedParam != nullptr)
        return linkedParam->getText(value, maximumStringLength);
    return juce::String(value, 2);
}

int HostedPluginParameter::getNumSteps() const
{
    if (linkedParam != nullptr)
        return linkedParam->getNumSteps();
    return AudioProcessorParameter::getNumSteps();
}

bool HostedPluginParameter::isDiscrete() const
{
    if (linkedParam != nullptr)
        return linkedParam->isDiscrete();
    return false;
}

bool HostedPluginParameter::isBoolean() const
{
    if (linkedParam != nullptr)
        return linkedParam->isBoolean();
    return false;
}

//==============================================================================
// PluginAllianceLauncherProcessor implementation
//==============================================================================

PluginAllianceLauncherProcessor::PluginAllianceLauncherProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    // Create parameter slots
    for (int i = 0; i < kMaxParameters; ++i)
    {
        auto* param = new HostedPluginParameter(i);
        hostedParameters.add(param);
        addParameter(param);
    }

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

    // Unlink existing parameters first
    unlinkAllParameters();

    bool success = pluginHost.loadPlugin(desc, currentSampleRate, currentBlockSize);

    if (success)
    {
        pluginDatabase.addToRecent(desc);
        // Sync parameters from the newly loaded plugin
        syncParametersFromHostedPlugin();
    }

    return success;
}

void PluginAllianceLauncherProcessor::unloadPlugin()
{
    juce::ScopedLock lock(pluginLock);
    unlinkAllParameters();
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

void PluginAllianceLauncherProcessor::syncParametersFromHostedPlugin()
{
    auto* loadedPlugin = pluginHost.getLoadedPlugin();
    if (loadedPlugin == nullptr)
        return;

    isUpdatingParameters = true;

    auto& params = loadedPlugin->getParameters();
    int numParams = juce::jmin(static_cast<int>(params.size()), kMaxParameters);

    for (int i = 0; i < numParams; ++i)
    {
        if (auto* param = params[i])
        {
            hostedParameters[i]->linkToParameter(param);
            // Add ourselves as a listener to the hosted parameter
            param->addListener(this);
        }
    }

    // Unlink remaining slots
    for (int i = numParams; i < kMaxParameters; ++i)
    {
        hostedParameters[i]->unlink();
    }

    isUpdatingParameters = false;

    // Notify host that parameters have changed
    updateHostDisplay();
}

void PluginAllianceLauncherProcessor::unlinkAllParameters()
{
    auto* loadedPlugin = pluginHost.getLoadedPlugin();

    // Remove listeners from hosted plugin parameters
    if (loadedPlugin != nullptr)
    {
        auto& params = loadedPlugin->getParameters();
        for (auto* param : params)
        {
            if (param != nullptr)
                param->removeListener(this);
        }
    }

    // Unlink all parameter slots
    for (auto* param : hostedParameters)
    {
        param->unlink();
    }
}

void PluginAllianceLauncherProcessor::parameterValueChanged(int parameterIndex, float newValue)
{
    if (isUpdatingParameters)
        return;

    // Find which of our parameters maps to this hosted parameter index
    auto* loadedPlugin = pluginHost.getLoadedPlugin();
    if (loadedPlugin == nullptr)
        return;

    auto& params = loadedPlugin->getParameters();
    if (parameterIndex < 0 || parameterIndex >= static_cast<int>(params.size()))
        return;

    // The parameterIndex is the index in the hosted plugin's parameter list
    // which should match our hostedParameters index (since we link them 1:1)
    if (parameterIndex < kMaxParameters)
    {
        // Notify the host that our parameter value changed
        if (auto* ourParam = hostedParameters[parameterIndex])
        {
            ourParam->sendValueChangedMessageToListeners(newValue);
        }
    }
}

void PluginAllianceLauncherProcessor::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
{
    if (isUpdatingParameters)
        return;

    // Forward gesture changes to host
    if (parameterIndex >= 0 && parameterIndex < kMaxParameters)
    {
        if (auto* ourParam = hostedParameters[parameterIndex])
        {
            if (gestureIsStarting)
                ourParam->beginChangeGesture();
            else
                ourParam->endChangeGesture();
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
