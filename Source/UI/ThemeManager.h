/*
  ==============================================================================
    ThemeManager.h
    Plugin Alliance Launcher - Singleton owning the active theme and a
    listener list for live theme switches.

    Usage:
      const Theme& t = ThemeManager::get().current();
      ThemeManager::get().setTheme (Themes::seventiesTheme);

      class MyComponent : public ThemeManager::Listener {
          MyComponent() { ThemeManager::get().addListener (this); }
          ~MyComponent() { ThemeManager::get().removeListener (this); }
          void themeChanged() override { repaint(); }
      };
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Theme.h"

namespace PALauncher
{

class ThemeManager
{
public:
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void themeChanged() = 0;
    };

    static ThemeManager& get()
    {
        static ThemeManager instance;
        return instance;
    }

    const Theme& current() const { return activeTheme; }

    void setTheme (const Theme& newTheme)
    {
        if (activeTheme.id == newTheme.id)
            return;
        activeTheme = newTheme;
        listeners.call ([](Listener& l) { l.themeChanged(); });
    }

    // Look up a built-in theme by id; returns the default if id is unknown.
    const Theme& findById (const juce::String& id) const
    {
        if (id == Themes::seventiesTheme.id) return Themes::seventiesTheme;
        return Themes::defaultTheme;
    }

    void setThemeById (const juce::String& id) { setTheme (findById (id)); }

    void addListener (Listener* l)    { listeners.add (l); }
    void removeListener (Listener* l) { listeners.remove (l); }

private:
    ThemeManager() = default;

    Theme activeTheme = Themes::defaultTheme;
    juce::ListenerList<Listener> listeners;

    JUCE_DECLARE_NON_COPYABLE (ThemeManager)
};

} // namespace PALauncher
