/*
  ==============================================================================
    SearchBar.h
    Plugin Alliance Launcher - Search Input Component
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

class SearchBar : public juce::Component,
                  public juce::TextEditor::Listener
{
public:
    SearchBar();
    ~SearchBar() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseMove(const juce::MouseEvent& e) override;

    // Get current search text
    juce::String getSearchText() const;

    // Clear search
    void clear();

    // Listener callback
    std::function<void(const juce::String&)> onSearchChanged;

private:
    void textEditorTextChanged(juce::TextEditor&) override;
    void textEditorReturnKeyPressed(juce::TextEditor&) override;
    void textEditorEscapeKeyPressed(juce::TextEditor&) override;

    bool isOverClearButton(const juce::Point<int>& pos) const;

    juce::TextEditor searchField;
    bool hasText = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SearchBar)
};

} // namespace PALauncher
