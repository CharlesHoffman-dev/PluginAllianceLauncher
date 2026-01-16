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

        // Check plugin name for known PA prefixes/brands (alphabetical)
        auto nameLower = desc.name.toLowerCase();
        if (nameLower.startsWith("bx_") ||
            nameLower.startsWith("bx ") ||
            nameLower.contains("a/da") ||
            nameLower.contains("acme") ||
            nameLower.contains("adptr") ||
            nameLower.contains("amek") ||
            nameLower.contains("ampeg") ||
            nameLower.contains("bettermaker") ||
            nameLower.contains("black box") ||
            nameLower.contains("cenozoix") ||
            nameLower.contains("chandler") ||
            nameLower.contains("cut classic") ||
            nameLower.contains("dangerous") ||
            nameLower.contains("dearvr") ||
            nameLower.contains("dear reality") ||
            nameLower.contains("diezel") ||
            nameLower.contains("ds audio") ||
            nameLower.contains("elysia") ||
            nameLower.contains("engl ") ||
            nameLower.contains("fiedler") ||
            nameLower.contains("focusrite") ||
            nameLower.contains("friedman") ||
            nameLower.contains("fuchs") ||
            nameLower.contains("gallien") ||
            nameLower.contains("harris doyle") ||
            nameLower.contains("hears") ||
            nameLower.contains("hum audio") ||
            nameLower.contains("karanyi") ||
            nameLower.contains("kiive") ||
            nameLower.contains("kirchhoff") ||
            nameLower.contains("knif") ||
            nameLower.contains("lindell") ||
            nameLower.contains("looptrotter") ||
            nameLower.contains("louder than liftoff") ||
            nameLower.contains("maag") ||
            nameLower.contains("maor appelbaum") ||
            nameLower.contains("millennia") ||
            nameLower.contains("mixland") ||
            nameLower.contains("neold") ||
            nameLower.contains("noveltech") ||
            nameLower.contains("pro audio dsp") ||
            nameLower.contains("purple audio") ||
            nameLower.contains("schoeps") ||
            nameLower.contains("shadow hills") ||
            nameLower.contains("sonible") ||
            nameLower.contains("spl ") ||
            nameLower.contains("ssl") ||
            nameLower.contains("suhr") ||
            nameLower.contains("swivel") ||
            nameLower.contains("three-body") ||
            nameLower.contains("thx") ||
            nameLower.contains("tomo") ||
            nameLower.contains("trinity") ||
            nameLower.contains("unfiltered") ||
            nameLower.contains("vertigo") ||
            nameLower.contains("wedge force"))
            return true;

        // Check file path for known PA plugin filenames
        auto pathLower = desc.fileOrIdentifier.toLowerCase();
        if (pathLower.contains("bx_") ||
            pathLower.contains("a-da") ||
            pathLower.contains("acme") ||
            pathLower.contains("adptr") ||
            pathLower.contains("amek") ||
            pathLower.contains("ampeg") ||
            pathLower.contains("bettermaker") ||
            pathLower.contains("black box") ||
            pathLower.contains("cenozoix") ||
            pathLower.contains("chandler") ||
            pathLower.contains("cut classic") ||
            pathLower.contains("dangerous") ||
            pathLower.contains("dearvr") ||
            pathLower.contains("dear reality") ||
            pathLower.contains("diezel") ||
            pathLower.contains("ds audio") ||
            pathLower.contains("elysia") ||
            pathLower.contains("engl ") ||
            pathLower.contains("fiedler") ||
            pathLower.contains("focusrite") ||
            pathLower.contains("friedman") ||
            pathLower.contains("fuchs") ||
            pathLower.contains("gallien") ||
            pathLower.contains("harris doyle") ||
            pathLower.contains("hears") ||
            pathLower.contains("hum audio") || pathLower.contains("laal") ||
            pathLower.contains("karanyi") ||
            pathLower.contains("kiive") ||
            pathLower.contains("kirchhoff") ||
            pathLower.contains("knif") ||
            pathLower.contains("lindell") ||
            pathLower.contains("looptrotter") ||
            pathLower.contains("louder than liftoff") ||
            pathLower.contains("maag") ||
            pathLower.contains("maor appelbaum") ||
            pathLower.contains("millennia") ||
            pathLower.contains("mixland") ||
            pathLower.contains("neold") ||
            pathLower.contains("noveltech") ||
            pathLower.contains("pro audio dsp") ||
            pathLower.contains("purple audio") ||
            pathLower.contains("schoeps") ||
            pathLower.contains("shadow hills") ||
            pathLower.contains("sonible") ||
            pathLower.contains("\\spl ") || pathLower.contains("/spl ") ||
            pathLower.contains("ssl") ||
            pathLower.contains("suhr") ||
            pathLower.contains("swivel") ||
            pathLower.contains("three-body") ||
            pathLower.contains("thx") ||
            pathLower.contains("tomo") ||
            pathLower.contains("trinity") ||
            pathLower.contains("unfiltered") ||
            pathLower.contains("vertigo") ||
            pathLower.contains("wedge force"))
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
        // All Plugin Alliance brands (alphabetical, lowercase for case-insensitive matching)

        // A
        paManufacturers.insert("a/da");
        paManufacturers.insert("acme audio");
        paManufacturers.insert("adptr audio");
        paManufacturers.insert("amek");
        paManufacturers.insert("ampeg");
        paManufacturers.insert("ams neve");

        // B
        paManufacturers.insert("bettermaker");
        paManufacturers.insert("black box analog design");
        paManufacturers.insert("brainworx");
        paManufacturers.insert("bx_digital");

        // C
        paManufacturers.insert("cenozoix");
        paManufacturers.insert("chandler limited");
        paManufacturers.insert("cut classic");

        // D
        paManufacturers.insert("dangerous music");
        paManufacturers.insert("dear reality");
        paManufacturers.insert("diezel");
        paManufacturers.insert("diezel amplification");
        paManufacturers.insert("ds audio");

        // E
        paManufacturers.insert("elysia");
        paManufacturers.insert("engl");

        // F
        paManufacturers.insert("fiedler audio");
        paManufacturers.insert("focusrite");
        paManufacturers.insert("friedman");
        paManufacturers.insert("friedman amplification");
        paManufacturers.insert("fuchs");

        // G
        paManufacturers.insert("gallien krueger");
        paManufacturers.insert("gallien-krueger");

        // H
        paManufacturers.insert("harris doyle");
        paManufacturers.insert("hears");
        paManufacturers.insert("hum audio devices");

        // K
        paManufacturers.insert("karanyi sounds");
        paManufacturers.insert("kiive audio");
        paManufacturers.insert("knif audio");

        // L
        paManufacturers.insert("lindell audio");
        paManufacturers.insert("looptrotter");
        paManufacturers.insert("louder than liftoff");

        // M
        paManufacturers.insert("maag audio");
        paManufacturers.insert("mäag audio");
        paManufacturers.insert("maor appelbaum & hendyamps");
        paManufacturers.insert("millennia");
        paManufacturers.insert("mixland");

        // N
        paManufacturers.insert("neold");
        paManufacturers.insert("neve");
        paManufacturers.insert("noveltech");

        // P
        paManufacturers.insert("plugin alliance");
        paManufacturers.insert("pro audio dsp");
        paManufacturers.insert("proaudiodsp");
        paManufacturers.insert("purple audio");

        // S
        paManufacturers.insert("schoeps");
        paManufacturers.insert("shadow hills");
        paManufacturers.insert("shadow hills industries");
        paManufacturers.insert("solid state logic");
        paManufacturers.insert("sonible");
        paManufacturers.insert("spl");
        paManufacturers.insert("ssl");
        paManufacturers.insert("suhr");
        paManufacturers.insert("swivel audio");

        // T
        paManufacturers.insert("three-body technology");
        paManufacturers.insert("thx");
        paManufacturers.insert("tomo audiolabs");
        paManufacturers.insert("trinity");

        // U
        paManufacturers.insert("unfiltered audio");

        // V
        paManufacturers.insert("vertigo");
        paManufacturers.insert("vertigo sound");

        // W
        paManufacturers.insert("wedge force");
    }

    std::set<juce::String> paManufacturers;
};

} // namespace PALauncher
