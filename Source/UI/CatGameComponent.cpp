/*
  ==============================================================================
    CatGameComponent.cpp
  ==============================================================================
*/

#include "CatGameComponent.h"
#include "../Utils/PluginImageCache.h"
#include "../Utils/SettingsManager.h"

namespace PALauncher
{

// ─────────────────────────────────────────────────────────────────────────────
//  Powerup helpers
// ─────────────────────────────────────────────────────────────────────────────
juce::Colour CatGameComponent::powerColour (PowerType t)
{
    switch (t)
    {
        case PowerType::Spread:  return juce::Colour (0xff5d9b84);   // teal
        case PowerType::Rapid:   return juce::Colour (0xfff2c91f);   // yellow
        case PowerType::Bomb:    return juce::Colour (0xffe34a3a);   // red
        case PowerType::Shield:  return juce::Colour (0xff7ed957);   // green
        case PowerType::Slow:    return juce::Colour (0xff9d6cd9);   // purple
        case PowerType::Mega:    return juce::Colour (0xffde7e44);   // orange
    }
    return juce::Colours::white;
}

juce::String CatGameComponent::powerLabel (PowerType t)
{
    switch (t)
    {
        case PowerType::Spread: return "SPREAD";
        case PowerType::Rapid:  return "RAPID";
        case PowerType::Bomb:   return "BOMB";
        case PowerType::Shield: return "SHIELD";
        case PowerType::Slow:   return "SLOW";
        case PowerType::Mega:   return "MEGA";
    }
    return {};
}

juce::Font CatGameComponent::retroFont (float height, int styleFlags) const
{
    if (retroTypeface != nullptr)
    {
        juce::Font f (retroTypeface);
        f.setHeight (height);
        if (styleFlags != 0) f.setStyleFlags (styleFlags);
        return f;
    }
    return juce::Font (height, styleFlags);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Construction
// ─────────────────────────────────────────────────────────────────────────────
CatGameComponent::CatGameComponent (juce::MidiKeyboardState& sharedKeyboardState,
                                    SettingsManager* settings)
    : kbState (sharedKeyboardState),
      settingsManager (settings),
      keyboard (sharedKeyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    setWantsKeyboardFocus (true);
    setOpaque (true);

    keyboard.setAvailableRange (kFirstNote, kLastNote);
    keyboard.setLowestVisibleKey (kFirstNote);
    keyboard.setOctaveForMiddleC (4);
    keyboard.setKeyPressBaseOctave (4);
    addAndMakeVisible (keyboard);

    {
        auto raw = PluginImageCache::getInstance().getAllCachedImages();
        pluginImagePool.ensureStorageAllocated (raw.size());
        // Asteroids max out around 180px wide; pre-scaling avoids JUCE's
        // per-frame resample of full-resolution browser thumbs.
        for (auto& img : raw)
        {
            if (! img.isValid()) continue;
            const int maxW = 220;
            if (img.getWidth() > maxW)
            {
                const float ratio = (float) maxW / (float) img.getWidth();
                pluginImagePool.add (img.rescaled (maxW,
                                                   juce::jmax (1, (int) (img.getHeight() * ratio)),
                                                   juce::Graphics::highResamplingQuality));
            }
            else
            {
                pluginImagePool.add (img);
            }
        }
    }

    // Load cat-head PNGs once. Try a few candidate locations so it works from
    // the source tree, the standalone exe folder, and a future installer.
    {
        const juce::File candidates[] = {
            juce::File::getSpecialLocation (juce::File::currentExecutableFile)
                .getParentDirectory().getChildFile ("Resources/CatHeads"),
            juce::File ("C:/Users/charl/PluginAllianceLauncher/Resources/CatHeads"),
        };
        for (auto& dir : candidates)
        {
            if (! dir.isDirectory()) continue;
            auto files = dir.findChildFiles (juce::File::findFiles, false, "*.png");
            files.sort();
            for (auto& f : files)
            {
                auto img = juce::ImageFileFormat::loadFrom (f);
                if (! img.isValid()) continue;
                // Pre-scale source PNGs (often 256x256+) down to a sprite-sized
                // texture so per-frame rotate+draw stays cheap.
                catHeadImages.add (img.rescaled (96, 96, juce::Graphics::highResamplingQuality));

                // The sphynx is the splash-screen mascot; load a higher-res
                // copy so it stays sharp at title size.
                if (f.getFileNameWithoutExtension() == "cat_r2_c4")
                    splashCatImage = img.rescaled (220, 220, juce::Graphics::highResamplingQuality);
            }
            if (! catHeadImages.isEmpty()) break;
        }
    }

    // Three distinct heads for the splash trio: first, sphynx, last - gives
    // good visual variety across the row.
    if (splashCatImage.isValid())
        splashHeads.add (splashCatImage);
    if (! catHeadImages.isEmpty())
    {
        splashHeads.add (catHeadImages.getReference (0));
        splashHeads.add (catHeadImages.getReference (catHeadImages.size() - 1));
    }

    // Load the retro pixel font (Press Start 2P) from Resources/Fonts.
    {
        const juce::File fontCandidates[] = {
            juce::File::getSpecialLocation (juce::File::currentExecutableFile)
                .getParentDirectory().getChildFile ("Resources/Fonts/PressStart2P-Regular.ttf"),
            juce::File ("C:/Users/charl/PluginAllianceLauncher/Resources/Fonts/PressStart2P-Regular.ttf"),
        };
        for (auto& f : fontCandidates)
        {
            if (! f.existsAsFile()) continue;
            juce::MemoryBlock mb;
            if (f.loadFileAsData (mb))
            {
                retroTypeface = juce::Typeface::createSystemTypefaceFor (mb.getData(), mb.getSize());
                if (retroTypeface != nullptr) break;
            }
        }
    }

    if (settingsManager != nullptr)
        sessionHighScore = settingsManager->getCatGameHighScore();

    kbState.addListener (this);
    startTimerHz (kFps);
}

void CatGameComponent::postSfx (Sfx s) const
{
    if (onSfxRequested) onSfxRequested (s);
}

CatGameComponent::~CatGameComponent()
{
    kbState.removeListener (this);
}

void CatGameComponent::resized()
{
    auto bounds = getLocalBounds();
    auto kbBounds = bounds.removeFromBottom (kKeyboardHeight);
    keyboard.setBounds (kbBounds);
    // Range now ends on B (no trailing C), so the simple "octaves * 7" math works.
    const int whiteKeysVisible = ((kLastNote - kFirstNote + 1) / 12) * 7;
    keyboard.setKeyWidth ((float) kbBounds.getWidth() / (float) whiteKeysVisible);

    buildStarfield();
}

void CatGameComponent::buildStarfield()
{
    stars.clearQuick();
    nebulas.clearQuick();
    juce::Random starRng (0xCA75);

    const int playH = getHeight() - kKeyboardHeight;
    const int playW = getWidth();
    if (playW <= 0 || playH <= 0) return;

    nebulas.add ({ playW * 0.18f, playH * 0.30f, playH * 0.55f, juce::Colour (0x551c4080) });
    nebulas.add ({ playW * 0.75f, playH * 0.50f, playH * 0.50f, juce::Colour (0x55502080) });
    nebulas.add ({ playW * 0.55f, playH * 0.78f, playH * 0.45f, juce::Colour (0x4530a0a0) });

    const int starCount = 180;
    for (int i = 0; i < starCount; ++i)
    {
        Star s;
        s.x = starRng.nextFloat() * (float) playW;
        s.y = starRng.nextFloat() * (float) playH;
        const float rRand = starRng.nextFloat();
        s.radius = 0.5f + rRand * rRand * rRand * 2.8f;

        const int colourPick = starRng.nextInt (10);
        if      (colourPick < 6) s.colour = juce::Colours::white;
        else if (colourPick < 8) s.colour = juce::Colour (0xffaecbff);
        else if (colourPick < 9) s.colour = juce::Colour (0xfffff5cc);
        else                     s.colour = juce::Colour (0xffffd1d1);

        s.twinkles     = (starRng.nextInt (6) == 0);
        s.twinklePhase = starRng.nextFloat() * juce::MathConstants<float>::twoPi;
        stars.add (s);
    }

    // Bake the static layers (gradient + nebulas + non-twinkling stars) into
    // one image so paint() can blit instead of re-rasterizing every frame.
    const int W = getWidth();
    const int H = getHeight();
    if (W <= 0 || H <= 0) { backdropCache = {}; return; }

    backdropCache = juce::Image (juce::Image::ARGB, W, H, true);
    juce::Graphics bg (backdropCache);

    juce::ColourGradient grad (juce::Colour (0xff04020a), 0.0f, 0.0f,
                               juce::Colour (0xff200c2e), 0.0f, (float) H,
                               false);
    grad.addColour (0.5f, juce::Colour (0xff140828));
    bg.setGradientFill (grad);
    bg.fillAll();

    for (auto& n : nebulas)
    {
        juce::ColourGradient ngrad (n.colour, n.cx, n.cy,
                                    n.colour.withAlpha (0.0f),
                                    n.cx + n.radius, n.cy,
                                    true);
        bg.setGradientFill (ngrad);
        bg.fillEllipse (n.cx - n.radius, n.cy - n.radius, n.radius * 2.0f, n.radius * 2.0f);
    }

    bg.setOpacity (1.0f);
    for (auto& s : stars)
    {
        if (s.twinkles) continue;     // twinkling stars are overlaid live
        bg.setColour (s.colour.withAlpha (0.9f));
        bg.fillEllipse (s.x - s.radius, s.y - s.radius, s.radius * 2.0f, s.radius * 2.0f);
    }
}

bool CatGameComponent::keyPressed (const juce::KeyPress& key)
{
    if (key == juce::KeyPress::escapeKey)
    {
        if (onExitRequested) onExitRequested();
        return true;
    }
    if (state == State::Splash)
    {
        state = State::Playing;
        return true;
    }
    if (state == State::GameOver && key == juce::KeyPress::returnKey)
    {
        resetGame();
        return true;
    }
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Paint
// ─────────────────────────────────────────────────────────────────────────────
void CatGameComponent::paint (juce::Graphics& g)
{
    // Static layers (gradient + nebulas + non-twinkling stars) come from the
    // cache so 60fps repaints don't re-rasterize them.
    if (backdropCache.isValid())
        g.drawImageAt (backdropCache, 0, 0);
    else
        g.fillAll (juce::Colour (0xff140828));

    // Only the twinkling subset needs live drawing.
    g.setOpacity (1.0f);
    for (auto& s : stars)
    {
        if (! s.twinkles) continue;
        const float alpha = 0.45f + 0.55f * (0.5f + 0.5f * std::sin (globalTime * 3.0f + s.twinklePhase));
        g.setColour (s.colour.withAlpha (alpha));
        g.fillEllipse (s.x - s.radius, s.y - s.radius, s.radius * 2.0f, s.radius * 2.0f);
    }

    // Slow-mo overlay tint
    if (slowTime > 0.0f)
    {
        g.setColour (juce::Colour (0xff9d6cd9).withAlpha (0.08f));
        g.fillAll();
    }

    // ── Falling plugins ─────────────────────────────────────────────────────
    g.setOpacity (1.0f);
    g.setColour (juce::Colours::white);
    for (auto& p : falling)
    {
        auto centre = juce::Point<float> (p.x + p.w * 0.5f, p.y + p.h * 0.5f);
        juce::Graphics::ScopedSaveState save (g);
        g.addTransform (juce::AffineTransform::rotation (p.rotation, centre.x, centre.y));
        g.setOpacity (1.0f);
        if (p.image.isValid())
            g.drawImageWithin (p.image, (int) p.x, (int) p.y, (int) p.w, (int) p.h,
                               juce::RectanglePlacement::centred);
        else
        {
            g.setColour (juce::Colours::lightgrey);
            g.fillRoundedRectangle (p.x, p.y, p.w, p.h, 6.0f);
        }
    }

    // ── Bosses (drawn over the regular asteroids so the halo isn't clipped) ─
    for (auto& b : bosses)
        drawBoss (g, b);

    // ── Floating powerup pickups ────────────────────────────────────────────
    for (auto& p : powerupsOnScreen)
        drawPowerup (g, p);

    // ── Particles ───────────────────────────────────────────────────────────
    for (auto& part : particles)
    {
        g.setColour (part.colour.withAlpha (juce::jlimit (0.0f, 1.0f, part.life)));
        g.fillEllipse (part.x - part.size, part.y - part.size,
                       part.size * 2.0f,   part.size * 2.0f);
    }

    // ── Explosion shockwaves ────────────────────────────────────────────────
    for (auto& ex : explosions)
    {
        const float age = (float) ex.ageTicks / (float) Explosion::lifetime;
        const float r   = ex.size * 0.5f * (0.3f + age * 1.4f);
        const float a   = juce::jmax (0.0f, 1.0f - age);

        g.setColour (juce::Colour (0xfff2c91f).withAlpha (a * 0.6f));
        g.drawEllipse (ex.cx - r, ex.cy - r, r * 2.0f, r * 2.0f, 3.0f);
        g.setColour (juce::Colour (0xffde7e44).withAlpha (a * 0.45f));
        g.drawEllipse (ex.cx - r * 0.6f, ex.cy - r * 0.6f, r * 1.2f, r * 1.2f, 2.0f);
    }

    // ── Cat heads ───────────────────────────────────────────────────────────
    for (auto& h : projectiles)
    {
        const auto rect = juce::Rectangle<float> (h.x - h.size * 0.5f,
                                                  h.y - h.size * 0.5f,
                                                  h.size, h.size);
        juce::Graphics::ScopedSaveState save (g);
        g.addTransform (juce::AffineTransform::rotation (h.rotation, h.x, h.y));

        if (h.headImageIndex >= 0 && h.headImageIndex < catHeadImages.size())
        {
            g.setOpacity (1.0f);
            g.setColour (juce::Colours::white);
            g.drawImageWithin (catHeadImages.getReference (h.headImageIndex),
                               (int) rect.getX(), (int) rect.getY(),
                               (int) rect.getWidth(), (int) rect.getHeight(),
                               juce::RectanglePlacement::centred);
        }
        else
        {
            drawCatHead (g, rect);
        }
    }

    // ── Toasts (floating text feedback) ─────────────────────────────────────
    for (auto& t : toasts)
    {
        const float alpha = juce::jlimit (0.0f, 1.0f, t.life);
        g.setColour (juce::Colours::black.withAlpha (alpha * 0.45f));
        g.setFont (retroFont (t.fontSize * 0.7f));
        g.drawText (t.text, (int) t.x - 199, (int) t.y - 14, 400, 30, juce::Justification::centred);
        g.setColour (t.colour.withAlpha (alpha));
        g.drawText (t.text, (int) t.x - 200, (int) t.y - 15, 400, 30, juce::Justification::centred);
    }

    // ── HUD ─────────────────────────────────────────────────────────────────
    g.setColour (juce::Colours::white.withAlpha (0.9f));
    g.setFont (retroFont (20.0f));
    g.drawText ("SCORE  " + juce::String (score), 14, 10, 420, 28, juce::Justification::topLeft);

    g.setFont (retroFont (12.0f));
    g.setColour (juce::Colour (0xff4fd5ff));
    g.drawText ("HISCORE  " + juce::String (sessionHighScore), 14, 46, 420, 20, juce::Justification::topLeft);

    if (combo >= 2)
    {
        const float scale = 1.0f + juce::jmin (0.65f, (float) (combo - 1) * 0.06f);
        g.setColour (juce::Colour (0xfff2c91f));
        g.setFont (retroFont (16.0f * scale));
        g.drawText ("x" + juce::String (combo) + "  COMBO",
                    getWidth() / 2 - 200, 14, 400, 32,
                    juce::Justification::centred);
    }

    // Lives - cat-head icons, bottom-right above the keyboard. Remaining lives
    // draw fully opaque; lost lives draw as a dim silhouette.
    {
        const int   iconSize = 24;
        const int   gap      = 4;
        const int   totalW   = kMaxEscapes * iconSize + (kMaxEscapes - 1) * gap;
        const int   startX   = getWidth()  - totalW - 14;
        const int   yPos     = getHeight() - kKeyboardHeight - iconSize - 6;
        for (int i = 0; i < kMaxEscapes; ++i)
        {
            const int x = startX + i * (iconSize + gap);
            // Lives deplete left-to-right: index 0 dies first, the rightmost
            // (index kMaxEscapes-1) is the last cat standing.
            const bool alive = i >= escaped;

            if (! catHeadImages.isEmpty())
            {
                // Same head each session (index 0) so the readout reads as one
                // unified row of "lives" rather than a chaotic mix.
                const auto& img = catHeadImages.getReference (0);
                g.setOpacity (alive ? 1.0f : 0.18f);
                g.drawImageWithin (img, x, yPos, iconSize, iconSize,
                                   juce::RectanglePlacement::centred);
            }
            else
            {
                g.setOpacity (1.0f);
                g.setColour (juce::Colours::white.withAlpha (alive ? 0.85f : 0.20f));
                g.fillEllipse ((float) x, (float) yPos,
                               (float) iconSize, (float) iconSize);
            }
        }
        g.setOpacity (1.0f);
    }

    drawActivePowerupChips (g);

    g.setFont (retroFont (8.0f));
    g.setColour (juce::Colours::white.withAlpha (0.45f));
    g.drawText ("PLAY A NOTE TO SHOOT   SHOOT POWERUPS TO GRAB THEM   ESC TO EXIT",
                12, getHeight() - kKeyboardHeight - 20, getWidth() - 24, 16,
                juce::Justification::centredLeft);

    // ── Splash overlay ──────────────────────────────────────────────────────
    if (state == State::Splash)
    {
        g.setColour (juce::Colours::black.withAlpha (0.55f));
        g.fillRect (0, 0, getWidth(), getHeight() - kKeyboardHeight);

        const int cx = getWidth() / 2;
        const int cy = (getHeight() - kKeyboardHeight) / 2;

        // Three distinct rumbling cat heads above the title. Rumble = small
        // per-frame sin-driven jitter, much faster than the previous spin.
        if (! splashHeads.isEmpty())
        {
            const int faceSize = 110;
            const int gap      = 32;
            const int totalW   = faceSize * 3 + gap * 2;
            int x = cx - totalW / 2;
            const int y = cy - 220;
            for (int i = 0; i < 3; ++i)
            {
                const auto& img = splashHeads.getReference (i % splashHeads.size());

                // True per-frame random jitter - reads as a hard vibration
                // rather than the smooth sin-wobble it was before.
                const float jx = (rng.nextFloat() * 2.0f - 1.0f) * 6.0f;
                const float jy = (rng.nextFloat() * 2.0f - 1.0f) * 6.0f;
                const float ja = (rng.nextFloat() * 2.0f - 1.0f) * 0.12f;

                juce::Graphics::ScopedSaveState save (g);
                g.addTransform (juce::AffineTransform::translation (jx, jy));
                g.addTransform (juce::AffineTransform::rotation (ja,
                                    (float) (x + faceSize * 0.5f),
                                    (float) (y + faceSize * 0.5f)));
                g.setOpacity (1.0f);
                g.setColour (juce::Colours::white);
                g.drawImageWithin (img, x, y, faceSize, faceSize,
                                   juce::RectanglePlacement::centred);
                x += faceSize + gap;
            }
        }

        // Title - arcade yellow with a shadow drop for chunky CRT vibes.
        g.setFont (retroFont (52.0f));
        g.setColour (juce::Colour (0xff2a2a2a));
        g.drawText ("PLUGIN BLASTER", cx - 500 + 4, cy - 70 + 4, 1000, 80,
                    juce::Justification::centred);
        g.setColour (juce::Colour (0xfff2c91f));
        g.drawText ("PLUGIN BLASTER", cx - 500, cy - 70, 1000, 80,
                    juce::Justification::centred);

        // Subtitle - bumped up for legibility on the splash.
        g.setColour (juce::Colours::white);
        g.setFont (retroFont (16.0f));
        g.drawText ("PLAY NOTES TO LAUNCH CATS",
                    cx - 600, cy + 20, 1200, 24, juce::Justification::centred);
        g.drawText ("SHOOT THE FALLING PLUGINS - DON'T LET THEM ESCAPE",
                    cx - 600, cy + 52, 1200, 24, juce::Justification::centred);

        if (sessionHighScore > 0)
        {
            g.setColour (juce::Colour (0xff4fd5ff));
            g.setFont (retroFont (14.0f));
            g.drawText ("HI " + juce::String (sessionHighScore),
                        cx - 400, cy + 102, 800, 22, juce::Justification::centred);
        }

        // Bright yellow + dark shadow pulses for "press any key" - reads
        // strongly over the dark-purple galaxy without blending in.
        const float pulse = 0.6f + 0.4f * (0.5f + 0.5f * std::sin (globalTime * 3.5f));
        g.setFont (retroFont (18.0f));
        g.setColour (juce::Colour (0xff000000).withAlpha (pulse * 0.7f));
        g.drawText ("PRESS ANY KEY TO START",
                    cx - 600 + 3, cy + 152 + 3, 1200, 24, juce::Justification::centred);
        g.setColour (juce::Colour (0xfff2c91f).withAlpha (pulse));
        g.drawText ("PRESS ANY KEY TO START",
                    cx - 600, cy + 152, 1200, 24, juce::Justification::centred);

        g.setColour (juce::Colours::white.withAlpha (0.5f));
        g.setFont (retroFont (10.0f));
        g.drawText ("ESC TO EXIT",
                    cx - 300, cy + 196, 600, 16, juce::Justification::centred);
    }

    // ── Game-over overlay ───────────────────────────────────────────────────
    if (state == State::GameOver)
    {
        g.setColour (juce::Colours::black.withAlpha (0.72f));
        g.fillRect (0, 0, getWidth(), getHeight() - kKeyboardHeight);

        const int cx = getWidth() / 2;
        const int cy = (getHeight() - kKeyboardHeight) / 2;

        // Black drop-shadow then yellow GAME OVER on top.
        g.setFont (retroFont (40.0f));
        g.setColour (juce::Colour (0xff2a2a2a));
        g.drawText ("GAME OVER", cx - 400 + 4, cy - 90 + 4, 800, 56, juce::Justification::centred);
        g.setColour (juce::Colour (0xfff2c91f));
        g.drawText ("GAME OVER", cx - 400, cy - 90, 800, 56, juce::Justification::centred);

        g.setColour (juce::Colours::white);
        g.setFont (retroFont (14.0f));
        g.drawText ("SCORE "      + juce::String (score),
                    cx - 300, cy - 20, 600, 22, juce::Justification::centred);
        g.drawText ("BEST COMBO X" + juce::String (comboBest),
                    cx - 300, cy + 8,  600, 22, juce::Justification::centred);
        g.setColour (juce::Colour (0xff4fd5ff));
        g.drawText ("HISCORE "    + juce::String (sessionHighScore),
                    cx - 300, cy + 36, 600, 22, juce::Justification::centred);

        const float pulse = 0.6f + 0.4f * (0.5f + 0.5f * std::sin (globalTime * 3.5f));
        g.setFont (retroFont (14.0f));
        g.setColour (juce::Colour (0xff000000).withAlpha (pulse * 0.7f));
        g.drawText ("PRESS ENTER TO PLAY AGAIN",
                    cx - 400 + 3, cy + 84 + 3, 800, 22, juce::Justification::centred);
        g.setColour (juce::Colour (0xfff2c91f).withAlpha (pulse));
        g.drawText ("PRESS ENTER TO PLAY AGAIN",
                    cx - 400, cy + 84, 800, 22, juce::Justification::centred);

        g.setColour (juce::Colours::white.withAlpha (0.45f));
        g.setFont (retroFont (8.0f));
        g.drawText ("ESC TO EXIT",
                    cx - 300, cy + 116, 600, 16, juce::Justification::centred);
    }
}

void CatGameComponent::drawBoss (juce::Graphics& g, const BossPlugin& b) const
{
    auto centre = juce::Point<float> (b.x + b.w * 0.5f, b.y + b.h * 0.5f);

    // Pulsing red halo
    const float pulse = 0.6f + 0.4f * std::sin (globalTime * 6.0f);
    juce::ColourGradient halo (juce::Colour (0xffe34a3a).withAlpha (0.5f * pulse),
                               centre.x, centre.y,
                               juce::Colour (0x00e34a3a),
                               centre.x + b.w * 0.7f, centre.y,
                               true);
    g.setGradientFill (halo);
    g.fillEllipse (b.x - b.w * 0.2f, b.y - b.h * 0.3f,
                   b.w * 1.4f, b.h * 1.6f);

    {
        juce::Graphics::ScopedSaveState save (g);
        g.addTransform (juce::AffineTransform::rotation (b.rotation, centre.x, centre.y));
        g.setOpacity (1.0f);
        g.setColour (juce::Colours::white);
        if (b.image.isValid())
            g.drawImageWithin (b.image, (int) b.x, (int) b.y, (int) b.w, (int) b.h,
                               juce::RectanglePlacement::centred);
        else
        {
            g.setColour (juce::Colours::lightgrey);
            g.fillRoundedRectangle (b.x, b.y, b.w, b.h, 6.0f);
        }

        // White damage flash
        if (b.hitFlash > 0.05f)
        {
            g.setColour (juce::Colours::white.withAlpha (juce::jlimit (0.0f, 1.0f, b.hitFlash)));
            g.fillRect (b.x, b.y, b.w, b.h);
        }
    }

    // HP bar above the boss
    const float hpRatio = juce::jlimit (0.0f, 1.0f, (float) b.hp / (float) juce::jmax (1, b.maxHp));
    const float barW    = b.w * 0.85f;
    const float barX    = b.x + (b.w - barW) * 0.5f;
    const float barY    = juce::jmax (4.0f, b.y - 14.0f);
    g.setColour (juce::Colours::black.withAlpha (0.55f));
    g.fillRoundedRectangle (barX, barY, barW, 7.0f, 3.5f);
    g.setColour (juce::Colour (0xffe34a3a));
    g.fillRoundedRectangle (barX, barY, barW * hpRatio, 7.0f, 3.5f);
    g.setColour (juce::Colours::white.withAlpha (0.7f));
    g.drawRoundedRectangle (barX, barY, barW, 7.0f, 3.5f, 1.0f);
}

void CatGameComponent::drawPowerup (juce::Graphics& g, const PowerupItem& p) const
{
    const float bob = std::sin (p.bobPhase + globalTime * 4.0f) * 4.0f;
    const float cx  = p.x;
    const float cy  = p.y + bob;
    const float r   = p.size * 0.5f;
    const auto col  = powerColour (p.type);

    juce::Graphics::ScopedSaveState save (g);
    g.addTransform (juce::AffineTransform::rotation (p.rotation, cx, cy));

    // Soft glow
    juce::ColourGradient glow (col.withAlpha (0.55f), cx, cy,
                               col.withAlpha (0.0f),  cx + r * 1.8f, cy, true);
    g.setGradientFill (glow);
    g.fillEllipse (cx - r * 1.8f, cy - r * 1.8f, r * 3.6f, r * 3.6f);

    // Body
    g.setColour (col);
    g.fillEllipse (cx - r, cy - r, r * 2.0f, r * 2.0f);

    // Inner ring
    g.setColour (juce::Colours::white.withAlpha (0.85f));
    g.drawEllipse (cx - r * 0.75f, cy - r * 0.75f, r * 1.5f, r * 1.5f, 1.5f);

    // First-letter glyph in the centre
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (r * 1.1f, juce::Font::bold));
    g.drawText (powerLabel (p.type).substring (0, 1),
                (int) (cx - r), (int) (cy - r * 0.9f),
                (int) (r * 2.0f), (int) (r * 1.8f),
                juce::Justification::centred);
}

void CatGameComponent::drawActivePowerupChips (juce::Graphics& g) const
{
    struct Chip { PowerType type; float secondsLeft; juce::String value; bool indefinite; };
    juce::Array<Chip> chips;
    if (spreadTime  > 0.0f) chips.add ({ PowerType::Spread,  spreadTime,  juce::String (spreadTime,  1) + "s", false });
    if (rapidTime   > 0.0f) chips.add ({ PowerType::Rapid,   rapidTime,   juce::String (rapidTime,   1) + "s", false });
    if (slowTime    > 0.0f) chips.add ({ PowerType::Slow,    slowTime,    juce::String (slowTime,    1) + "s", false });
    if (megaTime    > 0.0f) chips.add ({ PowerType::Mega,    megaTime,    juce::String (megaTime,    1) + "s", false });
    if (shieldStack > 0)    chips.add ({ PowerType::Shield,  0.0f,        "x" + juce::String (shieldStack), true });

    constexpr int chipW = 92;
    constexpr int chipH = 22;
    constexpr int gap   = 6;
    int x = 14;
    const int y = getHeight() - kKeyboardHeight - 50;

    for (auto& c : chips)
    {
        g.setColour (powerColour (c.type).withAlpha (0.85f));
        g.fillRoundedRectangle ((float) x, (float) y, (float) chipW, (float) chipH, 5.0f);
        g.setColour (juce::Colours::white);
        g.setFont (retroFont (8.0f));
        g.drawText (powerLabel (c.type) + " " + c.value,
                    x + 6, y, chipW - 12, chipH, juce::Justification::centredLeft);
        x += chipW + gap;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  MIDI / spawning
// ─────────────────────────────────────────────────────────────────────────────
void CatGameComponent::handleNoteOn (juce::MidiKeyboardState*, int /*midiChannel*/,
                                     int midiNote, float /*velocity*/)
{
    if (midiNote < kFirstNote || midiNote > kLastNote) return;
    juce::MessageManager::callAsync ([this, midiNote]()
    {
        if (state == State::Splash) { state = State::Playing; return; }
        spawnCatHead (midiNote);
    });
}

void CatGameComponent::handleNoteOff (juce::MidiKeyboardState*, int, int, float) {}

void CatGameComponent::spawnCatHead (int midiNote)
{
    if (state != State::Playing) return;
    if (shotCooldownTicks > 0) return;       // enforce reload between shots

    auto rect = keyboard.getRectangleForKey (midiNote);
    if (rect.isEmpty()) return;

    shotCooldownTicks = (rapidTime > 0.0f) ? kRapidShotCooldown : kBaseShotCooldown;

    const float launchX = keyboard.getX() + rect.getCentreX();
    const float launchY = (float) keyboard.getY() - 8.0f;

    const float baseSpeed = rapidTime > 0.0f ? 16.0f : 9.0f;
    const float baseSize  = megaTime  > 0.0f ? 56.0f : 34.0f;

    // Spread fires a centre shot + two angled shots.
    const std::vector<float> sideKicks = (spreadTime > 0.0f)
                                            ? std::vector<float> { -3.5f, 0.0f, 3.5f }
                                            : std::vector<float> { 0.0f };

    for (float vx : sideKicks)
    {
        CatHead h;
        h.x              = launchX;
        h.y              = launchY;
        h.vx             = vx;
        h.vy             = baseSpeed;
        h.size           = baseSize;
        h.rotation       = 0.0f;
        h.spin           = (rng.nextFloat() * 2.0f - 1.0f) * 0.35f;
        h.sourceNote     = midiNote;
        h.headImageIndex = catHeadImages.isEmpty() ? -1
                                                   : rng.nextInt (catHeadImages.size());
        projectiles.add (h);
    }

    postSfx (Sfx::Shoot);
}

void CatGameComponent::spawnFallingPlugin()
{
    if (pluginImagePool.isEmpty() || state != State::Playing)
        return;

    // Difficulty ramps: +12% fall speed every 10 seconds, capped at 2.6x.
    const float secondsIn  = (float) ticksSinceStart / (float) kFps;
    const float speedMul   = juce::jmin (2.6f, 1.0f + secondsIn / 10.0f * 0.12f);

    FallingPlugin p;
    p.image    = pluginImagePool [rng.nextInt (pluginImagePool.size())];
    p.tier     = 0;
    p.w        = 130.0f + rng.nextFloat() * 50.0f;
    p.h        = p.w * 0.6f;
    p.x        = rng.nextFloat() * juce::jmax (1.0f, (float) getWidth() - p.w);
    p.y        = -p.h;
    p.vx       = 0.0f;
    p.vy       = (0.7f + rng.nextFloat() * 1.4f) * speedMul;
    p.rotation = (rng.nextFloat() - 0.5f) * 0.3f;
    p.spin     = (rng.nextFloat() - 0.5f) * 0.025f;
    falling.add (p);
}

void CatGameComponent::spawnSplit (const FallingPlugin& src)
{
    for (int sign : { -1, 1 })
    {
        FallingPlugin p;
        p.image    = src.image;
        p.tier     = 1;
        p.w        = src.w * 0.55f;
        p.h        = src.h * 0.55f;
        p.x        = src.x + src.w * 0.5f - p.w * 0.5f;
        p.y        = src.y + src.h * 0.5f - p.h * 0.5f;
        p.vx       = sign * (1.6f + rng.nextFloat() * 1.4f);
        p.vy       = src.vy * 0.9f + 0.4f;
        p.rotation = src.rotation;
        p.spin     = sign * (0.06f + rng.nextFloat() * 0.06f);
        falling.add (p);
    }
}

void CatGameComponent::spawnBoss()
{
    if (pluginImagePool.isEmpty() || state != State::Playing)
        return;

    // Boss size + HP grow over time. Cap so the late-game doesn't go silly.
    const float secondsIn = (float) ticksSinceStart / (float) kFps;
    const int   wave      = juce::jmin (6, 1 + (int) (secondsIn / 45.0f));
    const int   hp        = 5 + wave * 2;          // wave 1 = 7 HP, wave 6 = 17 HP

    BossPlugin b;
    b.image    = pluginImagePool [rng.nextInt (pluginImagePool.size())];
    b.w        = 260.0f + (float) wave * 18.0f;
    b.h        = b.w * 0.6f;
    b.x        = rng.nextFloat() * juce::jmax (1.0f, (float) getWidth() - b.w);
    b.y        = -b.h;
    b.vx       = (rng.nextFloat() - 0.5f) * 1.2f;
    b.vy       = 0.45f + (float) wave * 0.05f;
    b.rotation = 0.0f;
    b.spin     = (rng.nextFloat() - 0.5f) * 0.012f;
    b.hp       = hp;
    b.maxHp    = hp;
    b.hitFlash = 0.0f;
    bosses.add (b);

    spawnToast ("BOSS INCOMING!", (float) getWidth() * 0.5f, 50.0f,
                juce::Colour (0xffe34a3a), 28.0f);
}

void CatGameComponent::onBossDestroyed (BossPlugin& boss)
{
    const float cx = boss.x + boss.w * 0.5f;
    const float cy = boss.y + boss.h * 0.5f;

    // Big payout. Combo doesn't carry the score here because we already
    // bumped it on every hit; just stack a flat reward.
    const int reward = 250 + boss.maxHp * 20;
    score += reward;
    if (score > sessionHighScore)
    {
        sessionHighScore = score;
        if (settingsManager != nullptr)
            settingsManager->setCatGameHighScore (sessionHighScore);
    }

    spawnExplosion (cx, cy, juce::jmax (boss.w, boss.h) * 1.6f,
                    juce::Colour (0xfff2c91f));
    spawnExplosion (cx + 30.0f, cy + 10.0f, boss.w, juce::Colour (0xffe34a3a));
    spawnExplosion (cx - 30.0f, cy - 10.0f, boss.w, juce::Colour (0xffde7e44));

    spawnToast ("+" + juce::String (reward), cx, cy - 20.0f,
                juce::Colour (0xfff2c91f), 32.0f);

    spawnPowerup (cx, cy);          // guaranteed drop
    postSfx (Sfx::BossKill);
}

void CatGameComponent::spawnPowerup (float cx, float cy)
{
    // Weighted bag: Bomb is the rarest (it's the most game-breaking), Shield
    // sits in the middle, the rest are common. Totals to 14.
    static constexpr PowerType bag[] = {
        PowerType::Spread, PowerType::Spread, PowerType::Spread,
        PowerType::Rapid,  PowerType::Rapid,  PowerType::Rapid,
        PowerType::Slow,   PowerType::Slow,   PowerType::Slow,
        PowerType::Mega,   PowerType::Mega,   PowerType::Mega,
        PowerType::Shield, PowerType::Shield,
        PowerType::Bomb,
    };

    PowerupItem p;
    p.type       = bag [rng.nextInt ((int) (sizeof (bag) / sizeof (bag[0])))];
    p.x          = cx;
    p.y          = cy;
    p.vy         = 1.4f;
    p.rotation   = 0.0f;
    p.spin       = 0.04f;
    p.bobPhase   = rng.nextFloat() * juce::MathConstants<float>::twoPi;
    powerupsOnScreen.add (p);
}

void CatGameComponent::spawnExplosion (float cx, float cy, float size, juce::Colour primary)
{
    Explosion ex;
    ex.cx   = cx;
    ex.cy   = cy;
    ex.size = size;
    explosions.add (ex);

    const int particleCount = 22;
    for (int i = 0; i < particleCount; ++i)
    {
        Particle p;
        const float angle = rng.nextFloat() * juce::MathConstants<float>::twoPi;
        const float speed = 2.5f + rng.nextFloat() * 4.5f;
        p.x      = cx;
        p.y      = cy;
        p.vx     = std::cos (angle) * speed;
        p.vy     = std::sin (angle) * speed;
        p.life   = 1.0f;
        p.decay  = 0.022f + rng.nextFloat() * 0.022f;
        p.size   = 1.5f + rng.nextFloat() * 2.5f;
        p.colour = (i % 3 == 0) ? juce::Colour (0xfff2c91f)
                 : (i % 3 == 1) ? juce::Colour (0xffde7e44)
                                : primary.brighter (0.2f);
        particles.add (p);
    }
}

void CatGameComponent::spawnToast (juce::String text, float cx, float cy, juce::Colour colour, float fontSize)
{
    Toast t;
    t.text     = std::move (text);
    t.x        = cx;
    t.y        = cy;
    t.vy       = -1.6f;
    t.life     = 1.0f;
    t.fontSize = fontSize;
    t.colour   = colour;
    toasts.add (t);
}

void CatGameComponent::applyPowerup (PowerType type, float pickupX, float pickupY)
{
    spawnToast (powerLabel (type) + "!", pickupX, pickupY - 10.0f, powerColour (type), 26.0f);
    postSfx (Sfx::Powerup);

    switch (type)
    {
        case PowerType::Spread: spreadTime = 8.0f; break;
        case PowerType::Rapid:  rapidTime  = 8.0f; break;
        case PowerType::Slow:   slowTime   = 6.0f; break;
        case PowerType::Mega:   megaTime   = 8.0f; break;
        case PowerType::Shield: ++shieldStack; break;
        case PowerType::Bomb:
        {
            // Clear the playfield. Each kill awards a single combo point so
            // we don't carpet-bomb the player to an unearned x20.
            for (auto& p : falling)
            {
                const float cx = p.x + p.w * 0.5f;
                const float cy = p.y + p.h * 0.5f;
                spawnExplosion (cx, cy, juce::jmax (p.w, p.h) * 1.1f, juce::Colour (0xfffff5cc));
                score += 1;
            }
            sessionHighScore = juce::jmax (sessionHighScore, score);
            falling.clearQuick();
            break;
        }
    }
}

void CatGameComponent::registerHit (float cx, float cy, int /*sizeTier*/, int midiNote)
{
    combo     = juce::jmin (kComboCap, combo + 1);
    comboBest = juce::jmax (comboBest, combo);
    score    += combo;

    // Ascending-melody bonus: the player gets +25 per step once they've stacked
    // 3+ consecutive ascending notes that all connected.
    if (midiNote > lastHitNote && lastHitNote >= 0)
        ++ascendingRun;
    else
        ascendingRun = 1;
    lastHitNote = midiNote;

    if (ascendingRun >= 3)
    {
        const int bonus = 25 * (ascendingRun - 2);
        score += bonus;
        spawnToast ("RISING MELODY +" + juce::String (bonus),
                    cx, cy - 26.0f, juce::Colour (0xff7dcfb6), 22.0f);
    }

    if (score > sessionHighScore)
    {
        const bool wasNewBest = (! highScoreCelebrated && score > 0
                                 && sessionHighScore > 0);
        sessionHighScore = score;
        if (settingsManager != nullptr)
            settingsManager->setCatGameHighScore (sessionHighScore);
        if (wasNewBest)
        {
            highScoreCelebrated = true;
            spawnToast ("NEW HIGH SCORE!", (float) getWidth() * 0.5f, 70.0f,
                        juce::Colour (0xfff2c91f), 28.0f);
        }
    }

    spawnExplosion (cx, cy, 90.0f, juce::Colour (0xfffff5cc));
    postSfx (Sfx::Hit);

    // Music-production-themed milestones
    if      (combo == 5)  spawnToast ("ON BEAT!",      cx, cy, juce::Colour (0xff7dcfb6), 26.0f);
    else if (combo == 10) spawnToast ("IN THE POCKET!",cx, cy, juce::Colour (0xfff2c91f), 30.0f);
    else if (combo == 15) spawnToast ("BANGER!",       cx, cy, juce::Colour (0xffde7e44), 34.0f);
    else if (combo == 20) spawnToast ("PLATINUM HIT!", cx, cy, juce::Colour (0xffe34a3a), 40.0f);

    if (rng.nextFloat() < kPowerupDropChance)
        spawnPowerup (cx, cy);
}

void CatGameComponent::onAsteroidEscaped()
{
    if (shieldStack > 0)
    {
        --shieldStack;
        spawnToast ("BLOCKED", (float) getWidth() / 2.0f, 80.0f, juce::Colour (0xff7ed957), 22.0f);
        postSfx (Sfx::ShieldBlock);
        return;
    }
    combo        = 1;
    ascendingRun = 0;
    lastHitNote  = -1;
    ++escaped;
    postSfx (Sfx::LifeLost);
    if (escaped >= kMaxEscapes)
    {
        state = State::GameOver;
        postSfx (Sfx::GameOver);
    }
}

void CatGameComponent::resetGame()
{
    state                = State::Playing;
    score                = 0;
    combo                = 1;
    comboBest            = 1;
    escaped              = 0;
    spawnCountdownTicks  = 60;
    bossCountdownTicks   = 45 * kFps;
    shotCooldownTicks    = 0;
    ticksSinceStart      = 0;
    ascendingRun         = 0;
    lastHitNote          = -1;
    highScoreCelebrated  = false;
    spreadTime = rapidTime = slowTime = megaTime = 0.0f;
    shieldStack = 0;
    falling.clearQuick();
    bosses.clearQuick();
    projectiles.clearQuick();
    powerupsOnScreen.clearQuick();
    explosions.clearQuick();
    particles.clearQuick();
    toasts.clearQuick();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Game loop
// ─────────────────────────────────────────────────────────────────────────────
void CatGameComponent::timerCallback()
{
    const float dt = 1.0f / (float) kFps;
    globalTime    += dt;

    // Always animate visuals so the game-over screen still has movement.
    for (int i = particles.size(); --i >= 0;)
    {
        auto& p = particles.getReference (i);
        p.x    += p.vx;
        p.y    += p.vy;
        p.vy   += 0.12f;
        p.life -= p.decay;
        if (p.life <= 0.0f) particles.remove (i);
    }
    for (int i = explosions.size(); --i >= 0;)
    {
        if (++explosions.getReference (i).ageTicks >= Explosion::lifetime)
            explosions.remove (i);
    }
    for (int i = toasts.size(); --i >= 0;)
    {
        auto& t = toasts.getReference (i);
        t.y    += t.vy;
        t.life -= 0.018f;
        if (t.life <= 0.0f) toasts.remove (i);
    }

    if (state != State::Playing)
    {
        repaint();
        return;
    }

    ++ticksSinceStart;
    if (shotCooldownTicks > 0) --shotCooldownTicks;
    const int playfieldBottom = getHeight() - kKeyboardHeight;
    const float fallMultiplier = (slowTime > 0.0f) ? 0.40f : 1.0f;

    // Spawn cadence accelerates with time. Faster ramp + tighter floor so the
    // late game gets genuinely overwhelming.
    if (--spawnCountdownTicks <= 0)
    {
        spawnFallingPlugin();
        const int floor  = 8;
        const int reduce = ticksSinceStart / (3 * kFps);                       // +1 per 3s
        const int base   = juce::jmax (floor, 55 - reduce);
        spawnCountdownTicks = base + rng.nextInt (juce::jmax (3, 25 - reduce));
    }

    // Boss waves: first ~45s, then every ~35–40s scaling slightly faster.
    if (--bossCountdownTicks <= 0)
    {
        spawnBoss();
        const int floor  = 25 * kFps;
        const int reduce = ticksSinceStart / (15 * kFps);          // -1s per 15s of play
        const int base   = juce::jmax (floor, 40 * kFps - reduce * kFps);
        bossCountdownTicks = base;
    }

    // Tick down active powerup timers
    if (spreadTime > 0.0f) spreadTime = juce::jmax (0.0f, spreadTime - dt);
    if (rapidTime  > 0.0f) rapidTime  = juce::jmax (0.0f, rapidTime  - dt);
    if (slowTime   > 0.0f) slowTime   = juce::jmax (0.0f, slowTime   - dt);
    if (megaTime   > 0.0f) megaTime   = juce::jmax (0.0f, megaTime   - dt);

    // Projectiles
    for (int i = projectiles.size(); --i >= 0;)
    {
        auto& h = projectiles.getReference (i);
        h.x        += h.vx;
        h.y        -= h.vy;
        h.rotation += h.spin;
        if (h.y + h.size < 0.0f || h.x < -h.size || h.x > getWidth() + h.size)
            projectiles.remove (i);
    }

    // Falling asteroids
    for (int i = falling.size(); --i >= 0;)
    {
        auto& p = falling.getReference (i);
        p.x        += p.vx * fallMultiplier;
        p.y        += p.vy * fallMultiplier;
        p.rotation += p.spin;

        if (p.x < 0.0f && p.vx < 0.0f)                       p.vx = -p.vx * 0.6f;
        if (p.x + p.w > (float) getWidth() && p.vx > 0.0f)   p.vx = -p.vx * 0.6f;

        if (p.y > (float) playfieldBottom)
        {
            onAsteroidEscaped();
            falling.remove (i);
        }
    }

    // Bosses
    for (int i = bosses.size(); --i >= 0;)
    {
        auto& b = bosses.getReference (i);
        b.x        += b.vx * fallMultiplier;
        b.y        += b.vy * fallMultiplier;
        b.rotation += b.spin;
        if (b.hitFlash > 0.0f)
            b.hitFlash = juce::jmax (0.0f, b.hitFlash - 0.08f);

        if (b.x < 0.0f && b.vx < 0.0f)                       b.vx = -b.vx;
        if (b.x + b.w > (float) getWidth() && b.vx > 0.0f)   b.vx = -b.vx;

        if (b.y > (float) playfieldBottom)
        {
            // Escaping bosses cost a life regardless of shields - they're a
            // bigger deal than a regular asteroid.
            bosses.remove (i);
            combo        = 1;
            ascendingRun = 0;
            lastHitNote  = -1;
            ++escaped;
            spawnToast ("BOSS ESCAPED!", (float) getWidth() * 0.5f, 80.0f,
                        juce::Colour (0xffe34a3a), 26.0f);
            postSfx (Sfx::LifeLost);
            if (escaped >= kMaxEscapes)
            {
                state = State::GameOver;
                postSfx (Sfx::GameOver);
            }
        }
    }

    // Falling powerup badges
    for (int i = powerupsOnScreen.size(); --i >= 0;)
    {
        auto& p = powerupsOnScreen.getReference (i);
        p.y        += p.vy * fallMultiplier;
        p.rotation += p.spin;
        if (p.y > (float) playfieldBottom + p.size)
            powerupsOnScreen.remove (i);     // missed it - it's just gone
    }

    // Collisions: cat → asteroid, then cat → powerup
    for (int i = projectiles.size(); --i >= 0;)
    {
        auto& h = projectiles.getReference (i);
        const juce::Rectangle<float> headRect (h.x - h.size * 0.4f,
                                               h.y - h.size * 0.4f,
                                               h.size * 0.8f,
                                               h.size * 0.8f);

        bool hit = false;
        for (int j = falling.size(); --j >= 0;)
        {
            auto& p = falling.getReference (j);
            if (! headRect.intersects (juce::Rectangle<float> { p.x, p.y, p.w, p.h }))
                continue;

            const float cx = p.x + p.w * 0.5f;
            const float cy = p.y + p.h * 0.5f;
            const int tierWasBig = (p.tier == 0);

            registerHit (cx, cy, p.tier, h.sourceNote);
            FallingPlugin snapshot = p;
            falling.remove (j);
            if (tierWasBig)
                spawnSplit (snapshot);
            hit = true;
            break;
        }
        if (! hit)
        {
            for (int k = bosses.size(); --k >= 0;)
            {
                auto& b = bosses.getReference (k);
                if (! headRect.intersects (juce::Rectangle<float> { b.x, b.y, b.w, b.h }))
                    continue;

                // Each shot does 1 damage. Combo + melody bonuses still apply
                // (it's still a hit) but split spawning is skipped.
                --b.hp;
                b.hitFlash = 1.0f;
                registerHit (h.x, h.y, 0, h.sourceNote);
                spawnExplosion (h.x, h.y, 36.0f, juce::Colour (0xfff2c91f));
                postSfx (Sfx::BossHit);

                if (b.hp <= 0)
                {
                    BossPlugin snap = b;
                    bosses.remove (k);
                    onBossDestroyed (snap);
                }
                hit = true;
                break;
            }
        }
        if (! hit)
        {
            for (int k = powerupsOnScreen.size(); --k >= 0;)
            {
                auto& pu = powerupsOnScreen.getReference (k);
                const float r = pu.size * 0.55f;
                if (headRect.intersects (juce::Rectangle<float> { pu.x - r, pu.y - r, r * 2.0f, r * 2.0f }))
                {
                    PowerupItem grabbed = pu;
                    powerupsOnScreen.remove (k);
                    applyPowerup (grabbed.type, grabbed.x, grabbed.y);
                    hit = true;
                    break;
                }
            }
        }
        if (hit)
            projectiles.remove (i);
    }

    repaint();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Cat-head drawing (called inside rotation transform)
// ─────────────────────────────────────────────────────────────────────────────
void CatGameComponent::drawCatHead (juce::Graphics& g, juce::Rectangle<float> b) const
{
    const float cx = b.getCentreX();
    const float cy = b.getCentreY();
    const float r  = b.getWidth() * 0.42f;

    juce::Path ears;
    ears.startNewSubPath (cx - r * 0.95f, cy - r * 0.35f);
    ears.lineTo          (cx - r * 0.50f, cy - r * 1.30f);
    ears.lineTo          (cx - r * 0.10f, cy - r * 0.60f);
    ears.closeSubPath();
    ears.startNewSubPath (cx + r * 0.10f, cy - r * 0.60f);
    ears.lineTo          (cx + r * 0.50f, cy - r * 1.30f);
    ears.lineTo          (cx + r * 0.95f, cy - r * 0.35f);
    ears.closeSubPath();

    g.setColour (juce::Colour (0xffde7e44));
    g.fillPath (ears);
    g.fillEllipse (cx - r, cy - r * 0.9f, r * 2.0f, r * 1.8f);

    juce::Path innerEars;
    innerEars.startNewSubPath (cx - r * 0.78f, cy - r * 0.45f);
    innerEars.lineTo          (cx - r * 0.50f, cy - r * 1.05f);
    innerEars.lineTo          (cx - r * 0.22f, cy - r * 0.55f);
    innerEars.closeSubPath();
    innerEars.startNewSubPath (cx + r * 0.22f, cy - r * 0.55f);
    innerEars.lineTo          (cx + r * 0.50f, cy - r * 1.05f);
    innerEars.lineTo          (cx + r * 0.78f, cy - r * 0.45f);
    innerEars.closeSubPath();
    g.setColour (juce::Colour (0xffffc0c8));
    g.fillPath (innerEars);

    g.setColour (juce::Colours::black);
    g.fillEllipse (cx - r * 0.45f - 1.5f, cy - r * 0.18f - 1.5f, 3.0f, 4.0f);
    g.fillEllipse (cx + r * 0.45f - 1.5f, cy - r * 0.18f - 1.5f, 3.0f, 4.0f);

    juce::Path nose;
    nose.addTriangle (cx - r * 0.18f, cy + r * 0.05f,
                      cx + r * 0.18f, cy + r * 0.05f,
                      cx,             cy + r * 0.28f);
    g.setColour (juce::Colour (0xff3d2a20));
    g.fillPath (nose);

    g.setColour (juce::Colour (0xff3d2a20));
    const float wY1 = cy + r * 0.20f;
    const float wY2 = cy + r * 0.36f;
    g.drawLine (cx - r * 0.45f, wY1, cx - r * 1.10f, wY1 - 2.0f, 1.0f);
    g.drawLine (cx - r * 0.45f, wY2, cx - r * 1.10f, wY2 + 2.0f, 1.0f);
    g.drawLine (cx + r * 0.45f, wY1, cx + r * 1.10f, wY1 - 2.0f, 1.0f);
    g.drawLine (cx + r * 0.45f, wY2, cx + r * 1.10f, wY2 + 2.0f, 1.0f);
}

} // namespace PALauncher
