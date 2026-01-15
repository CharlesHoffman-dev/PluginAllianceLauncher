/*
  ==============================================================================
    EraFilter.cpp
    Plugin Alliance Launcher - Era/Decade Filter Component Implementation
  ==============================================================================
*/

#include "EraFilter.h"

namespace PALauncher
{

EraFilter::EraFilter()
{
    titleLabel.setText("ERA", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xff888888));
    addAndMakeVisible(titleLabel);

    buildEraList();

    listBox.setModel(this);
    listBox.setRowHeight(26);
    listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(listBox);

    listBox.selectRow(0);
}

void EraFilter::buildEraList()
{
    eras.clear();

    // All eras option (represented by Era_Unknown as "any")
    eras.push_back({Era::Era_Unknown, "All Eras"});

    // Digital plugins (not based on hardware) - at top for easy access
    eras.push_back({Era::Era_Modern, "Digital"});

    // Historical eras (hardware emulations only)
    eras.push_back({Era::Era_1950s, "1950s"});
    eras.push_back({Era::Era_1960s, "1960s"});
    eras.push_back({Era::Era_1970s, "1970s"});
    eras.push_back({Era::Era_1980s, "1980s"});
    eras.push_back({Era::Era_1990s, "1990s"});
    eras.push_back({Era::Era_2000s, "2000s"});
    eras.push_back({Era::Era_2010s, "2010s"});
    eras.push_back({Era::Era_2020s, "2020s"});
}

void EraFilter::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff121212));
}

void EraFilter::resized()
{
    auto bounds = getLocalBounds().reduced(4);

    titleLabel.setBounds(bounds.removeFromTop(20));

    // Draw separator
    bounds.removeFromTop(4);

    listBox.setBounds(bounds);
}

int EraFilter::getNumRows()
{
    return static_cast<int>(eras.size());
}

void EraFilter::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowNumber < 0 || rowNumber >= static_cast<int>(eras.size()))
        return;

    const auto& item = eras[rowNumber];

    if (rowIsSelected)
    {
        g.setColour(juce::Colour(0xff0cbff2));
        g.fillRoundedRectangle(2.0f, 1.0f, width - 4.0f, height - 2.0f, 3.0f);
    }

    g.setColour(rowIsSelected ? juce::Colours::white : juce::Colour(0xfff9f9f9));
    g.setFont(juce::Font(14.0f));
    g.drawText(item.name, 8, 0, width - 16, height, juce::Justification::centredLeft);
}

void EraFilter::listBoxItemClicked(int row, const juce::MouseEvent&)
{
    if (row < 0 || row >= static_cast<int>(eras.size()))
        return;

    selectedRow = row;

    if (onEraChanged)
        onEraChanged(eras[row].era);
}

Era EraFilter::getSelectedEra() const
{
    if (selectedRow >= 0 && selectedRow < static_cast<int>(eras.size()))
        return eras[selectedRow].era;
    return Era::Era_Unknown;
}

} // namespace PALauncher
