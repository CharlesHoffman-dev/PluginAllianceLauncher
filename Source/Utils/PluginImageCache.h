/*
  ==============================================================================
    PluginImageCache.h
    Plugin Alliance Launcher - Plugin Image Download and Caching
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>
#include <set>

namespace PALauncher
{

class PluginImageCache : public juce::Thread
{
public:
    PluginImageCache();
    ~PluginImageCache() override;

    // Get image for a plugin (returns nullptr if not yet loaded)
    juce::Image getImage(const juce::String& pluginName);

    // Check if an image is available
    bool hasImage(const juce::String& pluginName) const;

    // Snapshot every currently-loaded image. Used by the easter-egg game
    // to populate its pool of "asteroids". Returns a copy of the image
    // handles (juce::Image is internally reference-counted).
    juce::Array<juce::Image> getAllCachedImages() const;

    // Request an image to be loaded (async)
    void requestImage(const juce::String& pluginName);

    // Clear all cached images (both memory and disk)
    void clearCache();

    // Callback when an image is loaded
    std::function<void(const juce::String&)> onImageLoaded;

    // Singleton access
    static PluginImageCache& getInstance();

private:
    void run() override;
    void initializeImageUrls();
    void initializeThumbnailFilenames();
    void initializeBundledImagesPath();
    juce::String normalizePluginName(const juce::String& name) const;
    juce::StringArray getNameVariants(const juce::String& normalizedName) const;
    juce::String findImageUrl(const juce::String& normalizedName) const;
    juce::File getCacheDirectory() const;
    juce::File getCacheFile(const juce::String& pluginName) const;
    juce::File getBundledImageFile(const juce::String& pluginName) const;
    bool loadFromBundled(const juce::String& pluginName);
    bool loadFromCache(const juce::String& pluginName);
    bool downloadImage(const juce::String& pluginName, const juce::String& url);
    juce::String generateProductPageUrl(const juce::String& pluginName) const;
    juce::String fetchImageUrlFromProductPage(const juce::String& pluginName);

    // Plugin name -> image URL mapping
    std::map<juce::String, juce::String> imageUrls;

    // Plugin name -> thumbnail filename mapping (for bundled images)
    std::map<juce::String, juce::String> thumbnailFilenames;

    // Loaded images
    std::map<juce::String, juce::Image> loadedImages;

    // Pending download requests
    std::set<juce::String> pendingRequests;

    // Path to bundled images (in plugin resources)
    juce::File bundledImagesPath;

    mutable juce::CriticalSection lock;
    juce::WaitableEvent wakeUp;
    bool shouldExit = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginImageCache)
};

} // namespace PALauncher
