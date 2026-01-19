#!/usr/bin/env python3
"""
================================================================================
  Plugin Data Generator

  Converts plugins.json → Source/Data/PluginData.h

  Usage:
      python scripts/generate_plugin_data.py

  This generates a C++ header containing all plugin metadata. The launcher uses
  this data to display plugin information (descriptions, images, categories).
================================================================================

JSON Schema (plugins.json):
---------------------------
{
  "plugins": [
    {
      "id":          "unique_plugin_id",           // Required: Unique identifier
      "vstFileName": "Exact VST3 Name",            // Required: EXACT name the VST3 reports
      "displayName": "Display Name for UI",        // Required: Name shown in launcher UI
      "brand":       "Manufacturer Name",          // Required: Company/brand name
      "description": "Short description text.",    // Required: Plugin description
      "category":    "Compressors",                // Required: Primary category
      "imageUrl":    "https://...",                // Optional: Thumbnail image URL
      "url":         "https://...",                // Optional: Product page URL
      "tags":        ["tag1", "tag2"]              // Optional: Additional tags
    }
  ]
}

How Matching Works:
-------------------
When you click a plugin in the launcher, it looks up metadata by comparing the
VST3's reported name against the 'vstFileName' field in the database.

To find the exact VST3 name:
  1. Check your DAW's plugin manager
  2. Or look at the plugin's .vst3 folder name
  3. Or check the log file on your desktop after clicking plugins

If a plugin shows generic description, the vstFileName doesn't match.
"""

import json
from pathlib import Path
from datetime import datetime

# ==============================================================================
# Configuration
# ==============================================================================

SCRIPT_DIR = Path(__file__).parent
PROJECT_ROOT = SCRIPT_DIR.parent
PLUGINS_JSON = PROJECT_ROOT / "plugins.json"
OUTPUT_HEADER = PROJECT_ROOT / "Source" / "Data" / "PluginData.h"

# ==============================================================================
# Utility Functions
# ==============================================================================

def escape_cpp_string(s: str) -> str:
    """Escape a string for safe use in C++ string literals."""
    if not s:
        return ""
    return s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n')

# ==============================================================================
# Code Generation
# ==============================================================================

