/*
  ==============================================================================
    Colors.h
    Plugin Alliance Launcher - Shared UI palette constants
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher::Colors
{
    // Single off-black used for inactive button surfaces and combo box bodies
    // across the whole UI. Lighter than the 0xff2a2a2a charcoal toolbar so
    // controls sit visibly above the chrome instead of disappearing into it.
    inline const juce::Colour buttonSurface { 0xff5a5a5a };
}
