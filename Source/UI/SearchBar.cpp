/*
  ==============================================================================
    SearchBar.cpp
    Plugin Alliance Launcher - Search Input Component Implementation
  ==============================================================================
*/

#include "SearchBar.h"
#include "Colors.h"

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
    searchField.setTextToShowWhenEmpty("Search plugins...", Colors::textMuted());
    searchField.setFont(juce::Font(14.0f));
    searchField.setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentBlack);
    searchField.setColour(juce::TextEditor::textColourId, Colors::textOnLight());
    searchField.setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentBlack);
    searchField.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colours::transparentBlack);
    searchField.setColour(juce::TextEditor::highlightColourId, Colors::accent());
    searchField.setColour(juce::TextEditor::highlightedTextColourId, Colors::cardBackground());
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

    // Background - white
    g.setColour(Colors::cardBackground());
    g.fillRoundedRectangle(bounds, 6.0f);

    // Subtle grey outline
    g.setColour(Colors::textPlaceholder());
    g.drawRoundedRectangle(bounds.reduced(0.5f), 6.0f, 1.0f);

    // Draw icon on right side - X if has text, magnifying glass otherwise
    auto iconBounds = getLocalBounds().removeFromRight(36).reduced(10).toFloat();
    float cx = iconBounds.getCentreX();
    float cy = iconBounds.getCentreY();

    if (hasText)
    {
        // Draw X (clear button)
        g.setColour(Colors::textDisabled());
        float size = 6.0f;
        g.drawLine(cx - size, cy - size, cx + size, cy + size, 2.0f);
        g.drawLine(cx + size, cy - size, cx - size, cy + size, 2.0f);
    }
    else
    {
        // Draw magnifying glass icon
        float radius = 6.0f;
        g.setColour(Colors::textMuted());

        // Draw circle (lens)
        g.drawEllipse(cx - radius - 2, cy - radius - 2, radius * 2, radius * 2, 2.0f);

        // Draw handle
        float handleStartX = cx + radius * 0.4f;
        float handleStartY = cy + radius * 0.4f;
        float handleEndX = cx + radius + 4;
        float handleEndY = cy + radius + 4;
        g.drawLine(handleStartX, handleStartY, handleEndX, handleEndY, 2.0f);
    }
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
    hasText = false;
    repaint();
}

void SearchBar::textEditorTextChanged(juce::TextEditor&)
{
    bool hadText = hasText;
    hasText = searchField.getText().isNotEmpty();

    if (hadText != hasText)
        repaint();  // Redraw icon

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

bool SearchBar::isOverClearButton(const juce::Point<int>& pos) const
{
    auto iconBounds = getLocalBounds().removeFromRight(36);
    return iconBounds.contains(pos);
}

void SearchBar::mouseDown(const juce::MouseEvent& e)
{
    if (hasText && isOverClearButton(e.getPosition()))
    {
        clear();
        if (onSearchChanged)
            onSearchChanged("");
    }
}

void SearchBar::mouseMove(const juce::MouseEvent& e)
{
    if (hasText && isOverClearButton(e.getPosition()))
        setMouseCursor(juce::MouseCursor::PointingHandCursor);
    else
        setMouseCursor(juce::MouseCursor::IBeamCursor);
}

} // namespace PALauncher
