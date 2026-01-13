/*
  ==============================================================================
    SubcategoryFilter.cpp
    Plugin Alliance Launcher - Subcategory Filter Component Implementation
  ==============================================================================
*/

#include "SubcategoryFilter.h"

namespace PALauncher
{

SubcategoryFilter::SubcategoryFilter()
{
    titleLabel.setText("Subcategory", juce::dontSendNotification);
    titleLabel.setFont(juce::Font(11.0f, juce::Font::bold));
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xff888888));
    addAndMakeVisible(titleLabel);

    listBox.setModel(this);
    listBox.setRowHeight(24);
    listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(listBox);

    buildSubcategoryList();
}

void SubcategoryFilter::setCategory(DisplayCategory category)
{
    if (currentCategory != category)
    {
        currentCategory = category;
        buildSubcategoryList();
        listBox.updateContent();
        listBox.selectRow(0);
        selectedRow = 0;
    }
}

void SubcategoryFilter::buildSubcategoryList()
{
    subcategories.clear();

    // Always have "All" option
    subcategories.push_back({-1, "All"});

    switch (currentCategory)
    {
        case DisplayCategory::Compressors:
            subcategories.push_back({static_cast<int>(CompressorType::Optical), getCompressorTypeName(CompressorType::Optical)});
            subcategories.push_back({static_cast<int>(CompressorType::VCA), getCompressorTypeName(CompressorType::VCA)});
            subcategories.push_back({static_cast<int>(CompressorType::FET), getCompressorTypeName(CompressorType::FET)});
            subcategories.push_back({static_cast<int>(CompressorType::Tube), getCompressorTypeName(CompressorType::Tube)});
            subcategories.push_back({static_cast<int>(CompressorType::Diode), getCompressorTypeName(CompressorType::Diode)});
            subcategories.push_back({static_cast<int>(CompressorType::MultiBand), getCompressorTypeName(CompressorType::MultiBand)});
            subcategories.push_back({static_cast<int>(CompressorType::Mastering), getCompressorTypeName(CompressorType::Mastering)});
            break;

        case DisplayCategory::EQ:
            subcategories.push_back({static_cast<int>(EQType::Parametric), getEQTypeName(EQType::Parametric)});
            subcategories.push_back({static_cast<int>(EQType::Dynamic), getEQTypeName(EQType::Dynamic)});
            subcategories.push_back({static_cast<int>(EQType::Passive), getEQTypeName(EQType::Passive)});
            subcategories.push_back({static_cast<int>(EQType::Console), getEQTypeName(EQType::Console)});
            subcategories.push_back({static_cast<int>(EQType::Analog), getEQTypeName(EQType::Analog)});
            subcategories.push_back({static_cast<int>(EQType::Mastering), getEQTypeName(EQType::Mastering)});
            subcategories.push_back({static_cast<int>(EQType::MidSide), getEQTypeName(EQType::MidSide)});
            break;

        case DisplayCategory::Reverb:
            subcategories.push_back({static_cast<int>(ReverbType::Hall), getReverbTypeName(ReverbType::Hall)});
            subcategories.push_back({static_cast<int>(ReverbType::Room), getReverbTypeName(ReverbType::Room)});
            subcategories.push_back({static_cast<int>(ReverbType::Plate), getReverbTypeName(ReverbType::Plate)});
            subcategories.push_back({static_cast<int>(ReverbType::Spring), getReverbTypeName(ReverbType::Spring)});
            subcategories.push_back({static_cast<int>(ReverbType::Algorithmic), getReverbTypeName(ReverbType::Algorithmic)});
            subcategories.push_back({static_cast<int>(ReverbType::Convolution), getReverbTypeName(ReverbType::Convolution)});
            break;

        case DisplayCategory::Delay:
            subcategories.push_back({static_cast<int>(DelayType::Tape), getDelayTypeName(DelayType::Tape)});
            subcategories.push_back({static_cast<int>(DelayType::Analog), getDelayTypeName(DelayType::Analog)});
            subcategories.push_back({static_cast<int>(DelayType::Digital), getDelayTypeName(DelayType::Digital)});
            subcategories.push_back({static_cast<int>(DelayType::PingPong), getDelayTypeName(DelayType::PingPong)});
            subcategories.push_back({static_cast<int>(DelayType::Modulated), getDelayTypeName(DelayType::Modulated)});
            break;

        case DisplayCategory::AmpSim:
            subcategories.push_back({static_cast<int>(AmpType::GuitarAmp), getAmpTypeName(AmpType::GuitarAmp)});
            subcategories.push_back({static_cast<int>(AmpType::BassAmp), getAmpTypeName(AmpType::BassAmp)});
            subcategories.push_back({static_cast<int>(AmpType::German), getAmpTypeName(AmpType::German)});
            subcategories.push_back({static_cast<int>(AmpType::American), getAmpTypeName(AmpType::American)});
            subcategories.push_back({static_cast<int>(AmpType::British), getAmpTypeName(AmpType::British)});
            subcategories.push_back({static_cast<int>(AmpType::HighGain), getAmpTypeName(AmpType::HighGain)});
            subcategories.push_back({static_cast<int>(AmpType::Vintage), getAmpTypeName(AmpType::Vintage)});
            break;

        case DisplayCategory::Saturation:
            subcategories.push_back({static_cast<int>(SaturationType::Tube), getSaturationTypeName(SaturationType::Tube)});
            subcategories.push_back({static_cast<int>(SaturationType::Tape), getSaturationTypeName(SaturationType::Tape)});
            subcategories.push_back({static_cast<int>(SaturationType::Transformer), getSaturationTypeName(SaturationType::Transformer)});
            subcategories.push_back({static_cast<int>(SaturationType::Console), getSaturationTypeName(SaturationType::Console)});
            break;

        case DisplayCategory::ChannelStrip:
            subcategories.push_back({static_cast<int>(ChannelStripType::SSL), getChannelStripTypeName(ChannelStripType::SSL)});
            subcategories.push_back({static_cast<int>(ChannelStripType::Neve), getChannelStripTypeName(ChannelStripType::Neve)});
            subcategories.push_back({static_cast<int>(ChannelStripType::API), getChannelStripTypeName(ChannelStripType::API)});
            subcategories.push_back({static_cast<int>(ChannelStripType::AMEK), getChannelStripTypeName(ChannelStripType::AMEK)});
            subcategories.push_back({static_cast<int>(ChannelStripType::Focusrite), getChannelStripTypeName(ChannelStripType::Focusrite)});
            subcategories.push_back({static_cast<int>(ChannelStripType::Vintage), getChannelStripTypeName(ChannelStripType::Vintage)});
            break;

        case DisplayCategory::Distortion:
            subcategories.push_back({static_cast<int>(DistortionType::Overdrive), getDistortionTypeName(DistortionType::Overdrive)});
            subcategories.push_back({static_cast<int>(DistortionType::Distortion), getDistortionTypeName(DistortionType::Distortion)});
            subcategories.push_back({static_cast<int>(DistortionType::Fuzz), getDistortionTypeName(DistortionType::Fuzz)});
            subcategories.push_back({static_cast<int>(DistortionType::BitCrusher), getDistortionTypeName(DistortionType::BitCrusher)});
            break;

        case DisplayCategory::Modulation:
            subcategories.push_back({static_cast<int>(ModulationType::Chorus), getModulationTypeName(ModulationType::Chorus)});
            subcategories.push_back({static_cast<int>(ModulationType::Flanger), getModulationTypeName(ModulationType::Flanger)});
            subcategories.push_back({static_cast<int>(ModulationType::Phaser), getModulationTypeName(ModulationType::Phaser)});
            subcategories.push_back({static_cast<int>(ModulationType::Tremolo), getModulationTypeName(ModulationType::Tremolo)});
            subcategories.push_back({static_cast<int>(ModulationType::Rotary), getModulationTypeName(ModulationType::Rotary)});
            break;

        default:
            // No subcategories for other categories
            break;
    }
}

void SubcategoryFilter::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff121212));
}

void SubcategoryFilter::resized()
{
    auto bounds = getLocalBounds().reduced(4);

    titleLabel.setBounds(bounds.removeFromTop(20));
    bounds.removeFromTop(4);
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
    g.setFont(juce::Font(12.0f));
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
