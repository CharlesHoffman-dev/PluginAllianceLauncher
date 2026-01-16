/*
  ==============================================================================
    PluginCard.cpp
    Plugin Alliance Launcher - Individual Plugin Display Card Implementation
  ==============================================================================
*/

#include "PluginCard.h"
#include "../Utils/PluginImageCache.h"

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

    // Set up Load button - white with black text, pointer cursor, no outline
    loadButton.setButtonText("Load");
    loadButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    loadButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
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
    juce::Colour bgColor = juce::Colours::white;
    if (selected)
        bgColor = juce::Colour(0xffe8f4fc);  // Light blue tint when selected
    else if (hovered)
        bgColor = juce::Colour(0xfffafafa);  // Slightly off-white on hover

    // Drop shadow effect
    g.setColour(juce::Colour(0x15000000));
    g.fillRoundedRectangle(bounds.translated(1.0f, 2.0f), 6.0f);

    g.setColour(bgColor);
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    if (selected)
    {
        g.setColour(juce::Colour(0xff0cbff2));
        g.drawRoundedRectangle(bounds, 6.0f, 2.0f);
    }
    else
    {
        // Subtle border for non-selected cards
        g.setColour(juce::Colour(0xffe0e0e0));
        g.drawRoundedRectangle(bounds, 6.0f, 1.0f);
    }

    // Content area
    auto contentBounds = getLocalBounds().reduced(10, 8);

    // Get brand name and display name (with brand removed)
    auto brandName = getBrandName(pluginInfo.description.name, pluginInfo.description.manufacturerName);
    auto displayName = getDisplayName(pluginInfo.description.name, brandName);

    // Brand name - gray text, in line with star
    g.setColour(juce::Colour(0xff666666));
    g.setFont(juce::Font(13.0f));
    auto brandBounds = contentBounds.removeFromTop(12);
    brandBounds.removeFromRight(26); // Space for favorite button
    g.drawText(brandName, brandBounds, juce::Justification::centredLeft, true);

    // Plugin name (with brand removed) - dark text, larger bold font
    g.setColour(juce::Colour(0xff1a1a1a));
    g.setFont(juce::Font(16.0f, juce::Font::bold));
    g.drawText(displayName, contentBounds.removeFromTop(24),
               juce::Justification::centredLeft, true);

    contentBounds.removeFromTop(8);

    // Plugin image - square area for better vertical thumbnail support
    auto imageBounds = contentBounds.removeFromTop(140);
    imageBoundsCache = imageBounds;  // Cache for button positioning

    if (pluginImage.isValid())
    {
        // Draw the image centered in the bounds
        float imageAspect = (float)pluginImage.getWidth() / (float)pluginImage.getHeight();
        float boundsAspect = (float)imageBounds.getWidth() / (float)imageBounds.getHeight();

        juce::Rectangle<float> drawBounds;
        if (imageAspect > boundsAspect)
        {
            // Image is wider - fit to width
            float drawWidth = (float)imageBounds.getWidth();
            float drawHeight = drawWidth / imageAspect;
            float y = imageBounds.getY() + (imageBounds.getHeight() - drawHeight) / 2.0f;
            drawBounds = juce::Rectangle<float>((float)imageBounds.getX(), y, drawWidth, drawHeight);
        }
        else
        {
            // Image is taller - fit to height
            float drawHeight = (float)imageBounds.getHeight();
            float drawWidth = drawHeight * imageAspect;
            float x = imageBounds.getX() + (imageBounds.getWidth() - drawWidth) / 2.0f;
            drawBounds = juce::Rectangle<float>(x, (float)imageBounds.getY(), drawWidth, drawHeight);
        }

        g.drawImage(pluginImage, drawBounds, juce::RectanglePlacement::centred);
    }
    else
    {
        // Draw placeholder - light gray
        g.setColour(juce::Colour(0xffeeeeee));
        g.fillRoundedRectangle(imageBounds.toFloat(), 4.0f);

        g.setColour(juce::Colour(0xff999999));
        g.setFont(juce::Font(12.0f));
        g.drawText("Loading...", imageBounds, juce::Justification::centred);
    }

    contentBounds.removeFromTop(14);

    // Category and Era tags row
    auto tagRow = contentBounds.removeFromTop(20);

    // Category tag
    juce::String categoryTag = getEffectCategoryName(pluginInfo.category);
    if (!categoryTag.isEmpty() && pluginInfo.category != EffectCategory::Unknown)
    {
        g.setColour(juce::Colour(0xff0cbff2).withAlpha(0.15f));
        auto tagBounds = tagRow.removeFromLeft(85);
        g.fillRoundedRectangle(tagBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff0099cc));
        g.setFont(juce::Font(12.0f));
        g.drawText(categoryTag, tagBounds, juce::Justification::centred);
    }

    // Era tag
    if (pluginInfo.era != Era::Era_Unknown)
    {
        tagRow.removeFromLeft(4);
        juce::String eraTag = getEraName(pluginInfo.era);

        g.setColour(juce::Colour(0xff888888).withAlpha(0.15f));
        auto eraBounds = tagRow.removeFromLeft(55);
        g.fillRoundedRectangle(eraBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff666666));
        g.setFont(juce::Font(12.0f));
        g.drawText(eraTag, eraBounds, juce::Justification::centred);
    }

    // Favorite heart - red when active, gray outline when inactive
    auto heartBounds = getLocalBounds().reduced(8).removeFromTop(24).removeFromRight(24);
    float cx = static_cast<float>(heartBounds.getCentreX());
    float cy = static_cast<float>(heartBounds.getCentreY()) + 1.0f;  // Shift down slightly
    float w = 11.0f;   // Half width
    float h = 13.0f;   // Height

    // Create heart path using bezier curves
    juce::Path heartPath;
    heartPath.startNewSubPath(cx, cy + h * 0.5f);  // Bottom point
    // Left side
    heartPath.cubicTo(cx - w * 0.8f, cy + h * 0.1f,    // Control point 1
                      cx - w, cy - h * 0.25f,           // Control point 2
                      cx - w * 0.5f, cy - h * 0.45f);   // Top of left lobe
    heartPath.cubicTo(cx - w * 0.1f, cy - h * 0.55f,   // Control point 1
                      cx, cy - h * 0.35f,               // Control point 2
                      cx, cy - h * 0.2f);               // Center dip
    // Right side
    heartPath.cubicTo(cx, cy - h * 0.35f,               // Control point 1
                      cx + w * 0.1f, cy - h * 0.55f,   // Control point 2
                      cx + w * 0.5f, cy - h * 0.45f);   // Top of right lobe
    heartPath.cubicTo(cx + w, cy - h * 0.25f,           // Control point 1
                      cx + w * 0.8f, cy + h * 0.1f,    // Control point 2
                      cx, cy + h * 0.5f);               // Back to bottom
    heartPath.closeSubPath();

    if (pluginInfo.isFavorite)
    {
        g.setColour(juce::Colour(0xffff4d6a));  // Pink/red color
        g.fillPath(heartPath);
    }
    else
    {
        g.setColour(juce::Colour(0xffcccccc));  // Light gray outline
        g.strokePath(heartPath, juce::PathStrokeType(1.5f));
    }

    // Darken entire card on hover or when loaded (drawn last, button is a child component so stays bright)
    if (hovered || isLoadedPlugin)
    {
        g.setColour(juce::Colour(0x40000000));  // Subtle semi-transparent black overlay
        g.fillRoundedRectangle(bounds, 6.0f);
    }
}

void PluginCard::resized()
{
    // Position the Load button in center of image area
    // Image area starts at y=58 (10 padding + 18 brand + 24 name + 8 spacing - 2 reduced)
    // and is 140px tall
    auto contentBounds = getLocalBounds().reduced(10, 8);
    contentBounds.removeFromTop(18);  // Brand name
    contentBounds.removeFromTop(24);  // Plugin name
    contentBounds.removeFromTop(8);   // Spacing
    auto imageBounds = contentBounds.removeFromTop(140);

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
    // Check if click is on the heart area (with expanded hit area for easier clicking)
    auto heartBounds = getLocalBounds().reduced(4).removeFromTop(28).removeFromRight(28);
    if (heartBounds.contains(e.getPosition()))
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
        loadButton.setButtonText(loaded ? "View" : "Load");
        loadButton.setVisible(loaded);  // Always show button when loaded
        repaint();
    }
}

} // namespace PALauncher
