/*
  ==============================================================================
    SearchBar.cpp
    Plugin Alliance Launcher - Search Input Component Implementation
  ==============================================================================
*/

#include "SearchBar.h"

namespace PALauncher
{

SearchBar::SearchBar()
{
    // Configure search field
    searchField.setMultiLine(false);
    searchField.setReturnKeyStartsNewLine(false);
    searchField.setScrollbarsShown(false);
    searchField.setCaretVisible(true);
    searchField.setPopupMenuEnabled(true);
    searchField.setTextToShowWhenEmpty("Search plugins...", juce::Colour(0xff888888));
    searchField.setFont(juce::Font(14.0f));
    searchField.setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentBlack);
    searchField.setColour(juce::TextEditor::textColourId, juce::Colours::white);
    searchField.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
    searchField.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::transparentBlack);
    searchField.setWantsKeyboardFocus(true);
    searchField.setMouseClickGrabsKeyboardFocus(true);  // Only grab focus when clicking directly on it
    searchField.addListener(this);
    addAndMakeVisible(searchField);

    // Prevent the SearchBar component itself from grabbing focus
    setWantsKeyboardFocus(false);
    setMouseClickGrabsKeyboardFocus(false);
}

void SearchBar::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Background
    g.setColour(juce::Colour(0xff1a1a1a));
    g.fillRoundedRectangle(bounds, 6.0f);

    // White outline
    g.setColour(juce::Colours::white);
    g.drawRoundedRectangle(bounds.reduced(0.5f), 6.0f, 1.0f);

    // Draw magnifying glass icon on right side
    auto iconBounds = getLocalBounds().removeFromRight(36).reduced(10).toFloat();
    float cx = iconBounds.getCentreX();
    float cy = iconBounds.getCentreY();
    float radius = 6.0f;

    g.setColour(juce::Colour(0xff888888));

    // Draw circle (lens)
    g.drawEllipse(cx - radius - 2, cy - radius - 2, radius * 2, radius * 2, 2.0f);

    // Draw handle
    float handleStartX = cx + radius * 0.4f;
    float handleStartY = cy + radius * 0.4f;
    float handleEndX = cx + radius + 4;
    float handleEndY = cy + radius + 4;
    g.drawLine(handleStartX, handleStartY, handleEndX, handleEndY, 2.0f);
}

void SearchBar::resized()
{
    auto bounds = getLocalBounds().reduced(8, 4);
    bounds.removeFromRight(32);  // Space for search icon drawn in paint()
    searchField.setBounds(bounds);
}

juce::String SearchBar::getSearchText() const
{
    return searchField.getText();
}

void SearchBar::clear()
{
    searchField.clear();
}

void SearchBar::textEditorTextChanged(juce::TextEditor&)
{
    if (onSearchChanged)
        onSearchChanged(searchField.getText());
}

void SearchBar::textEditorReturnKeyPressed(juce::TextEditor&)
{
    // Optionally trigger search on enter
    if (onSearchChanged)
        onSearchChanged(searchField.getText());
}

void SearchBar::textEditorEscapeKeyPressed(juce::TextEditor&)
{
    clear();
    if (onSearchChanged)
        onSearchChanged("");
}

} // namespace PALauncher
