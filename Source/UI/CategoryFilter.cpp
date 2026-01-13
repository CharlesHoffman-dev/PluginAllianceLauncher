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
    listBox.setRowHeight(28);
    listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(listBox);

    listBox.selectRow(0);
}

void CategoryFilter::buildCategoryList()
{
    categories.clear();

    // All plugins
    categories.push_back({DisplayCategory::All, "All Plugins", false});
    categories.push_back({DisplayCategory::Favorites, "Favorites", false});
    categories.push_back({DisplayCategory::Recent, "Recent", false});

    // Effects header
    categories.push_back({DisplayCategory::All, "EFFECTS", true});

    // Effect categories
    categories.push_back({DisplayCategory::EQ, "EQ", false});
    categories.push_back({DisplayCategory::Dynamics, "Dynamics", false});
    categories.push_back({DisplayCategory::Reverb, "Reverb", false});
    categories.push_back({DisplayCategory::Delay, "Delay", false});
    categories.push_back({DisplayCategory::Modulation, "Modulation", false});
    categories.push_back({DisplayCategory::Distortion, "Distortion", false});
    categories.push_back({DisplayCategory::Saturation, "Saturation", false});
    categories.push_back({DisplayCategory::AmpSim, "Amp Simulators", false});
    categories.push_back({DisplayCategory::ChannelStrip, "Channel Strips", false});
    categories.push_back({DisplayCategory::Mastering, "Mastering", false});
    categories.push_back({DisplayCategory::Pitch, "Pitch", false});
    categories.push_back({DisplayCategory::StereoImaging, "Stereo/Width", false});
    categories.push_back({DisplayCategory::Vocal, "Vocal", false});
    categories.push_back({DisplayCategory::Metering, "Metering", false});
    categories.push_back({DisplayCategory::Creative, "Creative FX", false});
    categories.push_back({DisplayCategory::Utility, "Utility", false});

    // Instruments header
    categories.push_back({DisplayCategory::All, "INSTRUMENTS", true});

    // Instrument categories
    categories.push_back({DisplayCategory::Synth, "Synths", false});
    categories.push_back({DisplayCategory::Drums, "Drums", false});
    categories.push_back({DisplayCategory::Sampler, "Samplers", false});
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
        // Draw header style
        g.setColour(juce::Colour(0xff888888));
        g.setFont(juce::Font(11.0f, juce::Font::bold));
        g.drawText(item.name, 8, 0, width - 16, height, juce::Justification::centredLeft);

        // Draw separator line below
        g.setColour(juce::Colour(0xff2a2a2a));
        g.drawHorizontalLine(height - 1, 8.0f, width - 8.0f);
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
        g.setFont(juce::Font(13.0f));

        // Indent non-header items slightly
        int indent = 16;
        if (item.category == DisplayCategory::All ||
            item.category == DisplayCategory::Favorites ||
            item.category == DisplayCategory::Recent)
        {
            indent = 8;
        }

        g.drawText(item.name, indent, 0, width - indent - 8, height, juce::Justification::centredLeft);
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
