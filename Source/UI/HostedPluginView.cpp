/*
  ==============================================================================
    HostedPluginView.cpp
    Plugin Alliance Launcher - Container for Hosted Plugin GUI Implementation
  ==============================================================================
*/

#include "HostedPluginView.h"
#include "Colors.h"

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
    editorViewport.setViewedComponent(&editorWrapper, false);
    addAndMakeVisible(editorViewport);

    setOpaque(true);
}

HostedPluginView::~HostedPluginView()
{
    hidePluginEditor();
}

void HostedPluginView::paint(juce::Graphics& g)
{
    g.fillAll(Colors::appBackground());

    if (pluginEditor == nullptr)
    {
        g.setColour(Colors::gridBackground().withAlpha(0.5f));
        g.setFont(juce::Font(14.0f));
        g.drawText("No plugin loaded.\nDouble-click a plugin to load it.",
                   getLocalBounds().reduced(20), juce::Justification::centred);
    }
}

void HostedPluginView::resized()
{
    // Viewport takes the full space
    editorViewport.setBounds(getLocalBounds());

    // Size the wrapper to at least cover the viewport so we have room to centre
    // the editor; if the editor is wider than the viewport, the wrapper grows so
    // the viewport scrolls.
    int viewW = editorViewport.getWidth();
    int viewH = editorViewport.getHeight();
    int editorW = pluginEditor != nullptr ? pluginEditor->getWidth()  : 0;
    int editorH = pluginEditor != nullptr ? pluginEditor->getHeight() : 0;
    int wrapperW = juce::jmax(viewW, editorW);
    int wrapperH = juce::jmax(viewH, editorH);
    editorWrapper.setSize(wrapperW, wrapperH);

    if (pluginEditor != nullptr)
    {
        int x = juce::jmax(0, (wrapperW - editorW) / 2);
        int y = juce::jmax(0, (wrapperH - editorH) / 2);
        pluginEditor->setBounds(x, y, editorW, editorH);
    }
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

            // Add the plugin editor inside the wrapper (not directly in the viewport)
            // so resized() can centre it horizontally.
            editorWrapper.addAndMakeVisible(pluginEditor.get());
            resized();
        }
    }

    repaint();
}

void HostedPluginView::hidePluginEditor()
{
    if (pluginEditor != nullptr)
    {
        editorWrapper.removeChildComponent(pluginEditor.get());
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
