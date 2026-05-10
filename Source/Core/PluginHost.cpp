/*
  ==============================================================================
    PluginHost.cpp
    Plugin Alliance Launcher - Plugin Hosting Implementation
  ==============================================================================
*/

#include "PluginHost.h"

namespace PALauncher
{

PluginHost::PluginHost()
{
    // Register all plugin formats
    formatManager.addDefaultFormats();
}

PluginHost::~PluginHost()
{
    unloadPlugin();
}

void PluginHost::swap(PluginHost& other) noexcept
{
    // formatManager, lock, sample-rate/block-size, and tempBuffer stay with the
    // host. Only the loaded plugin and its tied flags travel.
    std::swap(loadedPlugin, other.loadedPlugin);
    std::swap(loadedDescription, other.loadedDescription);
    std::swap(isPrepared, other.isPrepared);
    std::swap(hasSidechain, other.hasSidechain);
    std::swap(bypassed, other.bypassed);
}

bool PluginHost::loadPlugin(const juce::PluginDescription& description,
                            double sampleRate, int blockSize)
{
    juce::ScopedLock scopedLock(lock);

    // Unload current plugin if any
    if (loadedPlugin != nullptr)
    {
        if (isPrepared)
            loadedPlugin->releaseResources();
        loadedPlugin = nullptr;
    }

    // Create new plugin instance
    juce::String errorMessage;
    loadedPlugin = formatManager.createPluginInstance(
        description, sampleRate, blockSize, errorMessage);

    if (loadedPlugin == nullptr)
    {
        DBG("Failed to load plugin: " + errorMessage);
        return false;
    }

    // Store description
    loadedDescription = description;
    currentSampleRate = sampleRate;
    currentBlockSize = blockSize;

    // Try to configure bus layout - attempt stereo in/out first
    auto busesLayout = loadedPlugin->getBusesLayout();
    bool layoutChanged = false;

    // Configure main input bus to stereo if available
    if (loadedPlugin->getBusCount(true) > 0)
    {
        auto currentInput = busesLayout.getChannelSet(true, 0);
        if (currentInput != juce::AudioChannelSet::stereo())
        {
            busesLayout.getChannelSet(true, 0) = juce::AudioChannelSet::stereo();
            layoutChanged = true;
        }
    }

    // Configure sidechain input bus to stereo if available (bus index 1)
    if (loadedPlugin->getBusCount(true) > 1)
    {
        busesLayout.getChannelSet(true, 1) = juce::AudioChannelSet::stereo();
        hasSidechain = true;
        layoutChanged = true;
    }
    else
    {
        hasSidechain = false;
    }

    // Configure main output bus to stereo if available
    if (loadedPlugin->getBusCount(false) > 0)
    {
        auto currentOutput = busesLayout.getChannelSet(false, 0);
        if (currentOutput != juce::AudioChannelSet::stereo())
        {
            busesLayout.getChannelSet(false, 0) = juce::AudioChannelSet::stereo();
            layoutChanged = true;
        }
    }

    // Apply the bus layout if changed - if it fails, use the plugin's default
    if (layoutChanged)
    {
        if (!loadedPlugin->setBusesLayout(busesLayout))
        {
            DBG("Could not set stereo layout for " + description.name + ", using plugin's default");
            // Plugin doesn't support our layout, that's okay - use its default
        }
    }

    // Prepare the plugin
    loadedPlugin->prepareToPlay(sampleRate, blockSize);
    isPrepared = true;

    DBG("Successfully loaded plugin: " + description.name);
    return true;
}

void PluginHost::unloadPlugin()
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr)
    {
        if (isPrepared)
        {
            loadedPlugin->releaseResources();
            isPrepared = false;
        }
        loadedPlugin = nullptr;
    }

    loadedDescription = juce::PluginDescription();
}

bool PluginHost::hasLoadedPlugin() const
{
    return loadedPlugin != nullptr;
}

juce::String PluginHost::getLoadedPluginName() const
{
    if (loadedPlugin != nullptr)
        return loadedDescription.name;
    return {};
}

