/*
  ==============================================================================
    ModuleHeaderLayout.h
    Plugin Alliance Launcher - Single source of truth for the toolbar layout
    that spans a chain module (slot + output meter = 168 px wide).
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher::ModuleHeader
{
    // Module geometry. A module = ChainSlotCard (120 px) + ChainMeterCard
    // (48 px) sitting side-by-side. The toolbar visually spans both cards.
    constexpr int slotWidth   = 120;
    constexpr int meterWidth  = 48;
    constexpr int moduleWidth = slotWidth + meterWidth;   // 168
    constexpr int height      = 24;                       // Toolbar strip height
    constexpr int btnY        = 3;                        // Y inset for buttons inside the toolbar
    constexpr int btnH        = 18;                       // Button height

    // Button rect in MODULE-local coords. Slot card consumes x = 0..119,
    // meter card consumes x = 120..167. A button whose right edge exceeds
    // `slotWidth` would be clipped by the slot card's bounds, so AUTO ends
    // exactly at the slot/meter seam (x=120) instead of trying to straddle it.
    struct ButtonRect { int x, w; };

    constexpr ButtonRect power   { 6,   17 };   //   6 → 23   (left margin 6)
    constexpr ButtonRect ab      { 44,  30 };   //  44 → 74   (gap 21 after power)
    constexpr ButtonRect autoBtn { 95,  25 };   //  95 → 120  (gap 21 after ab, ends at seam)
    constexpr ButtonRect remove  { 147, 15 };   // 147 → 162  (right margin 6)
    // Internal gap pattern: 21 / 21 / 27. The third gap is unavoidably larger
    // because AUTO has to sit entirely inside the slot card. If you ever
    // want perfectly even gaps, refactor the toolbar into a sibling overlay
    // that spans both cards.

    // Convert a module-local button rect into the local coords of the slot or
    // meter card. `toolbarTop` is the y where the card has placed its toolbar
    // strip — typically the y of `toolbarBounds`.
    inline juce::Rectangle<int> toSlotRect (const ButtonRect& r, int toolbarTop)
    {
        return { r.x, toolbarTop + btnY, r.w, btnH };
    }

    inline juce::Rectangle<int> toMeterRect (const ButtonRect& r, int toolbarTop)
    {
        return { r.x - slotWidth, toolbarTop + btnY, r.w, btnH };
    }
}
