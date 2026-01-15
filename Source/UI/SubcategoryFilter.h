/*
  ==============================================================================
    SubcategoryFilter.h
    Plugin Alliance Launcher - Subcategory Filter Component
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Data/PluginCategories.h"
#include "../Data/PluginSubcategories.h"

namespace PALauncher
{

class SubcategoryFilter : public juce::Component,
                          public juce::ListBoxModel
{
public:
    SubcategoryFilter();
    ~SubcategoryFilter() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // ListBoxModel overrides
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent&) override;

    // Set the parent category to show relevant subcategories
    void setCategory(DisplayCategory category);

    // Get selected subcategory type (returns -1 for "All")
    int getSelectedSubcategoryType() const;

    // Callback when subcategory changes
    std::function<void(int)> onSubcategoryChanged;

private:
    struct SubcategoryItem
    {
        int typeValue;
        juce::String name;
    };

    void buildSubcategoryList();

    juce::ListBox listBox;
    std::vector<SubcategoryItem> subcategories;
    DisplayCategory currentCategory = DisplayCategory::All;
    int selectedRow = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SubcategoryFilter)
};

} // namespace PALauncher