def generate_cpp_header(plugins: list) -> str:
    """Generate the complete C++ header file content."""

    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    # Header comment
    header = f'''/*
  ==============================================================================
    PluginData.h
    AUTO-GENERATED - DO NOT EDIT

    Generated: {timestamp}
    Source: plugins.json

    To update: Edit plugins.json then run: python scripts/generate_plugin_data.py
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <map>

namespace PALauncher
{{

// =============================================================================
// Plugin Metadata Structure
// =============================================================================

struct PluginMetadata
{{
    juce::String id;           // Unique identifier (e.g., "ada_flanger")
    juce::String vstFileName;  // Exact VST3 reported name - used for matching
    juce::String displayName;  // Name shown in UI
    juce::String brand;        // Manufacturer name
    juce::String description;  // Plugin description text
    juce::String imageUrl;     // Thumbnail image URL
    juce::String productUrl;   // Product page URL
    juce::String category;     // Primary category
    juce::StringArray tags;    // Additional tags
}};

// =============================================================================
// Plugin Database
// =============================================================================

inline const std::vector<PluginMetadata>& getPluginDatabase()
{{
    static const std::vector<PluginMetadata> database = {{
'''

    # Generate plugin entries
    entries = []
    for plugin in plugins:
        plugin_id = escape_cpp_string(plugin.get('id', ''))
        vst_name = escape_cpp_string(plugin.get('vstFileName', ''))
        display_name = escape_cpp_string(plugin.get('displayName', ''))
        brand = escape_cpp_string(plugin.get('brand', ''))
        description = escape_cpp_string(plugin.get('description', ''))
        image_url = escape_cpp_string(plugin.get('imageUrl', ''))
        product_url = escape_cpp_string(plugin.get('url', ''))
        category = escape_cpp_string(plugin.get('category', ''))
        tags = plugin.get('tags', [])

        tags_str = ', '.join([f'"{escape_cpp_string(t)}"' for t in tags])

        entry = f'''        {{
            "{plugin_id}",
            "{vst_name}",
            "{display_name}",
            "{brand}",
            "{description}",
            "{image_url}",
            "{product_url}",
            "{category}",
            {{{tags_str}}}
        }}'''
        entries.append(entry)

    header += ',\n'.join(entries)

    # Lookup function - simplified and clear
    header += '''
    };
    return database;
}

// =============================================================================
// Metadata Lookup Function
// =============================================================================
//
// Finds plugin metadata by matching the VST3's reported name.
//
// Matching priority:
//   1. Exact match on vstFileName (case-insensitive)
//   2. Exact match on displayName (case-insensitive)
//   3. Partial match - vstFileName contains search or vice versa
//
// Returns nullptr if no match found.
//

inline const PluginMetadata* findPluginMetadata(const juce::String& vstReportedName)
{
    static bool initialized = false;
    static std::map<juce::String, const PluginMetadata*> vstNameLookup;
    static std::map<juce::String, const PluginMetadata*> displayNameLookup;

    const auto& database = getPluginDatabase();

    // Build lookup tables on first call
    if (!initialized)
    {
        for (const auto& plugin : database)
        {
            // Index by vstFileName (primary match)
            auto vstLower = plugin.vstFileName.toLowerCase();
            if (vstNameLookup.find(vstLower) == vstNameLookup.end())
                vstNameLookup[vstLower] = &plugin;

            // Index by displayName (secondary match)
            auto displayLower = plugin.displayName.toLowerCase();
            if (displayNameLookup.find(displayLower) == displayNameLookup.end())
                displayNameLookup[displayLower] = &plugin;
        }
        initialized = true;
    }

    auto searchLower = vstReportedName.toLowerCase();

    // 1. Try exact match on vstFileName
    auto it = vstNameLookup.find(searchLower);
    if (it != vstNameLookup.end())
        return it->second;

    // 2. Try exact match on displayName
    it = displayNameLookup.find(searchLower);
    if (it != displayNameLookup.end())
        return it->second;

    // 3. Try partial match (for plugins with slightly different names)
    for (const auto& plugin : database)
    {
        if (plugin.vstFileName.containsIgnoreCase(vstReportedName) ||
            vstReportedName.containsIgnoreCase(plugin.vstFileName))
            return &plugin;
    }

    return nullptr;
}

} // namespace PALauncher
'''

    return header

# ==============================================================================
# Main Entry Point
# ==============================================================================

def main():
    print("=" * 60)
    print("  Plugin Data Generator")
    print("=" * 60)

    # Verify source file exists
    if not PLUGINS_JSON.exists():
        print(f"\nERROR: {PLUGINS_JSON} not found!")
        print("Create plugins.json with your plugin data.")
        return 1

    # Load plugin data
    print(f"\nReading: {PLUGINS_JSON}")
    with open(PLUGINS_JSON, 'r', encoding='utf-8') as f:
        data = json.load(f)

    plugins = data.get('plugins', [])
    print(f"Found: {len(plugins)} plugins")

    # Validate required fields
    errors = []
    for i, plugin in enumerate(plugins):
        missing = []
        for field in ['id', 'vstFileName', 'displayName', 'brand', 'description', 'category']:
            if not plugin.get(field):
                missing.append(field)
        if missing:
            errors.append(f"  Plugin #{i+1} ({plugin.get('id', 'unknown')}): missing {', '.join(missing)}")

    if errors:
        print(f"\nWARNING: Some plugins have missing required fields:")
        for err in errors[:10]:  # Show first 10
            print(err)
        if len(errors) > 10:
            print(f"  ... and {len(errors) - 10} more")

    # Generate header
    print(f"\nGenerating: {OUTPUT_HEADER}")
    OUTPUT_HEADER.parent.mkdir(parents=True, exist_ok=True)

    header_content = generate_cpp_header(plugins)

    with open(OUTPUT_HEADER, 'w', encoding='utf-8') as f:
        f.write(header_content)

    print(f"\nSUCCESS: Generated {OUTPUT_HEADER}")
    print(f"Total plugins: {len(plugins)}")
    print("\nNext steps:")
    print("  1. Rebuild the project")
    print("  2. Launch the app to test")
    print("=" * 60)

    return 0


if __name__ == "__main__":
    exit(main())
