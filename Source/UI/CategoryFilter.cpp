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

    // Effects header
    categories.push_back({DisplayCategory::All, "EFFECTS", true});

    // Effect categories (alphabetical)
    categories.push_back({DisplayCategory::AmpSim, "Amp Simulators", false});
    categories.push_back({DisplayCategory::ChannelStrip, "Channel Strips", false});
    categories.push_back({DisplayCategory::Compressors, "Compressors", false});
    categories.push_back({DisplayCategory::Creative, "Creative", false});
    categories.push_back({DisplayCategory::Delay, "Delay", false});
    categories.push_back({DisplayCategory::Distortion, "Distortion", false});
    categories.push_back({DisplayCategory::EQ, "EQs", false});
    categories.push_back({DisplayCategory::Expanders, "Expanders", false});
    categories.push_back({DisplayCategory::Mastering, "Mastering", false});
    categories.push_back({DisplayCategory::Metering, "Metering", false});
    categories.push_back({DisplayCategory::Mixing, "Mixing", false});
    categories.push_back({DisplayCategory::Modulation, "Modulation", false});
    categories.push_back({DisplayCategory::Pitch, "Pitch", false});
    categories.push_back({DisplayCategory::Reverb, "Reverb", false});
    categories.push_back({DisplayCategory::Saturation, "Saturation", false});
    categories.push_back({DisplayCategory::StereoImaging, "Stereo Imaging", false});
    categories.push_back({DisplayCategory::Utility, "Utility", false});
    categories.push_back({DisplayCategory::Vocal, "Vocal Processing", false});

    // Instruments header
    categories.push_back({DisplayCategory::All, "INSTRUMENTS", true});

    // Instrument categories (alphabetical)
    categories.push_back({DisplayCategory::Drums, "Drums", false});
    categories.push_back({DisplayCategory::Sampler, "Samplers", false});
    categories.push_back({DisplayCategory::Synth, "Synths", false});

    // Brands header
    categories.push_back({DisplayCategory::All, "BRANDS", true});

    // Brand categories (alphabetical)
    categories.push_back({DisplayCategory::Brand_ACMEAudio, "ACME Audio", false});
    categories.push_back({DisplayCategory::Brand_ADA, "ADA", false});
    categories.push_back({DisplayCategory::Brand_ADPTRAudio, "ADPTR AUDIO", false});
    categories.push_back({DisplayCategory::Brand_AMEK, "AMEK", false});
    categories.push_back({DisplayCategory::Brand_Ampeg, "Ampeg", false});
    categories.push_back({DisplayCategory::Brand_Bettermaker, "Bettermaker", false});
    categories.push_back({DisplayCategory::Brand_BlackBoxAnalogDesign, "Black Box Analog Design", false});
    categories.push_back({DisplayCategory::Brand_Brainworx, "Brainworx", false});
    categories.push_back({DisplayCategory::Brand_ChandlerLimited, "Chandler Limited", false});
    categories.push_back({DisplayCategory::Brand_CutClassic, "Cut Classic", false});
    categories.push_back({DisplayCategory::Brand_DangerousMusic, "Dangerous Music", false});
    categories.push_back({DisplayCategory::Brand_Diezel, "Diezel", false});
    categories.push_back({DisplayCategory::Brand_DSAudio, "DS Audio", false});
    categories.push_back({DisplayCategory::Brand_Elysia, "elysia", false});
    categories.push_back({DisplayCategory::Brand_ENGL, "ENGL", false});
    categories.push_back({DisplayCategory::Brand_FiedlerAudio, "fiedler audio", false});
    categories.push_back({DisplayCategory::Brand_Focusrite, "Focusrite", false});
    categories.push_back({DisplayCategory::Brand_Friedman, "Friedman", false});
    categories.push_back({DisplayCategory::Brand_Fuchs, "Fuchs", false});
    categories.push_back({DisplayCategory::Brand_GallienKrueger, "Gallien-Krueger", false});
    categories.push_back({DisplayCategory::Brand_HarrisDoyle, "Harris Doyle", false});
    categories.push_back({DisplayCategory::Brand_HEARS, "HEARS", false});
    categories.push_back({DisplayCategory::Brand_HUMAudioDevices, "HUM Audio Devices", false});
    categories.push_back({DisplayCategory::Brand_KaranyiSounds, "Karanyi Sounds", false});
    categories.push_back({DisplayCategory::Brand_KiiveAudio, "Kiive Audio", false});
    categories.push_back({DisplayCategory::Brand_KnifAudio, "Knif Audio", false});
    categories.push_back({DisplayCategory::Brand_LindellAudio, "Lindell Audio", false});
    categories.push_back({DisplayCategory::Brand_Looptrotter, "Looptrotter", false});
    categories.push_back({DisplayCategory::Brand_LouderThanLiftoff, "Louder Than Liftoff", false});
    categories.push_back({DisplayCategory::Brand_MaorAppelbaumHendyamps, "Maor Appelbaum & Hendyamps", false});
    categories.push_back({DisplayCategory::Brand_Millennia, "Millennia", false});
    categories.push_back({DisplayCategory::Brand_Mixland, "Mixland", false});
    categories.push_back({DisplayCategory::Brand_MaagAudio, "Mäag Audio", false});
    categories.push_back({DisplayCategory::Brand_NEOLD, "NEOLD", false});
    categories.push_back({DisplayCategory::Brand_Noveltech, "Noveltech", false});
    categories.push_back({DisplayCategory::Brand_ProAudioDSP, "Pro Audio DSP", false});
    categories.push_back({DisplayCategory::Brand_PurpleAudio, "Purple Audio", false});
    categories.push_back({DisplayCategory::Brand_ShadowHills, "Shadow Hills", false});
    categories.push_back({DisplayCategory::Brand_SSL, "Solid State Logic (SSL)", false});
    categories.push_back({DisplayCategory::Brand_SPL, "SPL", false});
    categories.push_back({DisplayCategory::Brand_Suhr, "Suhr", false});
    categories.push_back({DisplayCategory::Brand_SwivelAudio, "Swivel Audio", false});
    categories.push_back({DisplayCategory::Brand_ThreeBodyTechnology, "Three-Body Technology", false});
    categories.push_back({DisplayCategory::Brand_THX, "THX", false});
    categories.push_back({DisplayCategory::Brand_TOMOAudiolabs, "TOMO Audiolabs", false});
    categories.push_back({DisplayCategory::Brand_UnfilteredAudio, "Unfiltered Audio", false});
    categories.push_back({DisplayCategory::Brand_Vertigo, "Vertigo", false});
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
