/*
  ==============================================================================
    ChainSlotCard.h
    Plugin Alliance Launcher - Individual Chain Slot Display Card
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

namespace PALauncher
{

class ChainSlotCard : public juce::Component,
                      private juce::Timer
{
public:
    ChainSlotCard(int slotIndex);
    ~ChainSlotCard() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent&) override;
    void mouseExit(const juce::MouseEvent&) override;
    void mouseDown(const juce::MouseEvent&) override;
    void mouseDoubleClick(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;

    // Set the slot data to display
    void setSlotData(const ChainSlot& slot, int slotIndex, bool isSelected);
    int getSlotIndex() const { return slotIdx; }

    // Selection state
    void setSelected(bool shouldBeSelected);
    bool isSelected() const { return selected; }

    // Bypass state
    void setBypassed(bool shouldBeBypassed);
    bool isBypassed() const { return bypassed; }

    // A/B state
    void setABSlot(ABSlot slot);
    ABSlot getABSlot() const { return abSlot; }

    // Auto-gain toggle lives in the slot's portion of the unified header so
    // all four buttons (Power, A/B, AUTO, X) can be evenly distributed across
    // the module. The actual LUFS work still happens on the slot's processor
    // side; this card just owns the toggle UI.
    void setAutoGainEnabled(bool enabled);
    bool isAutoGainEnabled() const { return autoGainEnabled; }
    void setAutoGainAnalyzing(bool analyzing);

    // Update image from cache
    void updateImage();

    // Callbacks
    std::function<void(int slotIndex)> onSelected;
    std::function<void(int slotIndex)> onViewPlugin;  // Fired on double-click of the plugin image (when loaded)
    std::function<void(int slotIndex)> onRemove;
    std::function<void(int slotIndex, bool bypass)> onToggleBypass;
    std::function<void(int slotIndex, ABSlot newSlot)> onToggleAB;
    std::function<void(int slotIndex, bool enabled)> onAutoGainToggled;
    std::function<void(int slotIndex, juce::Point<int> dragPos)> onDragStart;
    std::function<void(int slotIndex, juce::Point<int> dragPos)> onDragMove;
    std::function<void(int slotIndex)> onDragEnd;

    // Card size - square thumbnail with toolbar
    static constexpr int cardWidth = 120;
    static constexpr int cardHeight = 128;  // Toolbar (24) + square image (98) + padding

private:
    void timerCallback() override;

    int slotIdx;
    bool selected = false;
    bool hovered = false;
    bool bypassed = false;
    bool autoGainEnabled = false;
    bool autoGainAnalyzing = false;
    bool autoFlashOn = false;
    ABSlot abSlot = ABSlot::A;
    juce::String pluginName;

    juce::Image pluginImage;
    juce::Rectangle<int> imageBoundsCache;

    // Button areas (small icons ~20×20px)
    juce::Rectangle<int> bypassButtonBounds;
    juce::Rectangle<int> abButtonBounds;
    juce::Rectangle<int> autoButtonBounds;
    juce::Rectangle<int> removeButtonBounds;

    bool isDragging = false;
    juce::Point<int> dragStartPos;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChainSlotCard)
};

} // namespace PALauncher
