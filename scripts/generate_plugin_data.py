#!/usr/bin/env python3
"""
Generate C++ header file from plugins.json

Usage:
    python generate_plugin_data.py

This script reads plugins.json and generates Source/Data/PluginData.h
which contains all plugin metadata as compile-time constants.
"""

import json
import os
from pathlib import Path
from datetime import datetime

# Paths
SCRIPT_DIR = Path(__file__).parent
PROJECT_ROOT = SCRIPT_DIR.parent
PLUGINS_JSON = PROJECT_ROOT / "plugins.json"
OUTPUT_HEADER = PROJECT_ROOT / "Source" / "Data" / "PluginData.h"


def escape_cpp_string(s: str) -> str:
    """Escape a string for use in C++ code."""
    if not s:
        return ""
    return s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n')


def generate_header(plugins: list) -> str:
    """Generate the C++ header file content."""

    lines = []
    lines.append("/*")
    lines.append("  ==============================================================================")
    lines.append("    PluginData.h")
    lines.append("    AUTO-GENERATED FILE - DO NOT EDIT DIRECTLY")
    lines.append(f"    Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    lines.append("")
    lines.append("    Edit plugins.json and run: python scripts/generate_plugin_data.py")
    lines.append("  ==============================================================================")
    lines.append("*/")
    lines.append("")
    lines.append("#pragma once")
    lines.append("")
    lines.append("#include <JuceHeader.h>")
    lines.append("#include <vector>")
    lines.append("#include <map>")
    lines.append("")
    lines.append("namespace PALauncher")
    lines.append("{")
    lines.append("")
    lines.append("struct PluginMetadata")
    lines.append("{")
    lines.append("    juce::String id;           // Unique identifier (e.g., \"ada_flanger\")")
    lines.append("    juce::String brand;        // Brand name (e.g., \"A/DA\")")
    lines.append("    juce::String product;      // Product name (e.g., \"Flanger\")")
    lines.append("    juce::String fullName;     // Full display name (e.g., \"ADA Flanger\")")
    lines.append("    juce::String description;  // Short description")
    lines.append("    juce::String imageUrl;     // Thumbnail image URL")
    lines.append("    juce::String productUrl;   // Product page URL")
    lines.append("    juce::String category;     // Primary category")
    lines.append("    juce::StringArray tags;    // All tags (category, era, type, etc.)")
    lines.append("};")
    lines.append("")
    lines.append("inline std::vector<PluginMetadata> getPluginDatabase()")
    lines.append("{")
    lines.append("    return {")

    for i, plugin in enumerate(plugins):
        plugin_id = plugin.get('id', '')
        if not plugin_id:
            # Generate ID from name if not present
            name = plugin.get('name', '')
            plugin_id = name.lower().replace(' ', '_').replace('/', '_').replace('-', '_')

        brand = escape_cpp_string(plugin.get('brand', ''))
        product = escape_cpp_string(plugin.get('product', ''))
        full_name = escape_cpp_string(plugin.get('name', ''))
        description = escape_cpp_string(plugin.get('description', ''))
        image_url = escape_cpp_string(plugin.get('imageUrl', ''))
        product_url = escape_cpp_string(plugin.get('url', ''))
        category = escape_cpp_string(plugin.get('category', ''))
        tags = plugin.get('tags', [])

        # Build tags string array
        tags_str = ', '.join([f'"{escape_cpp_string(t)}"' for t in tags]) if tags else ''

        comma = "," if i < len(plugins) - 1 else ""

        lines.append(f'        {{')
        lines.append(f'            "{plugin_id}",')
        lines.append(f'            "{brand}",')
        lines.append(f'            "{product}",')
        lines.append(f'            "{full_name}",')
        lines.append(f'            "{description}",')
        lines.append(f'            "{image_url}",')
        lines.append(f'            "{product_url}",')
        lines.append(f'            "{category}",')
        lines.append(f'            {{{tags_str}}}')
        lines.append(f'        }}{comma}')

    lines.append("    };")
    lines.append("}")
    lines.append("")
    lines.append("// Lookup plugin metadata by various identifiers")
    lines.append("inline const PluginMetadata* findPluginMetadata(const juce::String& searchName)")
    lines.append("{")
    lines.append("    static std::vector<PluginMetadata> database = getPluginDatabase();")
    lines.append("    static bool initialized = false;")
    lines.append("    static std::map<juce::String, const PluginMetadata*> lookupByName;")
    lines.append("    static std::map<juce::String, const PluginMetadata*> lookupById;")
    lines.append("")
    lines.append("    if (!initialized)")
    lines.append("    {")
    lines.append("        for (const auto& plugin : database)")
    lines.append("        {")
    lines.append("            lookupByName[plugin.fullName.toLowerCase()] = &plugin;")
    lines.append("            lookupById[plugin.id.toLowerCase()] = &plugin;")
    lines.append("            // Also index by brand + product")
    lines.append("            lookupByName[(plugin.brand + \" \" + plugin.product).toLowerCase()] = &plugin;")
    lines.append("        }")
    lines.append("        initialized = true;")
    lines.append("    }")
    lines.append("")
    lines.append("    auto searchLower = searchName.toLowerCase();")
    lines.append("")
    lines.append("    // Try exact match by full name")
    lines.append("    auto it = lookupByName.find(searchLower);")
    lines.append("    if (it != lookupByName.end())")
    lines.append("        return it->second;")
    lines.append("")
    lines.append("    // Try by ID")
    lines.append("    it = lookupById.find(searchLower);")
    lines.append("    if (it != lookupById.end())")
    lines.append("        return it->second;")
    lines.append("")
    lines.append("    // Try partial match")
    lines.append("    for (const auto& plugin : database)")
    lines.append("    {")
    lines.append("        if (plugin.fullName.containsIgnoreCase(searchName) ||")
    lines.append("            searchName.containsIgnoreCase(plugin.fullName))")
    lines.append("            return &plugin;")
    lines.append("    }")
    lines.append("")
    lines.append("    return nullptr;")
    lines.append("}")
    lines.append("")
    lines.append("} // namespace PALauncher")
    lines.append("")

    return '\n'.join(lines)


def main():
    # Check if plugins.json exists
    if not PLUGINS_JSON.exists():
        print(f"Error: {PLUGINS_JSON} not found")
        print("Please create plugins.json or export it from the HTML editor")
        return 1

    # Load plugins
    print(f"Reading {PLUGINS_JSON}...")
    with open(PLUGINS_JSON, 'r', encoding='utf-8') as f:
        data = json.load(f)

    plugins = data.get('plugins', [])
    print(f"Found {len(plugins)} plugins")

    # Generate header
    print(f"Generating {OUTPUT_HEADER}...")
    header_content = generate_header(plugins)

    # Ensure output directory exists
    OUTPUT_HEADER.parent.mkdir(parents=True, exist_ok=True)

    # Write header
    with open(OUTPUT_HEADER, 'w', encoding='utf-8') as f:
        f.write(header_content)

    print(f"Successfully generated {OUTPUT_HEADER}")
    print(f"Total plugins: {len(plugins)}")

    return 0


if __name__ == "__main__":
    exit(main())
