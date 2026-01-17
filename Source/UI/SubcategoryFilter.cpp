/*
  ==============================================================================
    SubcategoryFilter.cpp
    Plugin Alliance Launcher - Subcategory Filter Component Implementation
  ==============================================================================
*/

#include "SubcategoryFilter.h"
#include <algorithm>

namespace PALauncher
{

SubcategoryFilter::SubcategoryFilter()
{
    listBox.setModel(this);
    listBox.setRowHeight(26);
    listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(listBox);

    buildSubcategoryList();
}

void SubcategoryFilter::setCategory(DisplayCategory category)
{
    currentCategory = category;
    buildSubcategoryList();
    listBox.updateContent();
    listBox.selectRow(0);
    selectedRow = 0;
    repaint();
}

void SubcategoryFilter::buildSubcategoryList()
{
    subcategories.clear();

    // Always have "All" option
    subcategories.push_back({-1, "All"});

    switch (currentCategory)
    {
        case DisplayCategory::Dynamics:
            subcategories.push_back({static_cast<int>(CompressorType::Optical), getCompressorTypeName(CompressorType::Optical)});
            subcategories.push_back({static_cast<int>(CompressorType::VCA), getCompressorTypeName(CompressorType::VCA)});
            subcategories.push_back({static_cast<int>(CompressorType::FET), getCompressorTypeName(CompressorType::FET)});
            subcategories.push_back({static_cast<int>(CompressorType::Tube), getCompressorTypeName(CompressorType::Tube)});
            subcategories.push_back({static_cast<int>(CompressorType::Diode), getCompressorTypeName(CompressorType::Diode)});
            subcategories.push_back({static_cast<int>(CompressorType::MultiBand), getCompressorTypeName(CompressorType::MultiBand)});
            subcategories.push_back({static_cast<int>(CompressorType::Mastering), getCompressorTypeName(CompressorType::Mastering)});
            break;

        case DisplayCategory::Equalization:
            subcategories.push_back({static_cast<int>(EQType::Parametric), getEQTypeName(EQType::Parametric)});
            subcategories.push_back({static_cast<int>(EQType::Dynamic), getEQTypeName(EQType::Dynamic)});
            subcategories.push_back({static_cast<int>(EQType::Passive), getEQTypeName(EQType::Passive)});
            subcategories.push_back({static_cast<int>(EQType::Console), getEQTypeName(EQType::Console)});
            subcategories.push_back({static_cast<int>(EQType::Analog), getEQTypeName(EQType::Analog)});
            subcategories.push_back({static_cast<int>(EQType::Mastering), getEQTypeName(EQType::Mastering)});
            subcategories.push_back({static_cast<int>(EQType::MidSide), getEQTypeName(EQType::MidSide)});
            break;

        case DisplayCategory::Reverbs:
            subcategories.push_back({static_cast<int>(ReverbType::Hall), getReverbTypeName(ReverbType::Hall)});
            subcategories.push_back({static_cast<int>(ReverbType::Room), getReverbTypeName(ReverbType::Room)});
            subcategories.push_back({static_cast<int>(ReverbType::Plate), getReverbTypeName(ReverbType::Plate)});
            subcategories.push_back({static_cast<int>(ReverbType::Spring), getReverbTypeName(ReverbType::Spring)});
            subcategories.push_back({static_cast<int>(ReverbType::Algorithmic), getReverbTypeName(ReverbType::Algorithmic)});
            subcategories.push_back({static_cast<int>(ReverbType::Convolution), getReverbTypeName(ReverbType::Convolution)});
            break;

        case DisplayCategory::GuitarBass:
            subcategories.push_back({static_cast<int>(GuitarBassType::Amp), getGuitarBassTypeName(GuitarBassType::Amp)});
            subcategories.push_back({static_cast<int>(GuitarBassType::Cabinet), getGuitarBassTypeName(GuitarBassType::Cabinet)});
            subcategories.push_back({static_cast<int>(GuitarBassType::Pedal), getGuitarBassTypeName(GuitarBassType::Pedal)});
            subcategories.push_back({static_cast<int>(GuitarBassType::Preamp), getGuitarBassTypeName(GuitarBassType::Preamp)});
            subcategories.push_back({static_cast<int>(GuitarBassType::Suite), getGuitarBassTypeName(GuitarBassType::Suite)});
            break;

        case DisplayCategory::Saturation:
            subcategories.push_back({static_cast<int>(SaturationType::Tube), getSaturationTypeName(SaturationType::Tube)});
            subcategories.push_back({static_cast<int>(SaturationType::Tape), getSaturationTypeName(SaturationType::Tape)});
            subcategories.push_back({static_cast<int>(SaturationType::Transformer), getSaturationTypeName(SaturationType::Transformer)});
            subcategories.push_back({static_cast<int>(SaturationType::Console), getSaturationTypeName(SaturationType::Console)});
            break;

        case DisplayCategory::SpecialProcessing:
            subcategories.push_back({static_cast<int>(SpecialProcessingType::ThreeDAudio), getSpecialProcessingTypeName(SpecialProcessingType::ThreeDAudio)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::Imagers), getSpecialProcessingTypeName(SpecialProcessingType::Imagers)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::LoFi), getSpecialProcessingTypeName(SpecialProcessingType::LoFi)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::Modulation), getSpecialProcessingTypeName(SpecialProcessingType::Modulation)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::MultiFX), getSpecialProcessingTypeName(SpecialProcessingType::MultiFX)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::Pitch), getSpecialProcessingTypeName(SpecialProcessingType::Pitch)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::Restoration), getSpecialProcessingTypeName(SpecialProcessingType::Restoration)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::SurroundSound), getSpecialProcessingTypeName(SpecialProcessingType::SurroundSound)});
            subcategories.push_back({static_cast<int>(SpecialProcessingType::Utility), getSpecialProcessingTypeName(SpecialProcessingType::Utility)});
            break;

        default:
            // No subcategories for other categories
            break;
    }

    // Sort subcategories alphabetically (keeping "All" at the top)
    if (subcategories.size() > 1)
    {
        std::sort(subcategories.begin() + 1, subcategories.end(),
            [](const SubcategoryItem& a, const SubcategoryItem& b)
            {
                return a.name.compareIgnoreCase(b.name) < 0;
            });
    }
}

