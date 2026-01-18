# Plugin Data Workflow

This document explains how to edit and update plugin metadata for the Plugin Alliance Launcher.

## Overview

Plugin metadata (names, brands, descriptions, images, tags) is managed through a browser-based editor and automatically converted to C++ code via a build script.

**Workflow:**
1. Edit plugins in the HTML editor (`plugin-editor.html`)
2. Export to `plugins.json`
3. Run the Python build script
4. C++ header is generated automatically

## Files

| File | Purpose |
|------|---------|
| `plugins.json` | Source of truth for all plugin data |
| `plugin-editor.html` | Browser-based visual editor |
| `scripts/generate_plugin_data.py` | Converts JSON to C++ header |
| `Source/Data/PluginData.h` | Auto-generated C++ header (DO NOT EDIT) |

## How to Edit Plugin Data

### Step 1: Open the Editor

Open `plugin-editor.html` in any web browser (Chrome, Firefox, Edge).

### Step 2: Load the Data

Click **"Load JSON"** and select `plugins.json` from the project root.

### Step 3: Edit Plugins

- Use the **search box** to find plugins by name
- Use **sidebar filters** to filter by category, brand, or completion status
- Click on a plugin card to expand and edit its details:
  - **Brand**: The manufacturer (e.g., "Brainworx", "A/DA")
  - **Product**: The product name (e.g., "bx_console N", "Flanger")
  - **Description**: Short description of the plugin
  - **Category**: Primary effect type
  - **Tags**: Additional tags for filtering
  - **URLs**: Product page and thumbnail image URLs

### Step 4: Export

Click **"Export JSON"** to download the updated `plugins.json`. Replace the existing file in the project root.

### Step 5: Generate C++ Header

Run the Python script to generate the C++ header:

```bash
cd PluginAllianceLauncher
python scripts/generate_plugin_data.py
```

This creates/updates `Source/Data/PluginData.h`.

### Step 6: Rebuild

Rebuild the project in Visual Studio to include the updated plugin data.

## Plugin Data Schema

Each plugin in `plugins.json` has these fields:

```json
{
  "id": "ada_flanger",
  "name": "ADA Flanger",
  "brand": "A/DA",
  "product": "Flanger",
  "url": "https://www.plugin-alliance.com/...",
  "imageUrl": "https://www.plugin-alliance.com/...",
  "description": "Bucket-brigade analog flanging...",
  "category": "Modulation",
  "tags": ["Flanger", "Analog", "1970s"]
}
```

| Field | Description |
|-------|-------------|
| `id` | Unique identifier (auto-generated from name) |
| `name` | Full display name |
| `brand` | Manufacturer/brand name |
| `product` | Product name (without brand) |
| `url` | Product page URL |
| `imageUrl` | Thumbnail image URL |
| `description` | Short description (1-2 sentences) |
| `category` | Primary category |
| `tags` | Array of tags for filtering |

## Categories

Standard categories:
- Amp Simulator
- Channel Strip
- Compressor
- Delay
- Equalizer
- Gate
- Imager
- Limiter
- Lo-Fi
- Mastering
- Meter
- Modulation
- Multi-FX
- Pitch
- Restoration
- Reverb
- Saturator
- Utility
- Virtual Instrument

## Auto-Assign Tags

The editor has an **"Auto-Assign Tags"** button that attempts to automatically categorize plugins based on their names and descriptions. Review the results and adjust as needed.

## Tips

- The **"Missing Data"** filter shows plugins that need attention
- Use **drag and drop** to load JSON files
- Plugins are saved with **pagination** (20 per page) for performance
- The editor works completely offline - no server required

## For Developers

The generated `PluginData.h` provides:

```cpp
namespace PALauncher {
    struct PluginMetadata { ... };
    std::vector<PluginMetadata> getPluginDatabase();
    const PluginMetadata* findPluginMetadata(const juce::String& searchName);
}
```

Use `findPluginMetadata()` to look up plugin info by name or ID. It supports:
- Exact match by full name
- Exact match by ID
- Partial/substring matching
