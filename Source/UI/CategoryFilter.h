/*
  ==============================================================================
    CategoryFilter.h
    Plugin Alliance Launcher - Category Filter Sidebar
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Data/PluginCategories.h"

namespace PALauncher
{

class CategoryFilter : public juce::Component,
                       public juce::ListBoxModel
{
public:
    CategoryFilter();
    ~CategoryFilter() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // ListBoxModel overrides
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent&) override;

    // Get selected category
    DisplayCategory getSelectedCategory() const;

    // Callback when category changes
    std::function<void(DisplayCategory)> onCategoryChanged;

private:
    struct CategoryItem
    {
        DisplayCategory category;
        juce::String name;
        bool isHeader = false;
    };

    void buildCategoryList();

    juce::ListBox listBox;
    std::vector<CategoryItem> categories;
    int selectedRow = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CategoryFilter)
};

} // namespace PALauncher
