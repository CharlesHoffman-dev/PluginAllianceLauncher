/*
  ==============================================================================
    Theme.h
    Plugin Alliance Launcher - Theme definition and built-in presets.

    A Theme is a flat struct of semantic colour slots. Components ask the
    ThemeManager for the current theme via Colors:: accessors instead of
    hardcoding hex literals, so swapping the theme repaints the whole UI in
    one shot.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

struct Theme
{
    // Stable identifier used for persistence and the settings menu tick.
    juce::String id;
    juce::String displayName;

    // ── Backgrounds ─────────────────────────────────────────────────────────
    juce::Colour appBackground;          // Deepest dark - main editor fill
    juce::Colour panelBackground;        // Top bar, dark sidebar surfaces
    juce::Colour toolbarBackground;      // Module charcoal, popup menu bg
    juce::Colour sidebarHeader;          // Sidebar section header strips
    juce::Colour gridBackground;         // Plugin list / browser grid area
    juce::Colour chainBackground;        // Chain (signal flow) section background
    juce::Colour scrollTrackOnDark;      // Scrollbar track in dark sidebars
    juce::Colour scrollTrackOnLight;     // Scrollbar track in light grid

    // ── Buttons & controls ──────────────────────────────────────────────────
    juce::Colour buttonSurface;          // Inactive button & ComboBox body
    juce::Colour buttonOutline;          // ComboBox / popup outline
    juce::Colour borderSubtle;           // Default card / chain-slot border
    juce::Colour borderDivider;          // Popup menu separator hairline

    // ── Cards (plugin browser tiles + chain slot bodies) ────────────────────
    juce::Colour cardBackground;         // Card body fill
    juce::Colour cardBackgroundHover;    // Card body on hover
    juce::Colour cardBackgroundBypassed; // Module body when bypassed
    juce::Colour cardBackgroundSelected; // Card body when selected
    juce::Colour placeholderImage;       // Plugin-image placeholder fill

    // ── Accents (selection, focus, highlights) ──────────────────────────────
    juce::Colour accent;                 // Primary highlight (cyan in dark, teal in 70s)
    juce::Colour accentSecondary;        // Star / favourite / secondary highlight
    juce::Colour ctaButton;              // Primary call-to-action button body (Load)
    juce::Colour highlightAlt;           // Secondary highlight: selected-card border, scrollbar thumb

    // ── Text ───────────────────────────────────────────────────────────────
    juce::Colour textOnDark;             // White-on-dark labels
    juce::Colour textOnLight;            // Dark-on-light text inside cards
    juce::Colour textMuted;              // Secondary labels, descriptions
    juce::Colour textPlaceholder;        // "Loading..." / dim hints
    juce::Colour textDisabled;           // Disabled control text

    // ── Fader thumb states (meter gain slider) ──────────────────────────────
    juce::Colour faderThumbDisabled;     // Greyed thumb when auto-gain owns control

    // ── Status / meters (fixed across themes - clipping is always red) ──────
    juce::Colour meterLow;               // Green (level < 0.7)
    juce::Colour meterMid;               // Orange (level 0.7-0.9)
    juce::Colour meterHigh;              // Red (clip, also Remove button)

    // ── Shadow (fixed across themes) ────────────────────────────────────────
    juce::Colour shadow;                 // Drop-shadow tint (ARGB with alpha)
};

namespace Themes
{
    // ── Default (current) — cool dark with cyan accent ──────────────────────
    inline const Theme defaultTheme = {
        "default", "Default (Dark)",

        // Backgrounds
        juce::Colour (0xff121212),
        juce::Colour (0xff1a1a1a),
        juce::Colour (0xff2a2a2a),
        juce::Colour (0xff5a5a5a),       // Sidebar header - matches ComboBox/menu body
        juce::Colour (0xfff9f9f9),
        juce::Colour (0xfff9f9f9),       // Chain bg - matches grid in default
        juce::Colour (0xff1f1f1f),
        juce::Colour (0xffe8e8e8),

        // Buttons / controls
        juce::Colour (0xff5a5a5a),
        juce::Colour (0xff4a4a4a),
        juce::Colour (0xffe0e0e0),
        juce::Colour (0xff3a3a3a),

        // Cards
        // Use hex literal for white instead of juce::Colours::white - the latter
        // is a global Colour whose init order vs. these inline theme structs is
        // unspecified, and on MSVC it sometimes initializes AFTER the theme, so
        // the theme captures a default Colour() (transparent black).
        juce::Colour (0xffffffff),
        juce::Colour (0xfffafafa),
        juce::Colour (0xfff0f0f0),
        juce::Colour (0xffe8f4fc),
        juce::Colour (0xffeeeeee),

        // Accents
        juce::Colour (0xff0cbff2),       // Cyan
        juce::Colour (0xffffc107),       // Gold
        juce::Colour (0xff0cbff2),       // CTA Load button - cyan accent
        juce::Colour (0xff0cbff2),       // highlightAlt - same as accent in default

        // Text
        juce::Colour (0xffffffff),       // textOnDark - white (hex literal, see note above)
        juce::Colour (0xff1a1a1a),
        juce::Colour (0xff999999),
        juce::Colour (0xffb0b0b0),
        juce::Colour (0xff666666),

        // Fader
        juce::Colour (0xffbfbfbf),

        // Status (fixed)
        juce::Colour (0xff00cc00),
        juce::Colour (0xffffaa00),
        juce::Colour (0xffcc0000),

        // Shadow
        juce::Colour (0x15000000),
    };

    // ── 70s Vibe — anchored on a four-colour palette:
    //     #ffd195 cream    #5d9b84 teal
    //     #de7e44 orange   #f2c91f yellow
    //   Backgrounds stay screen-friendly black so the warm palette pops.
    //   The chain section is rendered as horizontal STRIPES of all four
    //   palette colours (handled in PluginChainView::paint), so the
    //   chainBackground field below only stores the first stripe colour
    //   and isn't used directly when the seventies theme is active.
    inline const Theme seventiesTheme = {
        "seventies", "70s Vibe",

        // Backgrounds — screen-friendly blacks
        juce::Colour (0xff0d0d0d),       // App bg          - near-black
        juce::Colour (0xff161616),       // Panel / top bar - one notch lighter
        juce::Colour (0xff262626),       // Toolbar / popup - one more notch lighter
        juce::Colour (0xff5d9b84),       // Sidebar header  - teal/green (palette)
        juce::Colour (0xfff5efe0),       // Grid light bg   - off-white tan
        juce::Colour (0xfff2c91f),       // Chain (fallback - stripes drawn over)
        juce::Colour (0xffc9e8dd),       // Scroll on dark  - pale teal (matches selected card)
        juce::Colour (0xffc9e8dd),       // Scroll on light - pale teal (matches selected card)

        // Buttons / dropdowns - combo body sits on teal/green so combos read as
        // calm surfaces; orange is reserved for active/selected state.
        juce::Colour (0xff5d9b84),       // Button surface  - teal/green
        juce::Colour (0xff4a7a6a),       // Outline         - darker teal
        juce::Colour (0xffe6bc86),       // Subtle border   - dimmer cream
        juce::Colour (0xff4a3328),       // Divider         - dark brown

        // Cards — card body stays WHITE; "light grey" tints become cream.
        juce::Colour (0xffffffff),       // Card body - WHITE (hex literal, not Colours::white; see note above)
        juce::Colour (0xffffdba7),       // Hover           - brighter cream
        juce::Colour (0xffffd195),       // Bypassed        - cream (palette)
        juce::Colour (0xffc9e8dd),       // Selected        - pale teal wash
        juce::Colour (0xffffd195),       // Placeholder     - cream (palette)

        // Accents - orange is the "active / selected" colour in 70s. Used by
        // sidebar selection, Subscribe banner, A/B active side, + button, the
        // "Chain on" pill, and tag chips.
        juce::Colour (0xffde7e44),       // Accent - orange (palette)
        juce::Colour (0xfff2c91f),       // Yellow (palette) - star
        juce::Colour (0xffde7e44),       // CTA Load button - orange (matches accent + banner)
        juce::Colour (0xff5d9b84),       // highlightAlt - teal/green (selected-card border, scrollbar thumb)

        // Text
        juce::Colour (0xffffffff),       // On dark - white
        juce::Colour (0xff3d2a20),       // On cream cards - deep brown
        juce::Colour (0xff8b6a50),       // Muted - mid brown
        juce::Colour (0xffa88864),       // Placeholder
        juce::Colour (0xff6a4f3d),       // Disabled

        // Fader
        juce::Colour (0xff8b6a50),

        // Status (fixed)
        juce::Colour (0xff00cc00),
        juce::Colour (0xffffaa00),
        juce::Colour (0xffcc0000),

        // Shadow (fixed)
        juce::Colour (0x15000000),
    };
} // namespace Themes

} // namespace PALauncher
