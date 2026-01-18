#!/usr/bin/env python3
"""
Migrate category and era mappings from PluginDatabase.cpp to plugins.json
"""

import json
import re
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent
PROJECT_ROOT = SCRIPT_DIR.parent
PLUGINS_JSON = PROJECT_ROOT / "plugins.json"
DATABASE_CPP = PROJECT_ROOT / "Source" / "Core" / "PluginDatabase.cpp"

# Map C++ enum values to JSON-friendly category names
CATEGORY_MAP = {
    "EffectCategory::EQ": "Equalizer",
    "EffectCategory::Filter": "Filter",
    "EffectCategory::Compressor": "Compressor",
    "EffectCategory::Limiter": "Limiter",
    "EffectCategory::Gate": "Gate",
    "EffectCategory::TransientShaper": "Transient Shaper",
    "EffectCategory::DeEsser": "De-Esser",
    "EffectCategory::ChannelStrip": "Channel Strip",
    "EffectCategory::Saturation": "Saturator",
    "EffectCategory::Reverb": "Reverb",
    "EffectCategory::Delay": "Delay",
    "EffectCategory::Modulation": "Modulation",
    "EffectCategory::Pitch": "Pitch",
    "EffectCategory::AmpSimulator": "Amp Simulator",
    "EffectCategory::Mastering": "Mastering",
    "EffectCategory::Metering": "Meter",
    "EffectCategory::StereoWidth": "Imager",
    "EffectCategory::LoFi": "Lo-Fi",
    "EffectCategory::Restoration": "Restoration",
    "EffectCategory::Sequencer": "Sequencer",
    "EffectCategory::Unknown": "",
}

ERA_MAP = {
    "Era::Era_1950s": "1950s",
    "Era::Era_1960s": "1960s",
    "Era::Era_1970s": "1970s",
    "Era::Era_1980s": "1980s",
    "Era::Era_1990s": "1990s",
    "Era::Era_2000s": "2000s",
    "Era::Era_2010s": "2010s",
    "Era::Era_2020s": "2020s",
    "Era::Modern": "Modern",
}

SUBCATEGORY_MAP = {
    # Compressor types
    "CompressorType::Optical": "Opto",
    "CompressorType::VCA": "VCA",
    "CompressorType::FET": "FET",
    "CompressorType::Tube": "Tube",
    "CompressorType::Bus": "Bus",
    "CompressorType::MultiBand": "Multi-band",
    "CompressorType::Mastering": "Mastering",
    # Channel strip types
    "ChannelStripType::SSL": "SSL",
    "ChannelStripType::Neve": "Neve",
    "ChannelStripType::AMEK": "AMEK",
    "ChannelStripType::Focusrite": "Focusrite",
    "ChannelStripType::Vintage": "Vintage",
    # Amp types
    "AmpType::German": "German",
    "AmpType::American": "American",
    "AmpType::British": "British",
    "AmpType::BassAmp": "Bass",
    "AmpType::HighGain": "High Gain",
    # Reverb types
    "ReverbType::Hall": "Hall",
    "ReverbType::Plate": "Plate",
    "ReverbType::Room": "Room",
    "ReverbType::Spring": "Spring",
    "ReverbType::Algorithmic": "Algorithmic",
    # Delay types
    "DelayType::Tape": "Tape",
    "DelayType::Digital": "Digital",
    "DelayType::Analog": "Analog",
    # EQ types
    "EQType::Parametric": "Parametric",
    "EQType::Graphic": "Graphic",
    "EQType::Dynamic": "Dynamic",
    "EQType::Passive": "Passive",
    "EQType::Console": "Console",
    # Special processing
    "SpecialProcessingType::Gate": "Gate",
    "SpecialProcessingType::TransientShaper": "Transient",
    "SpecialProcessingType::Imagers": "Stereo",
    "SpecialProcessingType::DeEsser": "De-Esser",
    "SpecialProcessingType::LoFi": "Lo-Fi",
}


def extract_mappings(cpp_content: str, map_name: str, value_map: dict) -> dict:
    """Extract mappings from a C++ static map."""
    results = {}

    # Find the map definition
    pattern = rf'static const std::map<[^>]+>\s+{map_name}\s*=\s*\{{'
    match = re.search(pattern, cpp_content)
    if not match:
        return results

    start = match.end()

    # Find matching closing brace
    brace_count = 1
    i = start
    while i < len(cpp_content) and brace_count > 0:
        if cpp_content[i] == '{':
            brace_count += 1
        elif cpp_content[i] == '}':
            brace_count -= 1
        i += 1

    map_content = cpp_content[start:i-1]

    # Extract entries like {"name", Category::Value}
    entry_pattern = r'\{"([^"]+)",\s*([^}]+)\}'
    for name, value in re.findall(entry_pattern, map_content):
        value = value.strip()
        if value in value_map:
            results[name.lower()] = value_map[value]

    return results


def match_plugin(plugin_name: str, mappings: dict) -> str:
    """Find the best matching category/era for a plugin name."""
    name_lower = plugin_name.lower()

    # Try exact match first
    if name_lower in mappings:
        return mappings[name_lower]

    # Try partial matches
    for key, value in mappings.items():
        if key in name_lower or name_lower in key:
            return value

    return ""


def main():
    print("Loading plugins.json...")
    with open(PLUGINS_JSON, 'r', encoding='utf-8') as f:
        data = json.load(f)

    print("Loading PluginDatabase.cpp...")
    with open(DATABASE_CPP, 'r', encoding='utf-8') as f:
        cpp_content = f.read()

    # Extract all mappings
    print("Extracting category mappings...")
    category_mappings = extract_mappings(cpp_content, "pluginCategories", CATEGORY_MAP)
    print(f"  Found {len(category_mappings)} category mappings")

    print("Extracting era mappings...")
    era_mappings = extract_mappings(cpp_content, "pluginEras", ERA_MAP)
    print(f"  Found {len(era_mappings)} era mappings")

    # Extract subcategory mappings
    subcategory_mappings = {}
    for map_name in ["compressorTypes", "channelStripTypes", "ampTypes",
                     "reverbTypes", "delayTypes", "eqTypes", "specialProcessingTypes"]:
        sub_map = extract_mappings(cpp_content, map_name, SUBCATEGORY_MAP)
        subcategory_mappings.update(sub_map)
    print(f"  Found {len(subcategory_mappings)} subcategory mappings")

    # Update plugins
    updated = 0
    for plugin in data['plugins']:
        name = plugin['name']

        # Match category
        category = match_plugin(name, category_mappings)
        if category and not plugin.get('category'):
            plugin['category'] = category
            updated += 1

        # Match era and add to tags
        era = match_plugin(name, era_mappings)
        if era:
            tags = plugin.get('tags', [])
            if era not in tags:
                tags.append(era)
                plugin['tags'] = tags

        # Match subcategory and add to tags
        subcat = match_plugin(name, subcategory_mappings)
        if subcat:
            tags = plugin.get('tags', [])
            if subcat not in tags:
                tags.append(subcat)
                plugin['tags'] = tags

    # Save updated plugins.json
    print(f"\nUpdating {updated} plugins with categories...")
    with open(PLUGINS_JSON, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=2, ensure_ascii=False)

    print("Done!")

    # Print summary
    categories_assigned = sum(1 for p in data['plugins'] if p.get('category'))
    print(f"\nSummary:")
    print(f"  Total plugins: {len(data['plugins'])}")
    print(f"  With category: {categories_assigned}")
    print(f"  Without category: {len(data['plugins']) - categories_assigned}")


if __name__ == "__main__":
    main()
