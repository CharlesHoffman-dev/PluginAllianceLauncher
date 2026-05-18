/*
  ==============================================================================
    PluginCard.cpp
    Plugin Alliance Launcher - Individual Plugin Display Card Implementation
  ==============================================================================
*/

#include "PluginCard.h"
#include "../Utils/PluginImageCache.h"
#include "Colors.h"

namespace PALauncher
{

// Custom LookAndFeel for Load button - no outline, 4px radius, bold text
class CardButtonLookAndFeel : public juce::LookAndFeel_V4
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

    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                        bool /*isMouseOverButton*/, bool isButtonDown) override
    {
        auto font = juce::Font(button.getHeight() * 0.48f, juce::Font::bold);
        g.setFont(font);
        g.setColour(button.findColour(isButtonDown ? juce::TextButton::textColourOnId
                                                    : juce::TextButton::textColourOffId)
                        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

        auto bounds = button.getLocalBounds();
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, true);
    }
};

// Static instance shared by all cards
static CardButtonLookAndFeel cardButtonLookAndFeel;

PluginCard::PluginCard()
{
    // Prevent focus grabbing - don't steal focus from other components
    setWantsKeyboardFocus(false);
    setMouseClickGrabsKeyboardFocus(false);
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    // Cache paint output to an image - cards are static 99% of the time so
    // scroll / parent-repaint events become free blits instead of full
    // re-rasterizations. Buffer only regenerates on hover, select, image
    // load, or favourite-toggle (each of which calls repaint()).
    setBufferedToImage(true);

    // Set up Load button - white with black text, pointer cursor, no outline
    loadButton.setButtonText("Load");
    loadButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
    loadButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
    loadButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    loadButton.setLookAndFeel(&cardButtonLookAndFeel);
    loadButton.onClick = [this]()
    {
        if (onDoubleClick)
            onDoubleClick(pluginInfo);
    };
    loadButton.setVisible(false);
    addAndMakeVisible(loadButton);
}

void PluginCard::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);

    // Background - white with subtle shadow effect
    juce::Colour bgColor = Colors::cardBackground();
    if (selected)
        bgColor = Colors::cardBackgroundSelected();  // Light blue tint when selected
    else if (hovered)
        bgColor = Colors::cardBackgroundHover();  // Slightly off-white on hover

    // Drop shadow effect
    g.setColour(Colors::shadow());
    g.fillRoundedRectangle(bounds.translated(1.0f, 2.0f), 6.0f);

    g.setColour(bgColor);
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    if (selected)
    {
        // Use highlightAlt (teal in 70s, cyan in default) so the selected card
        // stays distinguishable from the orange "active / selection" accent.
        g.setColour(Colors::highlightAlt());
        g.drawRoundedRectangle(bounds, 6.0f, 2.0f);
    }
    else
    {
        // Subtle border for non-selected cards
        g.setColour(Colors::borderSubtle());
        g.drawRoundedRectangle(bounds, 6.0f, 1.0f);
    }

    // Content area - tighter padding
    auto contentBounds = getLocalBounds().reduced(8, 6);

    // Get brand name and display name (with brand removed)
    auto brandName = getBrandName(pluginInfo.description.name, pluginInfo.description.manufacturerName);
    auto displayName = getDisplayName(pluginInfo.description.name, brandName);

    // Add spacing above brand name to push content below the star
    contentBounds.removeFromTop(9);

    // Brand name - gray text
    g.setColour(Colors::textDisabled());
    g.setFont(juce::Font(13.0f));
    auto brandBounds = contentBounds.removeFromTop(14);
    g.drawText(brandName, brandBounds, juce::Justification::centredLeft, true);

    // Plugin name (with brand removed) - dark text
    g.setColour(Colors::textOnLight());
    g.setFont(juce::Font(16.0f, juce::Font::bold));
    g.drawText(displayName, contentBounds.removeFromTop(24),
               juce::Justification::centredLeft, true);

    contentBounds.removeFromTop(6);

    // Plugin image - square area for better vertical thumbnail support
    auto imageBounds = contentBounds.removeFromTop(125);
    imageBoundsCache = imageBounds;  // Cache for button positioning

    if (pluginImage.isValid())
    {
        // Draw the image centered, maintaining aspect ratio, not stretching
        g.drawImageWithin(pluginImage,
                          imageBounds.getX(), imageBounds.getY(),
                          imageBounds.getWidth(), imageBounds.getHeight(),
                          juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize);
    }
    else
    {
        // Draw placeholder - light gray
        g.setColour(Colors::placeholderImage());
        g.fillRoundedRectangle(imageBounds.toFloat(), 4.0f);

        g.setColour(Colors::textMuted());
        g.setFont(juce::Font(12.0f));
        g.drawText("Loading...", imageBounds, juce::Justification::centred);
    }

    contentBounds.removeFromTop(15);  // Spacing below thumbnail

    // Category and Era tags row
    auto tagRow = contentBounds.removeFromTop(18);

    // Category tag - check for instrument first, then effect category
    juce::String categoryTag;
    if (pluginInfo.isInstrument)
        categoryTag = "Synthesizer";
    else
        categoryTag = getEffectCategoryName(pluginInfo.category);

    if (!categoryTag.isEmpty() && (pluginInfo.isInstrument || pluginInfo.category != EffectCategory::Unknown))
    {
        g.setColour(Colors::accent().withAlpha(0.15f));
        auto tagBounds = tagRow.removeFromLeft(85);
        g.fillRoundedRectangle(tagBounds.toFloat(), 3.0f);

        g.setColour(Colors::accent().darker(0.2f));
        g.setFont(juce::Font(12.0f));
        g.drawText(categoryTag, tagBounds, juce::Justification::centred);
    }

    // Era tag
    if (pluginInfo.era != Era::Era_Unknown)
    {
        tagRow.removeFromLeft(4);
        juce::String eraTag = getEraName(pluginInfo.era);

        g.setColour(Colors::textMuted().withAlpha(0.15f));
        auto eraBounds = tagRow.removeFromLeft(55);
        g.fillRoundedRectangle(eraBounds.toFloat(), 3.0f);

        g.setColour(Colors::textDisabled());
        g.setFont(juce::Font(12.0f));
        g.drawText(eraTag, eraBounds, juce::Justification::centred);
    }

    // Favorite star - yellow when active, gray outline when inactive.
    // The star geometry is identical for every card, so build the path ONCE
    // (centred on the origin) at first paint and translate to the per-card
    // position via setUsingNonZeroWinding/AffineTransform on the fly.
    static const juce::Path baseStarPath = []
    {
        juce::Path p;
        constexpr float outerRadius = 10.0f;
        constexpr float innerRadius = 4.5f;
        for (int i = 0; i < 10; ++i)
        {
            const float radius = (i % 2 == 0) ? outerRadius : innerRadius;
            const float angle  = static_cast<float>(i)
                                  * juce::MathConstants<float>::pi / 5.0f
                                  - juce::MathConstants<float>::halfPi;
            const float x = radius * std::cos(angle);
            const float y = radius * std::sin(angle);
            if (i == 0) p.startNewSubPath(x, y);
            else        p.lineTo(x, y);
        }
        p.closeSubPath();
        return p;
    }();

    const auto starBounds = getLocalBounds().reduced(8).removeFromTop(24).removeFromRight(24);
    const float cx = static_cast<float>(starBounds.getCentreX());
    const float cy = static_cast<float>(starBounds.getCentreY());
    const auto starXform = juce::AffineTransform::translation(cx, cy);

    if (pluginInfo.isFavorite)
    {
        g.setColour(Colors::accentSecondary());  // Yellow/gold
        g.fillPath(baseStarPath, starXform);
    }
    else
    {
        g.setColour(Colors::textPlaceholder());  // Light grey outline
        g.strokePath(baseStarPath, juce::PathStrokeType(1.5f), starXform);
    }

    // Darken entire card on hover so the Load button reads better against the dimmed art.
    // (We intentionally do NOT dim "already loaded" plugins - the user must be free to load
    // the same plugin into another slot or the B host without the card looking unavailable.)
    if (hovered)
    {
        g.setColour(Colors::appBackground().withAlpha(0.25f));  // Subtle semi-transparent black overlay
        g.fillRoundedRectangle(bounds, 6.0f);
    }
}

