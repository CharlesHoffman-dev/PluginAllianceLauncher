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
    pluginNameLabel.setFont(juce::Font(14.0f, juce::Font::bold));
    pluginNameLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    pluginNameLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(pluginNameLabel);

    unloadButton.setButtonText("Unload");
    unloadButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2a2a2a));
    unloadButton.setColour(juce::TextButton::textColourOffId, juce::Colour(0xfff9f9f9));
    unloadButton.setLookAndFeel(&hostedViewButtonLookAndFeel);
    unloadButton.onClick = [this]()
    {
        if (onUnloadClicked)
            onUnloadClicked();
    };
    addAndMakeVisible(unloadButton);

    editorViewport.setScrollBarsShown(true, true);
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

    // Header bar
    g.setColour(juce::Colour(0xff1a1a1a));
    g.fillRect(0, 0, getWidth(), 36);

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
    auto bounds = getLocalBounds();

    // Header bar
    auto headerBounds = bounds.removeFromTop(36);
    headerBounds.reduce(8, 6);

    unloadButton.setBounds(headerBounds.removeFromRight(70));
    headerBounds.removeFromRight(8);
    pluginNameLabel.setBounds(headerBounds);

    // Editor viewport
    editorViewport.setBounds(bounds);

    if (pluginEditor != nullptr)
    {
        // Center the editor if smaller than viewport, otherwise let viewport scroll
        auto editorSize = pluginEditor->getBounds();
        int x = juce::jmax(0, (editorViewport.getWidth() - editorSize.getWidth()) / 2);
        int y = juce::jmax(0, (editorViewport.getHeight() - editorSize.getHeight()) / 2);
        pluginEditor->setTopLeftPosition(x, y);
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

    // Update plugin name
    pluginNameLabel.setText("Currently Loaded: " + pluginHost->getLoadedPluginName(),
                            juce::dontSendNotification);

    // Create editor
    if (pluginHost->hasEditor())
    {
        pluginEditor.reset(pluginHost->createEditor());

        if (pluginEditor != nullptr)
        {
            pluginEditor->addComponentListener(this);

            // Set initial size
            auto constrainer = pluginEditor->getConstrainer();
            if (constrainer != nullptr)
            {
                pluginEditor->setSize(
                    juce::jlimit(constrainer->getMinimumWidth(), constrainer->getMaximumWidth(), pluginEditor->getWidth()),
                    juce::jlimit(constrainer->getMinimumHeight(), constrainer->getMaximumHeight(), pluginEditor->getHeight())
                );
            }

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
        pluginEditor->removeComponentListener(this);
        editorViewport.setViewedComponent(nullptr, false);
        pluginEditor.reset();
    }

    pluginNameLabel.setText("", juce::dontSendNotification);
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

void HostedPluginView::componentMovedOrResized(juce::Component& component, bool, bool wasResized)
{
    if (&component == pluginEditor.get() && wasResized)
    {
        // Plugin editor changed size, update viewport
        resized();
    }
}

} // namespace PALauncher
