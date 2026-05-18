/*
  ==============================================================================
    SubcategoryFilter.cpp
    Plugin Alliance Launcher - Subcategory Filter Component Implementation
  ==============================================================================
*/

#include "SubcategoryFilter.h"
#include "Colors.h"
#include <algorithm>

namespace PALauncher
{

SubcategoryFilter::SubcategoryFilter()
{
    listBox.setModel(this);
    listBox.setRowHeight(26);
    listBox.setColour(juce::ListBox::backgroundColourId, juce::Colours::transparentBlack);
    listBox.setColour(juce::ListBox::outlineColourId, juce::Colours::transparentBlack);
    listBox.getViewport()->setScrollBarsShown(false, false);  // No scrollbars - parent viewport handles scrolling
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
        case DisplayCategory::Equalizers:
            subcategories.push_back({static_cast<int>(EQType::Parametric), getEQTypeName(EQType::Parametric)});
            subcategories.push_back({static_cast<int>(EQType::Dynamic), getEQTypeName(EQType::Dynamic)});
            subcategories.push_back({static_cast<int>(EQType::Passive), getEQTypeName(EQType::Passive)});
            subcategories.push_back({static_cast<int>(EQType::Mastering), getEQTypeName(EQType::Mastering)});
            subcategories.push_back({static_cast<int>(EQType::MidSide), getEQTypeName(EQType::MidSide)});
            break;

        case DisplayCategory::Compressors:
            subcategories.push_back({static_cast<int>(CompressorType::Bus), getCompressorTypeName(CompressorType::Bus)});
            subcategories.push_back({static_cast<int>(CompressorType::Optical), getCompressorTypeName(CompressorType::Optical)});
            subcategories.push_back({static_cast<int>(CompressorType::VCA), getCompressorTypeName(CompressorType::VCA)});
            subcategories.push_back({static_cast<int>(CompressorType::FET), getCompressorTypeName(CompressorType::FET)});
            subcategories.push_back({static_cast<int>(CompressorType::Tube), getCompressorTypeName(CompressorType::Tube)});
            subcategories.push_back({static_cast<int>(CompressorType::Diode), getCompressorTypeName(CompressorType::Diode)});
            subcategories.push_back({static_cast<int>(CompressorType::MultiBand), getCompressorTypeName(CompressorType::MultiBand)});
            subcategories.push_back({static_cast<int>(CompressorType::Mastering), getCompressorTypeName(CompressorType::Mastering)});
            break;

        case DisplayCategory::Other:
            subcategories.push_back({static_cast<int>(OtherType::ThreeDAndSurround), getOtherTypeName(OtherType::ThreeDAndSurround)});
            subcategories.push_back({static_cast<int>(OtherType::Gates), getOtherTypeName(OtherType::Gates)});
            subcategories.push_back({static_cast<int>(OtherType::LoFi), getOtherTypeName(OtherType::LoFi)});
            subcategories.push_back({static_cast<int>(OtherType::Modulators), getOtherTypeName(OtherType::Modulators)});
            subcategories.push_back({static_cast<int>(OtherType::MultiFX), getOtherTypeName(OtherType::MultiFX)});
            subcategories.push_back({static_cast<int>(OtherType::PitchCorrection), getOtherTypeName(OtherType::PitchCorrection)});
            subcategories.push_back({static_cast<int>(OtherType::Restoration), getOtherTypeName(OtherType::Restoration)});
            subcategories.push_back({static_cast<int>(OtherType::StereoImagers), getOtherTypeName(OtherType::StereoImagers)});
            subcategories.push_back({static_cast<int>(OtherType::TransientShapers), getOtherTypeName(OtherType::TransientShapers)});
            subcategories.push_back({static_cast<int>(OtherType::Utility), getOtherTypeName(OtherType::Utility)});
            subcategories.push_back({static_cast<int>(OtherType::VocalProcessing), getOtherTypeName(OtherType::VocalProcessing)});
            subcategories.push_back({static_cast<int>(OtherType::Vocoders), getOtherTypeName(OtherType::Vocoders)});
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
    g.fillAll(Colors::appBackground());

    // Draw header with charcoal/burnt-orange background and white text
    auto headerBounds = getLocalBounds().reduced(4).removeFromTop(24);
    g.setColour(Colors::sidebarHeader());
    g.fillRect(headerBounds);

    g.setColour(Colors::textOnDark());
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
        g.setColour(Colors::accent());
        g.fillRoundedRectangle(2.0f, 1.0f, width - 4.0f, height - 2.0f, 3.0f);
    }

    g.setColour(Colors::textOnDark());
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

int SubcategoryFilter::getRequiredHeight() const
{
    // 8px total vertical padding (reduced(4) on both sides)
    // 28px header
    // numRows * 26px (row height)
    return 8 + 28 + static_cast<int>(subcategories.size()) * 26;
}

} // namespace PALauncher
