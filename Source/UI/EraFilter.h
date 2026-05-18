/*
  ==============================================================================
    EraFilter.h
    Plugin Alliance Launcher - Era/Decade Filter Component
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Data/PluginCategories.h"

namespace PALauncher
{

class EraFilter : public juce::Component,
                  public juce::ListBoxModel
{
public:
    EraFilter();
    ~EraFilter() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // ListBoxModel overrides
    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
    void listBoxItemClicked(int row, const juce::MouseEvent&) override;
    juce::MouseCursor getMouseCursorForRow(int row) override;

    // Get selected era (-1 for All)
    Era getSelectedEra() const;

    // Callback when era changes
    std::function<void(Era)> onEraChanged;

private:
    struct EraItem
    {
        Era era;
        juce::String name;
    };

    void buildEraList();

    juce::ListBox listBox;
    std::vector<EraItem> eras;
    int selectedRow = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EraFilter)
};

} // namespace PALauncher
