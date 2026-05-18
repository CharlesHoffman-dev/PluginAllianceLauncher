/*
  ==============================================================================
    CatGameComponent.h
    Plugin Alliance Launcher - "ilovecats" easter-egg game.

    Asteroid-shooter where the player launches spinning cat heads from a
    4-octave on-screen MIDI keyboard at plugin thumbnails falling from the
    sky. Includes a combo system, screen shake, particle bursts, splitting
    asteroids, lives, game-over restart, and a powerup-drop system.

    Powerups (drop ~12% of kills, picked up by shooting them):
      SPREAD  — 3-shot fan for 8 s
      RAPID   — cats travel 2× faster for 8 s
      BOMB    — instant: destroys every asteroid on screen
      SHIELD  — stacking, absorbs one escape each
      SLOW    — falling asteroids slow to 40% for 6 s
      MEGA    — cats fire at 2× size for 8 s
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

class SettingsManager;

class CatGameComponent : public juce::Component,
                         public juce::MidiKeyboardState::Listener,
                         private juce::Timer
{
public:
    CatGameComponent (juce::MidiKeyboardState& sharedKeyboardState,
                      SettingsManager* settings);
    ~CatGameComponent() override;

    // Audio-side SFX trigger. The editor sets this so MIDI-thread hits can
    // ask the processor to play a synthesized cue. Triggered from the game
    // thread; the processor side must be lock-free and audio-safe.
    enum class Sfx { Shoot, Hit, Powerup, BossHit, BossKill, ShieldBlock, LifeLost, GameOver };
    std::function<void (Sfx)> onSfxRequested;

    void paint (juce::Graphics&) override;
    void resized() override;

    std::function<void()> onExitRequested;

    bool keyPressed (const juce::KeyPress&) override;

    void handleNoteOn  (juce::MidiKeyboardState*, int midiChannel, int midiNote, float velocity) override;
    void handleNoteOff (juce::MidiKeyboardState*, int midiChannel, int midiNote, float velocity) override;

private:
    enum class State { Splash, Playing, GameOver };
    enum class PowerType { Spread, Rapid, Bomb, Shield, Slow, Mega };

    struct CatHead
    {
        float x, y;
        float vx, vy;
        float size;
        float rotation;
        float spin;
        int   sourceNote;     // MIDI note that fired this shot (for melody bonus)
        int   headImageIndex; // -1 = procedural draw; otherwise index into catHeadImages
    };

    struct FallingPlugin
    {
        juce::Image image;
        float x, y;
        float w, h;
        float vx, vy;
        float rotation;
        float spin;
        int tier;
    };

    struct BossPlugin
    {
        juce::Image image;
        float x, y;
        float w, h;
        float vx, vy;
        float rotation;
        float spin;
        int   hp;
        int   maxHp;
        float hitFlash;      // 0..1 white-flash after a hit
    };

    struct PowerupItem
    {
        PowerType type;
        float x, y;
        float vy;
        float rotation;
        float spin;
        float bobPhase;
        float size = 36.0f;
    };

    struct Particle
    {
        float x, y;
        float vx, vy;
        juce::Colour colour;
        float life;
        float decay;
        float size;
    };

    struct Explosion
    {
        float cx, cy;
        float size;
        int   ageTicks = 0;
        static constexpr int lifetime = 14;
    };

    struct Toast
    {
        juce::String text;
        float x, y;
        float vy;
        float life;          // 1 → 0
        float fontSize;
        juce::Colour colour;
    };

    struct Star
    {
        float x, y;
        float radius;
        juce::Colour colour;
        bool twinkles;
        float twinklePhase;
    };

    struct Nebula
    {
        float cx, cy;
        float radius;
        juce::Colour colour;
    };

    void timerCallback() override;
    void spawnCatHead (int midiNote);
    void spawnFallingPlugin();
    void spawnSplit (const FallingPlugin& source);
    void spawnPowerup (float cx, float cy);
    void spawnExplosion (float cx, float cy, float size, juce::Colour primary);
    void spawnToast (juce::String text, float cx, float cy, juce::Colour colour, float fontSize = 22.0f);
    void spawnBoss();
    void onAsteroidEscaped();
    void registerHit (float cx, float cy, int sizeTier, int midiNote);
    void onBossDestroyed (BossPlugin& boss);
    void applyPowerup (PowerType type, float pickupX, float pickupY);
    void resetGame();
    void buildStarfield();
    void postSfx (Sfx s) const;
    void drawCatHead   (juce::Graphics& g, juce::Rectangle<float> bounds) const;
    void drawPowerup   (juce::Graphics& g, const PowerupItem& p) const;
    void drawBoss      (juce::Graphics& g, const BossPlugin& b) const;
    void drawActivePowerupChips (juce::Graphics& g) const;

    static juce::Colour    powerColour (PowerType);
    static juce::String    powerLabel  (PowerType);

    juce::Font retroFont (float height, int styleFlags = 0) const;

    juce::MidiKeyboardState& kbState;
    SettingsManager* settingsManager = nullptr;
    juce::MidiKeyboardComponent keyboard;
    juce::Array<juce::Image> pluginImagePool;
    juce::Array<juce::Image> catHeadImages;     // pre-scaled cat-head sprites
    juce::Image              splashCatImage;    // sphynx, mascot for the splash screen
    juce::Array<juce::Image> splashHeads;       // three distinct heads shown on splash
    juce::Image              backdropCache;     // static stars + nebulas + gradient, rebuilt on resize
    juce::Typeface::Ptr      retroTypeface;     // pixel font (Press Start 2P) used everywhere in-game

    juce::Array<CatHead> projectiles;
    juce::Array<FallingPlugin> falling;
    juce::Array<BossPlugin> bosses;
    juce::Array<PowerupItem> powerupsOnScreen;
    juce::Array<Explosion> explosions;
    juce::Array<Particle> particles;
    juce::Array<Toast> toasts;

    juce::Array<Star> stars;
    juce::Array<Nebula> nebulas;

    juce::Random rng { (juce::int64) juce::Time::currentTimeMillis() };

    State state = State::Splash;

    int   spawnCountdownTicks = 60;
    int   bossCountdownTicks  = 45 * 60;   // first boss ~45s in
    int   shotCooldownTicks   = 0;         // gates spawnCatHead; ticks down each frame
    int   ticksSinceStart     = 0;
    int   score               = 0;
    int   combo               = 1;
    int   comboBest           = 1;
    int   escaped             = 0;
    int   sessionHighScore    = 0;
    bool  highScoreCelebrated = false;     // toast only when newly beaten

    // Ascending-melody bonus: rewards the player for actually playing scales
    // up the keyboard. Reset on missed hit / descending note.
    int   lastHitNote     = -1;
    int   ascendingRun    = 0;

    float globalTime     = 0.0f;

    // Active powerup state. Float = seconds remaining (timed); shields stack.
    float spreadTime = 0.0f;
    float rapidTime  = 0.0f;
    float slowTime   = 0.0f;
    float megaTime   = 0.0f;
    int   shieldStack = 0;

    static constexpr int   kFirstNote        = 36;     // C2
    static constexpr int   kLastNote         = 83;     // B5  → 4 octaves, no trailing C
    static constexpr int   kKeyboardHeight   = 100;
    static constexpr int   kFps              = 60;
    static constexpr int   kMaxEscapes       = 9;
    static constexpr int   kComboCap         = 20;
    static constexpr float kPowerupDropChance= 0.05f;
    // Shot cooldown: ~165ms baseline, ~80ms under Rapid powerup.
    static constexpr int   kBaseShotCooldown = 10;     // ticks @ 60fps
    static constexpr int   kRapidShotCooldown= 5;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CatGameComponent)
};

} // namespace PALauncher
