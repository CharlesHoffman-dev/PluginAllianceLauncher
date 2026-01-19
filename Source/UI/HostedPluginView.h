/*
  ==============================================================================
    HostedPluginView.h
    Plugin Alliance Launcher - Container for Hosted Plugin GUI
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Core/PluginHost.h"

namespace PALauncher
{

class HostedPluginView : public juce::Component
{
public:
    HostedPluginView();
    ~HostedPluginView() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Set the plugin host to get the editor from
    void setPluginHost(PluginHost* host);

    // Show/hide the plugin editor
    void showPluginEditor();
    void hidePluginEditor();
    bool isShowingEditor() const { return pluginEditor != nullptr; }

    // Refresh the editor (e.g., when plugin changes)
    void refreshEditor();

    // Get the preferred size of the hosted plugin
    juce::Rectangle<int> getPluginEditorBounds() const;

    // Callbacks
    std::function<void()> onUnloadClicked;

private:
    PluginHost* pluginHost = nullptr;
    std::unique_ptr<juce::AudioProcessorEditor> pluginEditor;

    juce::Label pluginNameLabel;
    juce::TextButton unloadButton;
    juce::TextButton bypassButton;
    juce::Viewport editorViewport;

    // Cache the initial editor size to prevent auto-resizing plugins from growing
    int cachedEditorWidth = 0;
    int cachedEditorHeight = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HostedPluginView)
};

} // namespace PALauncher
