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

    if (loadedPlugin != nullptr && !isPrepared)
    {
        loadedPlugin->prepareToPlay(sampleRate, samplesPerBlock);
        isPrepared = true;
    }
    else if (loadedPlugin != nullptr && isPrepared)
    {
        // Re-prepare with new settings
        loadedPlugin->releaseResources();
        loadedPlugin->prepareToPlay(sampleRate, samplesPerBlock);
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

    if (loadedPlugin != nullptr && isPrepared)
    {
        loadedPlugin->processBlock(buffer, midiMessages);
    }
}

double PluginHost::getTailLengthSeconds() const
{
    juce::ScopedLock scopedLock(lock);

    if (loadedPlugin != nullptr)
        return loadedPlugin->getTailLengthSeconds();

    return 0.0;
}

void PluginHost::getPluginState(juce::MemoryBlock& destData)
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
