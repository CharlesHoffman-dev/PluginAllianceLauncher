/*
  ==============================================================================
    PAIdentifier.h
    Plugin Alliance Launcher - Plugin Alliance Plugin Detection
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <set>

namespace PALauncher
{

class PAIdentifier
{
public:
    PAIdentifier()
    {
        initializeManufacturers();
    }

    bool isPluginAlliancePlugin(const juce::PluginDescription& desc) const
    {
        // Exclude our own launcher plugin
        if (desc.name.containsIgnoreCase("Plugin Alliance Launcher"))
            return false;

        // Check manufacturer name
        if (paManufacturers.count(desc.manufacturerName.toLowerCase()) > 0)
            return true;

        // Check plugin name for known PA prefixes/brands
        auto nameLower = desc.name.toLowerCase();
        if (nameLower.startsWith("bx_") ||
            nameLower.startsWith("bx ") ||
            nameLower.contains("elysia") ||
            nameLower.contains("spl ") ||
            nameLower.contains("lindell") ||
            nameLower.contains("shadow hills") ||
            nameLower.contains("diezel") ||
            nameLower.contains("engl ") ||
            nameLower.contains("friedman") ||
            nameLower.contains("fuchs") ||
            nameLower.contains("suhr") ||
            nameLower.contains("ampeg") ||
            nameLower.contains("adptr") ||
            nameLower.contains("bettermaker") ||
            nameLower.contains("chandler") ||
            nameLower.contains("dangerous") ||
            nameLower.contains("maag") ||
            nameLower.contains("millennia") ||
            nameLower.contains("neold") ||
            nameLower.contains("noveltech") ||
            nameLower.contains("purple audio") ||
            nameLower.contains("vertigo") ||
            nameLower.contains("looptrotter") ||
            nameLower.contains("knif") ||
            nameLower.contains("tomo") ||
            nameLower.contains("kirchhoff") ||
            nameLower.contains("fiedler") ||
            nameLower.contains("hum audio") ||
            nameLower.contains("hears") ||
            nameLower.contains("acme"))
            return true;

        // Check file path for known PA plugin filenames
        auto pathLower = desc.fileOrIdentifier.toLowerCase();
        if (pathLower.contains("bx_") ||
            pathLower.contains("elysia") ||
            pathLower.contains("\\spl ") || pathLower.contains("/spl ") ||
            pathLower.contains("lindell") ||
            pathLower.contains("shadow hills") ||
            pathLower.contains("diezel") ||
            pathLower.contains("engl ") ||
            pathLower.contains("friedman") ||
            pathLower.contains("fuchs") ||
            pathLower.contains("suhr") ||
            pathLower.contains("ampeg") ||
            pathLower.contains("adptr") ||
            pathLower.contains("bettermaker") ||
            pathLower.contains("chandler") ||
            pathLower.contains("dangerous") ||
            pathLower.contains("maag") ||
            pathLower.contains("millennia") ||
            pathLower.contains("neold") ||
            pathLower.contains("noveltech") ||
            pathLower.contains("purple audio") ||
            pathLower.contains("vertigo") ||
            pathLower.contains("looptrotter") ||
            pathLower.contains("knif") ||
            pathLower.contains("tomo") ||
            pathLower.contains("kirchhoff") ||
            pathLower.contains("fiedler") ||
            pathLower.contains("hum audio") || pathLower.contains("laal") ||
            pathLower.contains("hears") ||
            pathLower.contains("acme"))
            return true;

        return false;
    }

    const std::set<juce::String>& getManufacturers() const
    {
        return paManufacturers;
    }

private:
    void initializeManufacturers()
    {
        // Core brands (lowercase for case-insensitive matching)
        paManufacturers.insert("plugin alliance");
        paManufacturers.insert("brainworx");
        paManufacturers.insert("bx_digital");

        // Partner brands
        paManufacturers.insert("adptr audio");
        paManufacturers.insert("unfiltered audio");
        paManufacturers.insert("lindell audio");
        paManufacturers.insert("elysia");
        paManufacturers.insert("shadow hills");
        paManufacturers.insert("shadow hills industries");
        paManufacturers.insert("spl");
        paManufacturers.insert("millennia");
        paManufacturers.insert("vertigo");
        paManufacturers.insert("vertigo sound");
        paManufacturers.insert("black box analog design");
        paManufacturers.insert("noveltech");
        paManufacturers.insert("maag audio");
        paManufacturers.insert("mäag audio");
        paManufacturers.insert("neold");
        paManufacturers.insert("three-body technology");
        paManufacturers.insert("hum audio devices");
        paManufacturers.insert("hears");
        paManufacturers.insert("bettermaker");
        paManufacturers.insert("proaudiodsp");
        paManufacturers.insert("fiedler audio");
        paManufacturers.insert("knif audio");
        paManufacturers.insert("tomo audiolabs");
        paManufacturers.insert("looptrotter");
        paManufacturers.insert("acme audio");

        // Amp brands
        paManufacturers.insert("ampeg");
        paManufacturers.insert("diezel");
        paManufacturers.insert("diezel amplification");
        paManufacturers.insert("fuchs");
        paManufacturers.insert("suhr");
        paManufacturers.insert("friedman");
        paManufacturers.insert("friedman amplification");
        paManufacturers.insert("engl");
        paManufacturers.insert("gallien krueger");
        paManufacturers.insert("gallien-krueger");
        paManufacturers.insert("chandler limited");
        paManufacturers.insert("a/da");

        // Console/Hardware brands
        paManufacturers.insert("amek");
        paManufacturers.insert("dangerous music");
        paManufacturers.insert("purple audio");
        paManufacturers.insert("ssl");
        paManufacturers.insert("solid state logic");
        paManufacturers.insert("neve");
        paManufacturers.insert("ams neve");
        paManufacturers.insert("focusrite");

        // Other
        paManufacturers.insert("thx");
        paManufacturers.insert("ds audio");
        paManufacturers.insert("swivel audio");
    }

    std::set<juce::String> paManufacturers;
};

} // namespace PALauncher