const juce::PluginDescription* PluginHost::getLoadedPluginDescription() const
{
    if (loadedPlugin != nullptr)
        return &loadedDescription;
    return nullptr;
}

void PluginHost::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ScopedLock scopedLock(lock);

    currentSampleRate = sampleRate;
    currentBlockSize = samplesPerBlock;

    if (loadedPlugin != nullptr)
    {
        if (isPrepared)
        {
            // Re-prepare with new settings
            loadedPlugin->releaseResources();
        }

        loadedPlugin->prepareToPlay(sampleRate, samplesPerBlock);
        isPrepared = true;
    }
}

void PluginHost::releaseResources()
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr && isPrepared)
    {
        loadedPlugin->releaseResources();
        isPrepared = false;
    }
}

void PluginHost::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin == nullptr || !isPrepared)
        return;

    // If bypassed, pass audio through unchanged
    if (bypassed)
        return;

    // Get the hosted plugin's channel requirements
    int pluginInputChannels = loadedPlugin->getTotalNumInputChannels();
    int pluginOutputChannels = loadedPlugin->getTotalNumOutputChannels();
    int bufferChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();

    // If channel counts match, process directly
    if (pluginInputChannels <= bufferChannels && pluginOutputChannels <= bufferChannels)
    {
        loadedPlugin->processBlock(buffer, midiMessages);
        return;
    }

    // Channel count mismatch - need to use a temporary buffer
    int maxChannels = juce::jmax(pluginInputChannels, pluginOutputChannels, bufferChannels);

    // Create or resize temporary buffer if needed
    if (tempBuffer.getNumChannels() < maxChannels || tempBuffer.getNumSamples() < numSamples)
    {
        tempBuffer.setSize(maxChannels, numSamples, false, false, true);
    }

    // Clear the temp buffer
    tempBuffer.clear();

    // Copy input channels from our buffer to temp buffer
    int channelsToCopy = juce::jmin(bufferChannels, pluginInputChannels);
    for (int ch = 0; ch < channelsToCopy; ++ch)
    {
        tempBuffer.copyFrom(ch, 0, buffer, ch, 0, numSamples);
    }

    // If plugin expects more input channels, duplicate the last channel or leave as silence
    // (Some plugins expect stereo pairs, so duplicate channel 1 to fill remaining)
    if (pluginInputChannels > bufferChannels && bufferChannels > 0)
    {
        int srcChannel = bufferChannels - 1;
        for (int ch = bufferChannels; ch < pluginInputChannels; ++ch)
        {
            tempBuffer.copyFrom(ch, 0, buffer, srcChannel, 0, numSamples);
        }
    }

    // Create a sub-buffer view with the correct channel count for the plugin
    juce::AudioBuffer<float> pluginBuffer(tempBuffer.getArrayOfWritePointers(), maxChannels, numSamples);

    // Process through the hosted plugin
    loadedPlugin->processBlock(pluginBuffer, midiMessages);

    // Copy output channels back to our buffer
    channelsToCopy = juce::jmin(bufferChannels, pluginOutputChannels);
    for (int ch = 0; ch < channelsToCopy; ++ch)
    {
        buffer.copyFrom(ch, 0, pluginBuffer, ch, 0, numSamples);
    }
}

double PluginHost::getTailLengthSeconds() const
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr)
        return loadedPlugin->getTailLengthSeconds();

    return 0.0;
}

void PluginHost::getPluginState(juce::MemoryBlock& destData) const
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr)
    {
        loadedPlugin->getStateInformation(destData);
    }
}

void PluginHost::setPluginState(const juce::MemoryBlock& data)
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr && data.getSize() > 0)
    {
        loadedPlugin->setStateInformation(data.getData(), (int)data.getSize());
    }
}

bool PluginHost::hasEditor() const
{
    if (loadedPlugin != nullptr)
        return loadedPlugin->hasEditor();
    return false;
}

juce::AudioProcessorEditor* PluginHost::createEditor()
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr && loadedPlugin->hasEditor())
        return loadedPlugin->createEditor();

    return nullptr;
}

} // namespace PALauncher