void PluginCard::resized()
{
    // Position the Load button in center of image area
    auto contentBounds = getLocalBounds().reduced(8, 6);
    contentBounds.removeFromTop(9);   // Spacing above brand
    contentBounds.removeFromTop(14);  // Brand name
    contentBounds.removeFromTop(24);  // Plugin name
    contentBounds.removeFromTop(6);   // Spacing
    auto imageBounds = contentBounds.removeFromTop(125);

    // Center a larger button in the image area
    int buttonWidth = 100;
    int buttonHeight = 36;
    int buttonX = imageBounds.getCentreX() - buttonWidth / 2;
    int buttonY = imageBounds.getCentreY() - buttonHeight / 2;
    loadButton.setBounds(buttonX, buttonY, buttonWidth, buttonHeight);
}

void PluginCard::mouseEnter(const juce::MouseEvent&)
{
    hovered = true;
    loadButton.setVisible(true);
    repaint();
}

void PluginCard::mouseExit(const juce::MouseEvent& e)
{
    // Only hide if mouse actually left the card (not just moved to a child component like the button)
    if (!getLocalBounds().contains(e.getPosition()))
    {
        hovered = false;
        loadButton.setVisible(false);
        repaint();
    }
}

void PluginCard::mouseDown(const juce::MouseEvent& e)
{
    // Check if click is on the star area (with expanded hit area for easier clicking)
    auto starBounds = getLocalBounds().reduced(4).removeFromTop(28).removeFromRight(28);
    if (starBounds.contains(e.getPosition()))
    {
        // Toggle favorite
        if (onFavoriteToggle)
            onFavoriteToggle(pluginInfo, !pluginInfo.isFavorite);
        return;
    }

    if (onSelected)
        onSelected(pluginInfo);
}

void PluginCard::mouseDoubleClick(const juce::MouseEvent&)
{
    if (onDoubleClick)
        onDoubleClick(pluginInfo);
}

void PluginCard::setPluginInfo(const PluginInfo& info)
{
    pluginInfo = info;

    // Reset hover and loaded state when card is assigned new plugin
    hovered = false;
    isLoadedPlugin = false;
    loadButton.setButtonText("Load");
    loadButton.setVisible(false);

    // Try to get image from cache
    updateImage();

    // Request image download if not cached
    PluginImageCache::getInstance().requestImage(pluginInfo.description.name);

    repaint();
}

void PluginCard::updateImage()
{
    pluginImage = PluginImageCache::getInstance().getImage(pluginInfo.description.name);
    repaint();
}

void PluginCard::setSelected(bool sel)
{
    if (selected != sel)
    {
        selected = sel;
        repaint();
    }
}

void PluginCard::setLoaded(bool loaded)
{
    if (isLoadedPlugin != loaded)
    {
        isLoadedPlugin = loaded;
        repaint();
    }
}

} // namespace PALauncher
