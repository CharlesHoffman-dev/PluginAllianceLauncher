/*
  ==============================================================================
    HostedPluginView.cpp
    Plugin Alliance Launcher - Container for Hosted Plugin GUI Implementation
  ==============================================================================
*/

#include "HostedPluginView.h"

namespace PALauncher
{

// Custom LookAndFeel for buttons - no outline, 4px radius
class HostedViewButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f);
        auto baseColour = backgroundColour;

        if (isButtonDown)
            baseColour = baseColour.darker(0.2f);
        else if (isMouseOverButton)
            baseColour = baseColour.brighter(0.1f);

        g.setColour(baseColour);
        g.fillRoundedRectangle(bounds, 4.0f);
    }
};

static HostedViewButtonLookAndFeel hostedViewButtonLookAndFeel;

HostedPluginView::HostedPluginView()
{
    editorViewport.setScrollBarsShown(false, false);
    addAndMakeVisible(editorViewport);

    setOpaque(true);
}

HostedPluginView::~HostedPluginView()
{
    hidePluginEditor();
}

void HostedPluginView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff121212));

    if (pluginEditor == nullptr)
    {
        g.setColour(juce::Colour(0xfff9f9f9).withAlpha(0.5f));
        g.setFont(juce::Font(14.0f));
        g.drawText("No plugin loaded.\nDouble-click a plugin to load it.",
                   getLocalBounds().reduced(20), juce::Justification::centred);
    }
}

void HostedPluginView::resized()
{
    // Viewport takes the full space
    editorViewport.setBounds(getLocalBounds());
}

void HostedPluginView::setPluginHost(PluginHost* host)
{
    pluginHost = host;
    refreshEditor();
}

void HostedPluginView::showPluginEditor()
{
    hidePluginEditor();

    if (pluginHost == nullptr || !pluginHost->hasLoadedPlugin())
        return;

    // Create editor
    if (pluginHost->hasEditor())
    {
        pluginEditor.reset(pluginHost->createEditor());

        if (pluginEditor != nullptr)
        {
            // Set initial size based on constrainer
            auto constrainer = pluginEditor->getConstrainer();
            if (constrainer != nullptr)
            {
                pluginEditor->setSize(
                    juce::jlimit(constrainer->getMinimumWidth(), constrainer->getMaximumWidth(), pluginEditor->getWidth()),
                    juce::jlimit(constrainer->getMinimumHeight(), constrainer->getMaximumHeight(), pluginEditor->getHeight())
                );
            }

            // Cache the initial size to prevent auto-resizing
            cachedEditorWidth = pluginEditor->getWidth();
            cachedEditorHeight = pluginEditor->getHeight();

            editorViewport.setViewedComponent(pluginEditor.get(), false);
            resized();
        }
    }

    repaint();
}

void HostedPluginView::hidePluginEditor()
{
    if (pluginEditor != nullptr)
    {
        editorViewport.setViewedComponent(nullptr, false);
        pluginEditor.reset();
    }

    cachedEditorWidth = 0;
    cachedEditorHeight = 0;
    repaint();
}

void HostedPluginView::refreshEditor()
{
    if (pluginHost != nullptr && pluginHost->hasLoadedPlugin())
    {
        showPluginEditor();
    }
    else
    {
        hidePluginEditor();
    }
}

juce::Rectangle<int> HostedPluginView::getPluginEditorBounds() const
{
    if (pluginEditor != nullptr)
        return pluginEditor->getBounds();
    return {};
}

} // namespace PALauncher
