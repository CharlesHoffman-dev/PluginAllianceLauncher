/*
  ==============================================================================
    PluginChainView.h
    Plugin Alliance Launcher - Horizontal Plugin Chain View
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ChainSlotCard.h"
#include "ChainMeterCard.h"
#include "../PluginProcessor.h"

namespace PALauncher
{

class PluginChainView : public juce::Component
{
public:
    PluginChainView();
    ~PluginChainView() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Update chain state from processor
    void setChainState(PluginAllianceLauncherProcessor& processor);

    // Update individual slot's A/B button state
    void updateSlotABButton(int slotIndex, ABSlot newSlot);

    // Update meter levels (called from processor during audio processing)
    void updateMeterLevels(int meterIndex, float leftPeak, float rightPeak);

    // Update auto-gain display state
    void updateAutoGainState(int meterIndex, bool enabled, float correctionDb);

    // Callbacks
    std::function<void(int slotIndex)> onSlotSelected;
    std::function<void(int slotIndex)> onSlotViewPlugin;  // Double-click on slot image
    std::function<void(int slotIndex)> onRemoveSlot;
    std::function<void()> onAddSlot;
    std::function<void(int slotIndex, ABSlot newSlot)> onToggleAB;
    std::function<void(int fromIndex, int toIndex)> onSlotReorder;
    std::function<void(int meterIndex, float newGain)> onMeterGainChanged;
    std::function<void(int meterIndex, bool enabled)> onAutoGainToggled;

    // Chain view dimensions
    static constexpr int viewHeight = 280;
    static constexpr int minWidth = 1200;

private:
    void handleSlotSelected(int slotIndex);
    void handleRemoveSlot(int slotIndex);
    void handleToggleBypass(int slotIndex, bool bypass);
    void handleToggleAB(int slotIndex, ABSlot newSlot);
    void handleDragStart(int slotIndex, juce::Point<int> dragPos);
    void handleDragMove(int slotIndex, juce::Point<int> dragPos);
    void handleDragEnd(int slotIndex);
    void handleMeterGainChanged(int meterIndex, float newGain);
    void handleAutoGainToggled(int meterIndex, bool enabled);

    int calculateDropIndex(juce::Point<int> screenPos);

    juce::OwnedArray<ChainSlotCard> slotCards;
    juce::OwnedArray<ChainMeterCard> meterCards;
    juce::TextButton addButton;

    int currentSelectedSlot = 0;
    int draggedSlotIndex = -1;
    int dropTargetIndex = -1;
    juce::Point<int> currentDragPosition;

    PluginAllianceLauncherProcessor* processor = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginChainView)
};

} // namespace PALauncher
