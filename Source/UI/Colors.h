/*
  ==============================================================================
    Colors.h
    Plugin Alliance Launcher - Theme-aware colour accessors.

    Components should call e.g. Colors::accent() or Colors::cardBackground()
    instead of writing juce::Colour(0x...) literals. The accessor returns
    whatever slot is current on ThemeManager::get().current(), so a theme
    swap re-tints the UI without touching call sites.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ThemeManager.h"

namespace PALauncher::Colors
{
    // ── Backgrounds ─────────────────────────────────────────────────────────
    inline juce::Colour appBackground()          { return ThemeManager::get().current().appBackground; }
    inline juce::Colour panelBackground()        { return ThemeManager::get().current().panelBackground; }
    inline juce::Colour toolbarBackground()      { return ThemeManager::get().current().toolbarBackground; }
    inline juce::Colour sidebarHeader()          { return ThemeManager::get().current().sidebarHeader; }
    inline juce::Colour gridBackground()         { return ThemeManager::get().current().gridBackground; }
    inline juce::Colour chainBackground()        { return ThemeManager::get().current().chainBackground; }
    inline juce::Colour scrollTrackOnDark()      { return ThemeManager::get().current().scrollTrackOnDark; }
    inline juce::Colour scrollTrackOnLight()     { return ThemeManager::get().current().scrollTrackOnLight; }

    // ── Buttons / controls ──────────────────────────────────────────────────
    inline juce::Colour buttonSurface()          { return ThemeManager::get().current().buttonSurface; }
    inline juce::Colour buttonOutline()          { return ThemeManager::get().current().buttonOutline; }
    inline juce::Colour borderSubtle()           { return ThemeManager::get().current().borderSubtle; }
    inline juce::Colour borderDivider()          { return ThemeManager::get().current().borderDivider; }

    // ── Cards ───────────────────────────────────────────────────────────────
    inline juce::Colour cardBackground()         { return ThemeManager::get().current().cardBackground; }
    inline juce::Colour cardBackgroundHover()    { return ThemeManager::get().current().cardBackgroundHover; }
    inline juce::Colour cardBackgroundBypassed() { return ThemeManager::get().current().cardBackgroundBypassed; }
    inline juce::Colour cardBackgroundSelected() { return ThemeManager::get().current().cardBackgroundSelected; }
    inline juce::Colour placeholderImage()       { return ThemeManager::get().current().placeholderImage; }

    // ── Accents ─────────────────────────────────────────────────────────────
    inline juce::Colour accent()                 { return ThemeManager::get().current().accent; }
    inline juce::Colour accentSecondary()        { return ThemeManager::get().current().accentSecondary; }
    inline juce::Colour ctaButton()              { return ThemeManager::get().current().ctaButton; }
    inline juce::Colour highlightAlt()           { return ThemeManager::get().current().highlightAlt; }

    // ── Text ────────────────────────────────────────────────────────────────
    inline juce::Colour textOnDark()             { return ThemeManager::get().current().textOnDark; }
    inline juce::Colour textOnLight()            { return ThemeManager::get().current().textOnLight; }
    inline juce::Colour textMuted()              { return ThemeManager::get().current().textMuted; }
    inline juce::Colour textPlaceholder()        { return ThemeManager::get().current().textPlaceholder; }
    inline juce::Colour textDisabled()           { return ThemeManager::get().current().textDisabled; }

    // ── Fader ───────────────────────────────────────────────────────────────
    inline juce::Colour faderThumbDisabled()     { return ThemeManager::get().current().faderThumbDisabled; }

    // ── Status / meters (fixed across themes) ───────────────────────────────
    inline juce::Colour meterLow()               { return ThemeManager::get().current().meterLow; }
    inline juce::Colour meterMid()               { return ThemeManager::get().current().meterMid; }
    inline juce::Colour meterHigh()              { return ThemeManager::get().current().meterHigh; }

    // ── Shadow ──────────────────────────────────────────────────────────────
    inline juce::Colour shadow()                 { return ThemeManager::get().current().shadow; }
}
