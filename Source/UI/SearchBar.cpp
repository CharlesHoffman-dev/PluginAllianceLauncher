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
    // Configure search icon (using magnifying glass character)
    searchIcon.setText(juce::CharPointer_UTF8("\xf0\x9f\x94\x8d"), juce::dontSendNotification);
    searchIcon.setFont(juce::Font(16.0f));
    searchIcon.setColour(juce::Label::textColourId, juce::Colours::grey);
    searchIcon.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(searchIcon);

    // Configure search field
    searchField.setMultiLine(false);
    searchField.setReturnKeyStartsNewLine(false);
    searchField.setScrollbarsShown(false);
    searchField.setCaretVisible(true);
    searchField.setPopupMenuEnabled(true);
    searchField.setTextToShowWhenEmpty("Search plugins...", juce::Colour(0xff888888));
    searchField.setFont(juce::Font(14.0f));
    searchField.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff1a1a1a));
    searchField.setColour(juce::TextEditor::textColourId, juce::Colours::white);
    searchField.setColour(juce::TextEditor::outlineColourId, juce::Colour(0xff2a2a2a));
    searchField.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour(0xff0cbff2));
    searchField.addListener(this);
    addAndMakeVisible(searchField);
}

void SearchBar::paint(juce::Graphics& g)
{
    g.setColour(juce::Colour(0xff1a1a1a));
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 6.0f);
}

void SearchBar::resized()
{
    auto bounds = getLocalBounds().reduced(4);

    searchIcon.setBounds(bounds.removeFromLeft(30));
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
