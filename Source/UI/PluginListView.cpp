/*
  ==============================================================================
    PluginListView.cpp
    Plugin Alliance Launcher - Scrollable Plugin Grid View Implementation
  ==============================================================================
*/

#include "PluginListView.h"
#include "../Utils/PluginImageCache.h"

namespace PALauncher
{

PluginListView::PluginListView()
{
    contentComponent.setOpaque(false);
    addAndMakeVisible(contentComponent);

    verticalScrollBar.setRangeLimits(0.0, 1.0);
    verticalScrollBar.setAutoHide(false);
    verticalScrollBar.addListener(this);
    addAndMakeVisible(verticalScrollBar);

    setOpaque(true);

    // Register for image loaded callbacks
    PluginImageCache::getInstance().onImageLoaded = [this](const juce::String& pluginName)
    {
        // Update any visible cards that match this plugin
        for (auto* card : visibleCards)
        {
            if (card->getPluginInfo().description.name.toLowerCase() == pluginName.toLowerCase())
            {
                card->updateImage();
            }
        }
    };
}

PluginListView::~PluginListView()
{
    verticalScrollBar.removeListener(this);
}

void PluginListView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xfff9f9f9));
}

void PluginListView::paintOverChildren(juce::Graphics& g)
{
    // Draw "No plugins found" on top of everything so it's not obscured
    if (allPlugins.isEmpty())
    {
        auto textBounds = getLocalBounds().withTrimmedRight(14);
        g.setColour(juce::Colour(0xff666666));
        g.setFont(juce::Font(14.0f));
        g.drawText("No plugins found.", textBounds, juce::Justification::centred);
    }
}

void PluginListView::resized()
{
    auto bounds = getLocalBounds();

    // Scrollbar on right
    verticalScrollBar.setBounds(bounds.removeFromRight(14));

    contentComponent.setBounds(bounds);
    updateLayout();
}

void PluginListView::setPlugins(const juce::Array<PluginInfo>& plugins)
{
    allPlugins = plugins;
    selectedIndex = -1;
    scrollOffset = 0;
    updateLayout();
}

void PluginListView::updatePlugins(const juce::Array<PluginInfo>& plugins)
{
    // Update plugin list while preserving scroll position
    // Used for favorites toggle and other updates that shouldn't reset scroll
    allPlugins = plugins;
    // Don't reset selectedIndex or scrollOffset
    updateLayout();
}

void PluginListView::setLoadedPluginId(const juce::String& pluginId)
{
    if (loadedPluginId != pluginId)
    {
        loadedPluginId = pluginId;
        updateVisibleCards();  // Refresh cards to update loaded state
    }
}

void PluginListView::updateLayout()
{
    numColumns = calculateNumColumns();

    int numRows = (allPlugins.size() + numColumns - 1) / numColumns;
    int totalHeight = numRows * (PluginCard::preferredHeight + cardSpacing) + cardSpacing;

    int visibleHeight = contentComponent.getHeight();

    // Update scrollbar
    if (totalHeight > visibleHeight)
    {
        verticalScrollBar.setRangeLimits(0.0, totalHeight);
        verticalScrollBar.setCurrentRange(scrollOffset, visibleHeight);
        verticalScrollBar.setVisible(true);
    }
    else
    {
        verticalScrollBar.setVisible(false);
        scrollOffset = 0;
    }

    updateVisibleCards();
}

int PluginListView::calculateNumColumns() const
{
    // Fixed 4 columns for consistent layout
    return 4;
}

void PluginListView::updateVisibleCards()
{
    // Clear existing cards
    visibleCards.clear();

    if (allPlugins.isEmpty())
        return;

    int visibleHeight = contentComponent.getHeight();
    int cardHeight = PluginCard::preferredHeight + cardSpacing;
    int cardWidth = PluginCard::preferredWidth + cardSpacing;

    // Calculate which rows are visible
    int firstVisibleRow = juce::jmax(0, scrollOffset / cardHeight);
    int lastVisibleRow = (scrollOffset + visibleHeight) / cardHeight + 1;

    // Calculate grid position - align cards to left with minimal padding
    int totalCardsWidth = numColumns * cardWidth;
    int availableWidth = contentComponent.getWidth();
    int startX = juce::jmax(4, (availableWidth - totalCardsWidth) / 2);

    for (int row = firstVisibleRow; row <= lastVisibleRow; ++row)
    {
        for (int col = 0; col < numColumns; ++col)
        {
            int pluginIndex = row * numColumns + col;

            if (pluginIndex >= allPlugins.size())
                break;

            auto* card = new PluginCard();
            card->setPluginInfo(allPlugins[pluginIndex]);
            card->setSelected(pluginIndex == selectedIndex);

            // Check if this is the currently loaded plugin
            bool isLoaded = loadedPluginId.isNotEmpty() &&
                           allPlugins[pluginIndex].description.fileOrIdentifier == loadedPluginId;
            card->setLoaded(isLoaded);

            card->onSelected = [this, pluginIndex](const PluginInfo& info)
            {
                selectedIndex = pluginIndex;
                for (auto* c : visibleCards)
                    c->setSelected(false);

                if (auto* selectedCard = visibleCards[pluginIndex - (scrollOffset / (PluginCard::preferredHeight + cardSpacing)) * numColumns])
                {
                    for (auto* c : visibleCards)
                    {
                        if (&c->getPluginInfo() == &info)
                            c->setSelected(true);
                    }
                }

                // Find and select the right card
                for (auto* c : visibleCards)
                {
                    if (c->getPluginInfo().description.fileOrIdentifier == info.description.fileOrIdentifier)
                        c->setSelected(true);
                }

                if (onPluginSelected)
                    onPluginSelected(info);
            };

            card->onDoubleClick = [this](const PluginInfo& info)
            {
                if (onPluginDoubleClick)
                    onPluginDoubleClick(info);
            };

            card->onFavoriteToggle = [this](const PluginInfo& info, bool favorite)
            {
                if (onFavoriteToggle)
                    onFavoriteToggle(info, favorite);
            };

            int x = startX + col * cardWidth;
            int y = cardSpacing + row * cardHeight - scrollOffset;

            card->setBounds(x, y, PluginCard::preferredWidth, PluginCard::preferredHeight);
            contentComponent.addAndMakeVisible(card);
            visibleCards.add(card);
        }
    }
}

void PluginListView::scrollBarMoved(juce::ScrollBar*, double newRangeStart)
{
    scrollOffset = static_cast<int>(newRangeStart);
    updateVisibleCards();
}

void PluginListView::mouseWheelMove(const juce::MouseEvent&, const juce::MouseWheelDetails& wheel)
{
    if (!verticalScrollBar.isVisible())
        return;

    float scrollAmount = wheel.deltaY * 200.0f;
    int newOffset = juce::jlimit(0,
                                  static_cast<int>(verticalScrollBar.getMaximumRangeLimit() - contentComponent.getHeight()),
                                  scrollOffset - static_cast<int>(scrollAmount));

    if (newOffset != scrollOffset)
    {
        scrollOffset = newOffset;
        verticalScrollBar.setCurrentRangeStart(scrollOffset);
        updateVisibleCards();
    }
}

const PluginInfo* PluginListView::getSelectedPlugin() const
{
    if (selectedIndex >= 0 && selectedIndex < allPlugins.size())
        return &allPlugins.getReference(selectedIndex);
    return nullptr;
}

void PluginListView::selectPluginAtIndex(int index)
{
    if (index >= 0 && index < allPlugins.size())
    {
        selectedIndex = index;
        updateVisibleCards();  // Refresh to show selection
    }
}

} // namespace PALauncher