void SubcategoryFilter::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff121212));

    // Draw header with grey background and white text
    auto headerBounds = getLocalBounds().reduced(4).removeFromTop(24);
    g.setColour(juce::Colour(0xff2a2a2a));
    g.fillRect(headerBounds);

    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(12.0f, juce::Font::bold));
    g.drawText("SUBCATEGORY", headerBounds.reduced(8, 0), juce::Justification::centredLeft);
}

void SubcategoryFilter::resized()
{
    auto bounds = getLocalBounds().reduced(4);
    bounds.removeFromTop(28);  // Space for header
    listBox.setBounds(bounds);
}

int SubcategoryFilter::getNumRows()
{
    return static_cast<int>(subcategories.size());
}

void SubcategoryFilter::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowNumber < 0 || rowNumber >= static_cast<int>(subcategories.size()))
        return;

    const auto& item = subcategories[rowNumber];

    if (rowIsSelected)
    {
        g.setColour(juce::Colour(0xff0cbff2));
        g.fillRoundedRectangle(2.0f, 1.0f, width - 4.0f, height - 2.0f, 3.0f);
    }

    g.setColour(rowIsSelected ? juce::Colours::white : juce::Colour(0xfff9f9f9));
    g.setFont(juce::Font(14.0f));
    g.drawText(item.name, 8, 0, width - 16, height, juce::Justification::centredLeft);
}

void SubcategoryFilter::listBoxItemClicked(int row, const juce::MouseEvent&)
{
    if (row < 0 || row >= static_cast<int>(subcategories.size()))
        return;

    selectedRow = row;

    if (onSubcategoryChanged)
        onSubcategoryChanged(subcategories[row].typeValue);
}

int SubcategoryFilter::getSelectedSubcategoryType() const
{
    if (selectedRow >= 0 && selectedRow < static_cast<int>(subcategories.size()))
        return subcategories[selectedRow].typeValue;
    return -1;
}

} // namespace PALauncher
