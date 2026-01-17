/*
  ==============================================================================
    CategoryFilter.cpp
    Plugin Alliance Launcher - Category Filter Sidebar Implementation
  ==============================================================================
*/

#include "CategoryFilter.h"

namespace PALauncher
{

CategoryFilter::CategoryFilter()
{
    buildCategoryList();

    listBox.setModel(this);
    listBox.setRowHeight(30);
    listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(listBox);

    listBox.selectRow(0);
}

void CategoryFilter::buildCategoryList()
{
    categories.clear();

    // Special categories at top
    categories.push_back({DisplayCategory::All, "All Plugins", false});
    categories.push_back({DisplayCategory::Favorites, "Favorites", false});
    categories.push_back({DisplayCategory::Recent, "Recent", false});

    // Instruments header (above Effects)
    categories.push_back({DisplayCategory::All, "INSTRUMENTS", true});

    // Only Synths - Plugin Alliance only has synth instruments
    categories.push_back({DisplayCategory::Inst_Synths, "Synthesizers", false});

    // Effects header
    categories.push_back({DisplayCategory::All, "EFFECTS", true});

    // Effect categories (user-defined order)
    categories.push_back({DisplayCategory::GuitarBass, "Amp Simulators", false});
    categories.push_back({DisplayCategory::ChannelStrip, "Channel Strips", false});
    categories.push_back({DisplayCategory::Equalization, "Equalizers", false});
    categories.push_back({DisplayCategory::Dynamics, "Compressors", false});
    categories.push_back({DisplayCategory::Saturation, "Saturators", false});
    categories.push_back({DisplayCategory::Delays, "Delays", false});
    categories.push_back({DisplayCategory::Reverbs, "Reverbs", false});
    categories.push_back({DisplayCategory::Meters, "Meters", false});
    categories.push_back({DisplayCategory::SpecialProcessing, "Other", false});
}

void CategoryFilter::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff121212));
}

void CategoryFilter::resized()
{
    listBox.setBounds(getLocalBounds().reduced(4));
}

int CategoryFilter::getNumRows()
{
    return static_cast<int>(categories.size());
}

void CategoryFilter::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowNumber < 0 || rowNumber >= static_cast<int>(categories.size()))
        return;

    const auto& item = categories[rowNumber];

    if (item.isHeader)
    {
        // Draw header style - grey background with white text
        g.setColour(juce::Colour(0xff2a2a2a));
        g.fillRect(4, 2, width - 8, height - 4);

        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(12.0f, juce::Font::bold));
        g.drawText(item.name, 12, 0, width - 24, height, juce::Justification::centredLeft);
    }
    else
    {
        // Draw item style
        if (rowIsSelected)
        {
            g.setColour(juce::Colour(0xff0cbff2));
            g.fillRoundedRectangle(4.0f, 2.0f, width - 8.0f, height - 4.0f, 4.0f);
        }

        g.setColour(rowIsSelected ? juce::Colours::white : juce::Colour(0xfff9f9f9));
        g.setFont(juce::Font(14.0f));

        // Consistent indent for all items
        g.drawText(item.name, 8, 0, width - 16, height, juce::Justification::centredLeft);
    }
}

void CategoryFilter::listBoxItemClicked(int row, const juce::MouseEvent&)
{
    if (row < 0 || row >= static_cast<int>(categories.size()))
        return;

    // Don't select headers
    if (categories[row].isHeader)
    {
        listBox.selectRow(selectedRow);
        return;
    }

    selectedRow = row;

    if (onCategoryChanged)
        onCategoryChanged(categories[row].category);
}

DisplayCategory CategoryFilter::getSelectedCategory() const
{
    if (selectedRow >= 0 && selectedRow < static_cast<int>(categories.size()))
        return categories[selectedRow].category;
    return DisplayCategory::All;
}

} // namespace PALauncher
