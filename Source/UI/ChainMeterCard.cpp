/*
  ==============================================================================
    ChainMeterCard.cpp
    Plugin Alliance Launcher - L/R Peak Meter with Gain Slider Implementation
  ==============================================================================
*/

#include "ChainMeterCard.h"
#include "ModuleHeaderLayout.h"
#include "Colors.h"

namespace PALauncher
{

namespace
{
    // Open rounded-rectangle path - right half of a module: rounded top-right
    // + bottom-right, flat left (no left edge drawn). Mirrors the slot card's
    // horseshoeLeftPath so the two strokes connect at the seam.
    static juce::Path horseshoeRightPath(juce::Rectangle<float> b, float r)
    {
        const float L = b.getX();
        const float R = b.getRight();
        const float T = b.getY();
        const float B = b.getBottom();
        const float halfPi = juce::MathConstants<float>::halfPi;
        const float pi     = juce::MathConstants<float>::pi;

        juce::Path p;
        p.startNewSubPath(L, T);                                  // top-left (flat seam)
        p.lineTo(R - r, T);                                       // top edge
        p.addCentredArc(R - r, T + r, r, r, 0.0f, 0.0f, halfPi);  // top-right arc
        p.lineTo(R, B - r);                                       // right edge
        p.addCentredArc(R - r, B - r, r, r, 0.0f, halfPi, pi);    // bottom-right arc
        p.lineTo(L, B);                                           // bottom edge
        return p;
    }
}

ChainMeterCard::ChainMeterCard(int meterIndex)
    : meterIdx(meterIndex)
{
    setSize(cardWidth, cardHeight);
    startTimerHz(30);  // 30 FPS refresh for smooth meter decay
}

void ChainMeterCard::paint(juce::Graphics& g)
{
    // The output meter (attachedLeft=true) is the right half of a unified
    // slot+meter module. Both fill and stroke are drawn with flat-left corners
    // via the bool variant + an open horseshoe path; that guarantees a clean
    // seam with the slot card on our left and avoids JUCE's pre-clipping of
    // off-screen-extended rounded rects.
    auto bounds = getLocalBounds().toFloat();
    bounds.removeFromTop(2.0f);
    bounds.removeFromBottom(2.0f);
    bounds.removeFromRight(2.0f);
    if (!attachedLeft)
        bounds.removeFromLeft(2.0f);

    constexpr float cardRadius = 6.0f;

    // Card fill: rounded right, flat left (when attached) so the seam is flat.
    juce::Path cardFill;
    cardFill.addRoundedRectangle(bounds.getX(), bounds.getY(),
                                 bounds.getWidth(), bounds.getHeight(),
                                 cardRadius, cardRadius,
                                 !attachedLeft, true,    // top-left, top-right
                                 !attachedLeft, true);   // bottom-left, bottom-right

    // Drop shadow under the meter's half of the module. Same flat-left shape.
    if (attachedLeft)
    {
        g.setColour(Colors::shadow());
        juce::Path shadow;
        auto sb = bounds.translated(1.0f, 2.0f);
        shadow.addRoundedRectangle(sb.getX(), sb.getY(), sb.getWidth(), sb.getHeight(),
                                   cardRadius, cardRadius,
                                   false, true, false, true);
        g.fillPath(shadow);
    }

    // Tint matches the slot so the combined module reads as one body.
    // Selection has no body tint - only the cyan border indicates it.
    juce::Colour bgColour = Colors::cardBackground();
    if (attachedLeft && bypassed)
        bgColour = Colors::cardBackgroundBypassed();
    g.setColour(bgColour);
    g.fillPath(cardFill);

    // Border: cyan when the parent slot is selected. For the attached output
    // meter we use the mirror horseshoe (no left edge) so the slot's border
    // continues across uninterrupted; the input meter draws a full ring.
    g.setColour(selected ? Colors::accent() : Colors::borderSubtle());
    if (attachedLeft)
    {
        g.strokePath(horseshoeRightPath(bounds, cardRadius),
                     juce::PathStrokeType(selected ? 2.0f : 1.0f));
    }
    else
    {
        g.drawRoundedRectangle(bounds, cardRadius, 1.0f);
    }

    auto contentBounds = getLocalBounds();

    // Charcoal toolbar at the top (output meters only). Flat top-left when
    // attached so it meets the slot's toolbar at the seam without a notch.
    if (autoGainSupported)
    {
        contentBounds.removeFromTop(3);
        contentBounds.removeFromBottom(3);
        // Match the card fill's 2 px right pad so the toolbar extends fully
        // to the visible card edge. The extra inset for fader breathing room
        // is applied AFTER the toolbar so it only affects the meter area.
        contentBounds.removeFromRight(2);
        if (!attachedLeft)
            contentBounds.removeFromLeft(3);

        auto toolbarBounds = contentBounds.removeFromTop(autoToolbarHeight);

        // Now narrow the meter/fader area so the fader doesn't crowd the
        // card's rounded right edge.
        contentBounds.removeFromRight(4);

        juce::Path toolbarPath;
        auto tbF = toolbarBounds.toFloat();
        toolbarPath.addRoundedRectangle(tbF.getX(), tbF.getY(),
                                        tbF.getWidth(), tbF.getHeight(),
                                        3.0f, 3.0f,
                                        !attachedLeft, true,    // top-left, top-right
                                        false,         false);  // bottom corners flat
        g.setColour(Colors::toolbarBackground());
        g.fillPath(toolbarPath);

        // AUTO lives in the slot card. X is the only button in the meter
        // card. Its position comes from ModuleHeaderLayout so the entire
        // module toolbar layout lives in one file.
        autoButtonBounds = {};
        removeButtonBounds = ModuleHeader::toMeterRect(ModuleHeader::remove, toolbarBounds.getY());

        g.setColour(Colors::meterHigh());
        g.fillRoundedRectangle(removeButtonBounds.toFloat(), 2.5f);
        g.setColour(Colors::textOnDark());
        g.setFont(juce::Font(10.0f, juce::Font::bold));
        g.drawText("X", removeButtonBounds, juce::Justification::centred);
    }
    else
    {
        autoButtonBounds = {};
        removeButtonBounds = {};
        contentBounds.removeFromTop(6);
    }

    // Breathing room between the charcoal header and the meter bars.
    // Output (in-module) meters get double the gap so the bars don't feel
    // crammed against the toolbar.
    contentBounds.removeFromTop(autoGainSupported ? 8 : 4);

    // Bars on the input meter are slightly taller (no toolbar above) but end
    // at the same Y as the output meter bars so the dB readouts beneath every
    // meter in the chain line up horizontally.
    const int barsHeight = autoGainSupported ? 70 : 95;
    auto meterArea = contentBounds.removeFromTop(barsHeight);

    constexpr int thumbH = 14;

    if (autoGainSupported && gainEditable)
    {
        // Layout: [L bar] gap [R bar] gap [fader column] inside the content
        // strip. Computed widths fit inside the 42 px post-padding width of
        // an attached output meter (right inset = 6).
        constexpr int barWidth   = 7;
        constexpr int barGap     = 2;
        constexpr int faderWidth = 12;
        constexpr int innerGap   = 4;
        const int groupWidth = barWidth * 2 + barGap + innerGap + faderWidth;
        int x = meterArea.getCentreX() - groupWidth / 2;

        auto leftMeterBounds  = juce::Rectangle<int>(x,                              meterArea.getY(), barWidth, meterArea.getHeight());
        auto rightMeterBounds = juce::Rectangle<int>(x + barWidth + barGap,          meterArea.getY(), barWidth, meterArea.getHeight());
        auto faderArea        = juce::Rectangle<int>(x + barWidth * 2 + barGap + innerGap,
                                                     meterArea.getY(), faderWidth, meterArea.getHeight());

        // L/R bar backgrounds - match the plugin browser grid tan/grey
        g.setColour(Colors::gridBackground());
        g.fillRoundedRectangle(leftMeterBounds.toFloat(),  2.0f);
        g.fillRoundedRectangle(rightMeterBounds.toFloat(), 2.0f);

        auto drawMeter = [&](juce::Rectangle<int> b, float level)
        {
            if (level <= 0.0f) return;
            int fillH = static_cast<int>(level * b.getHeight());
            auto fillBounds = b.removeFromBottom(fillH).toFloat();
            juce::Colour c = (level < 0.7f) ? Colors::meterLow()
                           : (level < 0.9f) ? Colors::meterMid()
                                            : Colors::meterHigh();
            g.setColour(c);
            g.fillRoundedRectangle(fillBounds, 2.0f);
        };
        drawMeter(leftMeterBounds,  leftLevel);
        drawMeter(rightMeterBounds, rightLevel);

        // Gain fader: track + unity tick + draggable thumb. Greyed when
        // auto-gain is on (auto overrides manual gain).
        const bool faderEnabled = !autoGainEnabled;

        // Track is inset by thumbH/2 so the thumb's top/bottom edges align
        // with the meter top/bottom at the slider's travel extremes.
        auto trackBounds = juce::Rectangle<int>(faderArea.getCentreX() - 2,
                                                faderArea.getY() + thumbH / 2,
                                                4,
                                                faderArea.getHeight() - thumbH);
        faderTrackBounds = faderArea;  // Whole column is draggable, not just the 4px track
        g.setColour(Colors::borderSubtle().brighter(0.1f));
        g.fillRoundedRectangle(trackBounds.toFloat(), 2.0f);

        // Unity-gain tick (small marker at 0 dB position).
        {
            const float unityFrac = (0.0f - kGainMinDb) / (kGainMaxDb - kGainMinDb);
            const int unityY = trackBounds.getBottom() - (int) std::round(unityFrac * trackBounds.getHeight());
            g.setColour(Colors::faderThumbDisabled());
            g.fillRect(faderArea.getX() + 1, unityY - 1, faderArea.getWidth() - 2, 1);
        }

        // Thumb position from current gain value.
        float gainDb = juce::Decibels::gainToDecibels(gainValue, kGainMinDb);
        float frac = (juce::jlimit(kGainMinDb, kGainMaxDb, gainDb) - kGainMinDb)
                     / (kGainMaxDb - kGainMinDb);
        const int thumbY = trackBounds.getBottom() - (int) std::round(frac * trackBounds.getHeight()) - thumbH / 2;
        sliderBounds = juce::Rectangle<int>(faderArea.getX(), thumbY, faderArea.getWidth(), thumbH);

        // Draw the thumb. Cyan when active, mid-grey when auto-gain has the
        // manual control disabled.
        auto thumbColour = faderEnabled ? Colors::accent() : Colors::faderThumbDisabled();
        if (faderEnabled && sliderBounds.contains(getMouseXYRelative()))
            thumbColour = thumbColour.brighter(0.15f);
        g.setColour(thumbColour);
        g.fillRoundedRectangle(sliderBounds.toFloat(), 3.0f);

        // Subtle grip lines on the thumb so it reads as draggable.
        g.setColour(Colors::textOnDark().withAlpha(faderEnabled ? 0.65f : 0.35f));
        for (int i = -1; i <= 1; ++i)
        {
            int gy = sliderBounds.getCentreY() + i * 3;
            g.fillRect(sliderBounds.getX() + 3, gy, sliderBounds.getWidth() - 6, 1);
        }
    }
    else
    {
        // Input meter (no gain slider): narrower bars centered in the card.
        constexpr int barWidth = 7;
        constexpr int barGap   = 2;
        int totalW = barWidth * 2 + barGap;
        int x = meterArea.getCentreX() - totalW / 2;
        auto leftMeterBounds  = juce::Rectangle<int>(x,                       meterArea.getY(), barWidth, meterArea.getHeight());
        auto rightMeterBounds = juce::Rectangle<int>(x + barWidth + barGap,   meterArea.getY(), barWidth, meterArea.getHeight());

        // L/R bar backgrounds - match the plugin browser grid tan/grey
        g.setColour(Colors::gridBackground());
        g.fillRoundedRectangle(leftMeterBounds.toFloat(),  2.0f);
        g.fillRoundedRectangle(rightMeterBounds.toFloat(), 2.0f);

        auto drawMeter = [&](juce::Rectangle<int> b, float level)
        {
            if (level <= 0.0f) return;
            int fillH = static_cast<int>(level * b.getHeight());
            auto fillBounds = b.removeFromBottom(fillH).toFloat();
            juce::Colour c = (level < 0.7f) ? Colors::meterLow()
                           : (level < 0.9f) ? Colors::meterMid()
                                            : Colors::meterHigh();
            g.setColour(c);
            g.fillRoundedRectangle(fillBounds, 2.0f);
        };
        drawMeter(leftMeterBounds,  leftLevel);
        drawMeter(rightMeterBounds, rightLevel);

        sliderBounds = {};       // No gain slider on the input meter.
        faderTrackBounds = {};
    }

    // Numeric readout centered in the gap between the meter bottom and the
    // module bottom (a 3 px gap above + 14 px text rect lands the baseline at
    // the visual midpoint of that strip).
    contentBounds.removeFromTop(3);
    auto readoutBounds = contentBounds.removeFromTop(14);

    auto formatDb = [](float db) -> juce::String
    {
        if (db <= ChainMeterCard::kGainMinDb + 0.05f)
            return juce::String(juce::CharPointer_UTF8("-\xe2\x88\x9e"));  // "-∞"
        return juce::String(db, 1);
    };

    if (autoGainEnabled)
    {
        juce::String corrText = (autoGainCorrectionDb >= 0.0f)
            ? "+" + juce::String(autoGainCorrectionDb, 1)
            : juce::String(autoGainCorrectionDb, 1);

        g.setColour(Colors::accent());
        g.setFont(juce::Font(10.0f, juce::Font::bold));
        g.drawText(corrText, readoutBounds, juce::Justification::centred);
    }
    else if (gainEditable)
    {
        float gainDb = juce::Decibels::gainToDecibels(gainValue, kGainMinDb);
        g.setColour(Colors::textDisabled());
        g.setFont(juce::Font(10.0f, juce::Font::bold));
        g.drawText(formatDb(gainDb), readoutBounds, juce::Justification::centred);
    }
    else
    {
        // Input meter: show the current peak dB (loudest of L/R), tracking
        // the meter bars' decay so the number falls naturally with the level.
        float peak = juce::jmax(leftLevel, rightLevel);
        float peakDb = juce::Decibels::gainToDecibels(peak, kGainMinDb);
        g.setColour(Colors::textDisabled());
        g.setFont(juce::Font(10.0f, juce::Font::bold));
        g.drawText(formatDb(peakDb), readoutBounds, juce::Justification::centred);
    }
}

void ChainMeterCard::resized()
{
    // Bounds calculated in paint()
}

void ChainMeterCard::setLevels(float newLeftPeak, float newRightPeak)
{
    leftLevel = juce::jmax(leftLevel, newLeftPeak);
    rightLevel = juce::jmax(rightLevel, newRightPeak);

    leftPeak = newLeftPeak;
    rightPeak = newRightPeak;

    repaint();
}

void ChainMeterCard::setGainValue(float newGain)
{
    gainValue = juce::jlimit(0.0f, kGainMaxLinear, newGain);
    repaint();
}

void ChainMeterCard::setAutoGainEnabled(bool enabled)
{
    autoGainEnabled = enabled;
    if (!enabled)
        setAutoGainAnalyzing(false);
    repaint();
}

void ChainMeterCard::setSelected(bool isSelected)
{
    if (selected != isSelected)
    {
        selected = isSelected;
        repaint();
    }
}

void ChainMeterCard::setBypassed(bool bypass)
{
    if (bypassed != bypass)
    {
        bypassed = bypass;
        repaint();
    }
}

void ChainMeterCard::setAutoGainCorrectionDb(float correctionDb)
{
    autoGainCorrectionDb = correctionDb;
}

void ChainMeterCard::setAutoGainAnalyzing(bool analyzing)
{
    if (autoGainAnalyzing == analyzing)
        return;

    autoGainAnalyzing = analyzing;
    if (analyzing)
    {
        autoFlashOn = true;
    }
    else
    {
        autoFlashOn = false;
    }
    repaint();
}

void ChainMeterCard::timerCallback()
{
    // Decay meter levels smoothly
    float decayRate = 0.95f;
    leftLevel *= decayRate;
    rightLevel *= decayRate;

    if (leftLevel < 0.001f) leftLevel = 0.0f;
    if (rightLevel < 0.001f) rightLevel = 0.0f;

    // Flash the AUTO button at ~4Hz while analyzing.
    static int flashCounter = 0;
    if (autoGainAnalyzing && ++flashCounter >= 7)
    {
        autoFlashOn = !autoFlashOn;
        flashCounter = 0;
    }

    repaint();
}

void ChainMeterCard::mouseDown(const juce::MouseEvent& e)
{
    // X (remove module) - checked first since it's the smallest hit target.
    if (autoGainSupported && removeButtonBounds.contains(e.getPosition()))
    {
        if (onRemoveRequest)
            onRemoveRequest(meterIdx);
        return;
    }

    // AUTO button hit (output meters only)
    if (autoGainSupported && autoButtonBounds.contains(e.getPosition()))
    {
        autoGainEnabled = !autoGainEnabled;
        if (onAutoGainToggled)
            onAutoGainToggled(meterIdx, autoGainEnabled);
        repaint();
        return;
    }

    // Manual gain fader. Modifier-click resets to 0 dB unity; plain click
    // jumps the thumb to the mouse Y; Shift+drag is fine-tune (relative,
    // 10x less sensitive).
    if (gainEditable && !autoGainEnabled && faderTrackBounds.contains(e.getPosition()))
    {
        if (e.mods.isCommandDown())
        {
            gainValue = 1.0f;  // 0 dB
            if (onGainChanged)
                onGainChanged(meterIdx, gainValue);
            repaint();
            return;
        }

        isDraggingSlider = true;
        fineDragMode = e.mods.isShiftDown();
        dragAnchorY = e.position.getY();
        dragAnchorDb = juce::Decibels::gainToDecibels(gainValue, kGainMinDb);
        if (!fineDragMode)
            applyFaderPosition(e.position.getY());
        return;
    }

    // Clicking anywhere else on the meter selects the parent module - the
    // slot to our left treats slot + meter as one unit for selection.
    if (onSelectRequest)
        onSelectRequest(meterIdx);
}

void ChainMeterCard::mouseDrag(const juce::MouseEvent& e)
{
    if (!isDraggingSlider)
        return;

    const bool shiftNow = e.mods.isShiftDown();
    if (shiftNow != fineDragMode)
    {
        // Toggling shift mid-drag re-anchors at the current position so the
        // gain doesn't jump as the sensitivity changes.
        fineDragMode = shiftNow;
        dragAnchorY = e.position.getY();
        dragAnchorDb = juce::Decibels::gainToDecibels(gainValue, kGainMinDb);
        return;
    }

    if (fineDragMode)
    {
        // Fine-tune: 10x less sensitive than the absolute mapping.
        constexpr float kFineScale = 0.1f;
        const float trackPixels = juce::jmax(1.0f, (float) faderTrackBounds.getHeight() - 14.0f);
        const float dbPerPixel  = (kGainMaxDb - kGainMinDb) / trackPixels;
        const float deltaY = dragAnchorY - e.position.getY();
        const float newDb  = juce::jlimit(kGainMinDb, kGainMaxDb,
                                          dragAnchorDb + deltaY * dbPerPixel * kFineScale);

        gainValue = juce::Decibels::decibelsToGain(newDb, kGainMinDb);
        if (onGainChanged)
            onGainChanged(meterIdx, gainValue);
        repaint();
    }
    else
    {
        applyFaderPosition(e.position.getY());
    }
}

void ChainMeterCard::applyFaderPosition(float mouseY)
{
    if (faderTrackBounds.isEmpty())
        return;

    // Map the mouse Y inside the fader track to a dB value, then to a linear
    // gain. Top of the track = +12 dB, bottom = -60 dB. The 7 px insets match
    // thumbH/2 so the drag extremes match the thumb's visible travel.
    const float top    = (float) faderTrackBounds.getY() + 7.0f;
    const float bottom = (float) faderTrackBounds.getBottom() - 7.0f;
    const float clamped = juce::jlimit(top, bottom, mouseY);
    const float frac   = (bottom - clamped) / (bottom - top);  // 0 at bottom, 1 at top
    const float newDb  = kGainMinDb + frac * (kGainMaxDb - kGainMinDb);

    gainValue = juce::Decibels::decibelsToGain(newDb, kGainMinDb);

    if (onGainChanged)
        onGainChanged(meterIdx, gainValue);

    repaint();
}

void ChainMeterCard::mouseUp(const juce::MouseEvent&)
{
    isDraggingSlider = false;
}

void ChainMeterCard::mouseMove(const juce::MouseEvent&)
{
    repaint();  // Repaint to update hover highlighting
}

} // namespace PALauncher
