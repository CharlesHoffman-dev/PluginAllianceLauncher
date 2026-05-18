/*
  ==============================================================================
    PluginListView.cpp
    Plugin Alliance Launcher - Scrollable Plugin Grid View Implementation
  ==============================================================================
*/

#include "PluginListView.h"
#include "../Utils/PluginImageCache.h"
#include "Colors.h"

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
    g.fillAll(Colors::gridBackground());
}

void PluginListView::paintOverChildren(juce::Graphics& g)
{
    // Draw "No plugins found" on top of everything so it's not obscured
    if (allPlugins.isEmpty())
    {
        auto textBounds = getLocalBounds().withTrimmedRight(14);
        g.setColour(Colors::textDisabled());
        g.setFont(juce::Font(14.0f));
        g.drawText("No plugins found.", textBounds, juce::Justification::centred);
    }
}

void PluginListView::resized()
{
    auto bounds = getLocalBounds();

    // Scrollbar on right, full height of the view. Internal padding (so the
    // blue thumb doesn't touch the top/bottom edges of the track) is applied
    // by CyanScrollBarLookAndFeel::drawScrollbar.
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
    int availableWidth = contentComponent.getWidth();
    int cardWidth = PluginCard::preferredWidth + cardSpacing;

    int cols = juce::jmax(2, availableWidth / cardWidth);
    return cols;
}

void PluginListView::updateVisibleCards()
{
    // Pool the PluginCard instances instead of destroying / recreating them on
    // every scroll. We grow the pool as needed, hide leftovers when fewer
    // cards fit, and just call setPluginInfo() / setBounds() to repurpose the
    // existing card objects.

    if (allPlugins.isEmpty())
    {
        for (auto* c : visibleCards) c->setVisible(false);
        return;
    }

    const int visibleHeight = contentComponent.getHeight();
    const int cardHeight    = PluginCard::preferredHeight + cardSpacing;
    const int cardWidth     = PluginCard::preferredWidth  + cardSpacing;

    const int firstVisibleRow = juce::jmax(0, scrollOffset / cardHeight);
    const int lastVisibleRow  = (scrollOffset + visibleHeight) / cardHeight + 1;

    const int totalCardsWidth = numColumns * cardWidth;
    const int availableWidth  = contentComponent.getWidth();
    const int startX          = juce::jmax(4, (availableWidth - totalCardsWidth) / 2);
    const int topInset        = 6;

    int slot = 0;  // index into the visibleCards pool

    for (int row = firstVisibleRow; row <= lastVisibleRow; ++row)
    {
        bool rowOutOfRange = false;
        for (int col = 0; col < numColumns; ++col)
        {
            const int pluginIndex = row * numColumns + col;
            if (pluginIndex >= allPlugins.size()) { rowOutOfRange = true; break; }

            PluginCard* card;
            if (slot < visibleCards.size())
            {
                card = visibleCards[slot];
            }
            else
            {
                card = new PluginCard();
                visibleCards.add(card);
                contentComponent.addAndMakeVisible(card);

                // Wire callbacks ONCE per card instance. They re-derive the
                // current plugin from the card itself / the info argument, so
                // they keep working after the card is reused.
                card->onSelected = [this](const PluginInfo& info)
                {
                    selectedIndex = -1;
                    for (int i = 0; i < allPlugins.size(); ++i)
                    {
                        if (allPlugins.getReference(i).description.fileOrIdentifier
                              == info.description.fileOrIdentifier)
                        {
                            selectedIndex = i;
                            break;
                        }
                    }
                    for (auto* c : visibleCards)
                        c->setSelected(c->getPluginInfo().description.fileOrIdentifier
                                         == info.description.fileOrIdentifier);
                    if (onPluginSelected) onPluginSelected(info);
                };
                card->onDoubleClick = [this](const PluginInfo& info)
                {
                    if (onPluginDoubleClick) onPluginDoubleClick(info);
                };
                card->onFavoriteToggle = [this](const PluginInfo& info, bool favorite)
                {
                    if (onFavoriteToggle) onFavoriteToggle(info, favorite);
                };
            }

            const auto& info = allPlugins.getReference(pluginIndex);
            card->setPluginInfo(info);
            card->setSelected(pluginIndex == selectedIndex);
            card->setLoaded(loadedPluginId.isNotEmpty()
                              && info.description.fileOrIdentifier == loadedPluginId);

            const int x = startX + col * cardWidth;
            const int y = topInset + cardSpacing + row * cardHeight - scrollOffset;
            card->setBounds(x, y, PluginCard::preferredWidth, PluginCard::preferredHeight);
            card->setVisible(true);
            ++slot;
        }
        if (rowOutOfRange) break;
    }

    // Hide any pooled cards we didn't need this frame.
    for (int i = slot; i < visibleCards.size(); ++i)
        visibleCards[i]->setVisible(false);
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
