/*
  ==============================================================================
    GameSfxEngine.h
    Sample-based SFX + looping background music for the easter-egg game.
    Triggered from the UI thread; rendered from the audio thread; sums into the
    plugin's output buffer.

    Resources live in Resources/GameSounds/*.wav. Loaded lazily the first time
    loadResourcesIfNeeded() is called (when the player enters the game).
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <atomic>
#include <array>
#include <vector>
#include <memory>

namespace PALauncher
{

class GameSfxEngine
{
public:
    enum class Sound { Shoot, Hit, Powerup, BossHit, BossKill, ShieldBlock, LifeLost, GameOver };

    GameSfxEngine() = default;

    void prepare (double sr)
    {
        sampleRate = sr > 0.0 ? sr : 44100.0;
        for (auto& v : voices) v.active = false;
        musicPosition = 0;
        pendingRead.store (0, std::memory_order_relaxed);
        pendingWrite.store (0, std::memory_order_relaxed);
    }

    // Called from the message thread (game entry). Idempotent and fast on
    // subsequent calls. Returns false if no resources directory was found.
    bool loadResourcesIfNeeded()
    {
        if (resourcesLoaded) return true;

        const juce::File dir = findResourcesDir();
        if (! dir.isDirectory()) return false;

        juce::AudioFormatManager fm;
        fm.registerBasicFormats();

        auto load = [&] (const juce::String& fileName) -> juce::AudioBuffer<float>*
        {
            auto f = dir.getChildFile (fileName);
            if (! f.existsAsFile()) return nullptr;
            std::unique_ptr<juce::AudioFormatReader> reader (fm.createReaderFor (f));
            if (reader == nullptr) return nullptr;

            auto buf = std::make_unique<juce::AudioBuffer<float>> (1, (int) reader->lengthInSamples);
            reader->read (buf.get(), 0, (int) reader->lengthInSamples, 0, true, false);
            auto* raw = buf.get();
            sourceSampleRate = reader->sampleRate;
            sampleStorage.push_back (std::move (buf));
            return raw;
        };

        auto addVariants = [&] (Sound s, std::initializer_list<juce::String> files)
        {
            auto& bank = banks[(int) s];
            for (auto& fn : files)
                if (auto* b = load (fn))
                    bank.variants.push_back (b);
        };

        addVariants (Sound::Shoot,       { "cat-1.wav", "cat-2.wav", "cat-3.wav", "cat-4.wav", "cat-5.wav" });
        addVariants (Sound::Hit,         { "explode-1.wav", "explode-2.wav", "explode-3.wav", "explode-4.wav" });
        addVariants (Sound::Powerup,     { "powerup-1.wav", "powerup-2.wav", "powerup-3.wav", "powerup-4.wav" });
        addVariants (Sound::BossHit,     { "explode-1.wav", "explode-2.wav" });    // reuse explosions
        addVariants (Sound::BossKill,    { "boss-kill.wav" });
        addVariants (Sound::ShieldBlock, { "shield-impact.wav" });
        addVariants (Sound::LifeLost,    { "health-damage.wav" });
        addVariants (Sound::GameOver,    { "game-over.wav" });

        if (auto* m = load ("background-music.wav"))
            musicBuffer = m;

        resourcesLoaded = true;
        return true;
    }

    // Safe to call from any thread. Drops if queue full.
    void trigger (Sound s)
    {
        const int w    = pendingWrite.load (std::memory_order_relaxed);
        const int next = (w + 1) % kPendingCap;
        if (next == pendingRead.load (std::memory_order_acquire))
            return;
        pending[w] = (uint8_t) s;
        pendingWrite.store (next, std::memory_order_release);
    }

    // Loop background music until stopMusic() is called.
    void startMusic() { musicShouldPlay.store (true,  std::memory_order_release); }
    void stopMusic()  { musicShouldPlay.store (false, std::memory_order_release); }

    // Audio-thread render: drains pending triggers, allocates voices, sums all
    // active voices + music into the buffer.
    void renderInto (juce::AudioBuffer<float>& buffer)
    {
        int r = pendingRead.load (std::memory_order_relaxed);
        const int w = pendingWrite.load (std::memory_order_acquire);
        while (r != w)
        {
            allocVoice ((Sound) pending[r]);
            r = (r + 1) % kPendingCap;
        }
        pendingRead.store (r, std::memory_order_release);

        const int numSamples  = buffer.getNumSamples();
        const int numChannels = buffer.getNumChannels();
        if (numSamples <= 0 || numChannels <= 0) return;

        const bool wantMusic = musicShouldPlay.load (std::memory_order_acquire) && musicBuffer != nullptr;
        bool anyActive = wantMusic;
        if (! anyActive)
            for (auto& v : voices) if (v.active) { anyActive = true; break; }
        if (! anyActive) return;

        float* const* writePtrs = buffer.getArrayOfWritePointers();
        if (writePtrs == nullptr) return;

        const float pitchRatio = (sourceSampleRate > 0.0) ? (float) (sourceSampleRate / sampleRate) : 1.0f;

        for (int n = 0; n < numSamples; ++n)
        {
            float mix = 0.0f;

            // SFX voices
            for (auto& v : voices)
            {
                if (! v.active) continue;
                const auto* src = v.buffer->getReadPointer (0);
                const int len   = v.buffer->getNumSamples();
                const float pos = v.position;
                const int   i0  = (int) pos;
                if (i0 >= len - 1) { v.active = false; continue; }
                const float frac = pos - (float) i0;
                const float s    = src[i0] + frac * (src[i0 + 1] - src[i0]);
                mix += s * v.gain;
                v.position += pitchRatio;
            }

            // Background music (quieter)
            if (wantMusic)
            {
                const auto* src = musicBuffer->getReadPointer (0);
                const int len   = musicBuffer->getNumSamples();
                if (len > 1)
                {
                    const float pos = (float) musicPosition;
                    const int   i0  = (int) pos;
                    const float frac = pos - (float) i0;
                    const int   i1  = (i0 + 1) % len;
                    const float s    = src[i0] + frac * (src[i1] - src[i0]);
                    mix += s * kMusicGain;
                    musicPosition = (int) (pos + pitchRatio);
                    if (musicPosition >= len) musicPosition -= len;
                }
            }

            mix = juce::jlimit (-1.0f, 1.0f, mix);
            for (int c = 0; c < numChannels; ++c)
                if (writePtrs[c] != nullptr)
                    writePtrs[c][n] += mix;
        }
    }

private:
    static constexpr int   kPendingCap = 32;
    static constexpr int   kMaxVoices  = 16;
    static constexpr float kMusicGain  = 0.20f;     // background music sits well below FX
    static constexpr float kSfxGain    = 0.85f;

    struct Voice
    {
        bool   active = false;
        const juce::AudioBuffer<float>* buffer = nullptr;
        float  position = 0.0f;
        float  gain     = 1.0f;
    };

    struct SoundBank
    {
        std::vector<const juce::AudioBuffer<float>*> variants;
    };

    Voice voices[kMaxVoices];
    std::array<SoundBank, 8> banks;
    std::vector<std::unique_ptr<juce::AudioBuffer<float>>> sampleStorage;
    const juce::AudioBuffer<float>* musicBuffer = nullptr;
    bool   resourcesLoaded = false;
    double sourceSampleRate = 44100.0;

    uint8_t pending[kPendingCap]{};
    std::atomic<int> pendingRead  { 0 };
    std::atomic<int> pendingWrite { 0 };
    std::atomic<bool> musicShouldPlay { false };
    int    musicPosition = 0;
    double sampleRate = 44100.0;

    juce::Random rng { (juce::int64) juce::Time::currentTimeMillis() };

    void allocVoice (Sound s)
    {
        auto& bank = banks[(int) s];
        if (bank.variants.empty()) return;
        const auto* buf = bank.variants[rng.nextInt ((int) bank.variants.size())];
        if (buf == nullptr) return;

        Voice* victim = nullptr;
        for (auto& v : voices)
            if (! v.active) { victim = &v; break; }
        if (victim == nullptr) victim = &voices[0];     // steal slot 0

        victim->active   = true;
        victim->buffer   = buf;
        victim->position = 0.0f;
        victim->gain     = kSfxGain;
    }

    static juce::File findResourcesDir()
    {
        const juce::File candidates[] = {
            juce::File::getSpecialLocation (juce::File::currentExecutableFile)
                .getParentDirectory().getChildFile ("Resources/GameSounds"),
            juce::File ("C:/Users/charl/PluginAllianceLauncher/Resources/GameSounds"),
        };
        for (auto& f : candidates)
            if (f.isDirectory()) return f;
        return {};
    }
};

} // namespace PALauncher
