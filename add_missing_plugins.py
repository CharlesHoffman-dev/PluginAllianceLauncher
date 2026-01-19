import json
import re

with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# Missing plugins to add (vstFileName, brand, category, tags)
missing_plugins = [
    ('AMEK EQ 250', 'AMEK', 'Equalizers', ['1980s', 'Parametric']),
    ('Ampeg SVTVR Classic', 'Ampeg', 'Amplifiers', ['1960s']),
    ('Arousor', 'SPL', 'Compressors', ['Original']),
    ('Arousor Lt', 'SPL', 'Compressors', ['Original']),
    ('Bettermaker BM60', 'Bettermaker', 'Compressors', ['2020s']),
    ('Bettermaker Bus Compressor', 'Bettermaker', 'Compressors', ['2010s', 'Bus']),
    ('Bettermaker Bus Compressor DSP', 'Bettermaker', 'Compressors', ['2010s', 'Bus']),
    ('Bettermaker C502V DSP', 'Bettermaker', 'Compressors', ['2010s']),
    ('Bettermaker Mastering Compressor DSP', 'Bettermaker', 'Compressors', ['2010s', 'Mastering']),
    ('Bettermaker Passive Equalizer', 'Bettermaker', 'Equalizers', ['2010s', 'Passive']),
    ('Dangerous BAX EQ Master', 'Dangerous Music', 'Equalizers', ['2000s', 'Mastering']),
    ('ENGL E765 RT', 'ENGL', 'Amplifiers', ['2000s']),
    ('Friedman BE100', 'Friedman', 'Amplifiers', ['2010s']),
    ('Fuchs Train II', 'Fuchs Audio', 'Amplifiers', ['2000s']),
    ('Kiive Tape Face', 'Kiive Audio', 'Saturators', ['Original']),
    ('Kiive Xtressor', 'Kiive Audio', 'Compressors', ['Original']),
    ('Knif Audio Knifonium', 'Knif Audio', 'Synthesizers', ['2010s']),
    ('Lindell 354E', 'Lindell Audio', 'Compressors', ['1970s', 'Diode']),
    ('Lindell 50 Buss', 'Lindell Audio', 'Compressors', ['2010s', 'Bus']),
    ('Lindell 50 Channel', 'Lindell Audio', 'Channel Strips', ['2010s']),
    ('Lindell 69 Buss', 'Lindell Audio', 'Compressors', ['2010s', 'Bus']),
    ('Lindell 69 Channel', 'Lindell Audio', 'Channel Strips', ['2010s']),
    ('Lindell 80 Bus', 'Lindell Audio', 'Compressors', ['1980s', 'Bus']),
    ('Lindell 80 Channel', 'Lindell Audio', 'Channel Strips', ['1980s']),
    ('Lindell 902 De-esser', 'Lindell Audio', 'Vocal Processing', ['2010s']),
    ('Lindell ChannelX', 'Lindell Audio', 'Channel Strips', ['Original']),
    ('Lindell MBC', 'Lindell Audio', 'Compressors', ['Original', 'Multi-Band']),
    ('Lindell MU-66', 'Lindell Audio', 'Compressors', ['1960s', 'Tube']),
    ('Lindell SBC', 'Lindell Audio', 'Compressors', ['Original', 'Bus']),
    ('Lindell TE-100', 'Lindell Audio', 'Saturators', ['Original']),
    ('Looptrotter SA2RATE2', 'Looptrotter', 'Saturators', ['2010s']),
    ('Maag EQ2', 'Maag Audio', 'Equalizers', ['2010s']),
    ('Maag MAGNUM-K', 'Maag Audio', 'Compressors', ['2010s']),
    ('Millennia TCL-2', 'Millennia', 'Compressors', ['1990s', 'Tube']),
    ('NEOLD OLDTIMER', 'NEOLD', 'Delays', ['2020s']),
    ('NEOLD WUNDERLICH', 'NEOLD', 'Saturators', ['2020s']),
    ('SPL De-Esser', 'SPL', 'Vocal Processing', ['Original']),
    ('SPL De-Esser Dual-Band', 'SPL', 'Vocal Processing', ['Original']),
    ('SPL Passeq Single', 'SPL', 'Equalizers', ['2000s', 'Passive']),
    ('Schoeps Mono Upmix 1to2', 'Schoeps', '3D & Surround Sound', ['Original']),
    ('Shadow Hills Class A Mastering Comp', 'Shadow Hills', 'Compressors', ['2010s', 'Mastering']),
    ('TBTECH Kirchhoff-EQ', 'Three-Body Technology', 'Equalizers', ['Original', 'Parametric', 'Dynamic']),
    ('TBTECH Trinity Shaper', 'Three-Body Technology', 'Transient Shapers', ['Original']),
    ('Unfiltered Audio Bass Mint', 'Unfiltered Audio', 'Saturators', ['Original']),
    ('Unfiltered Audio Dent 2', 'Unfiltered Audio', 'Lo-Fi', ['Original']),
    # bx_ plugins
    ('bx_2098 EQ', 'Brainworx', 'Equalizers', ['1970s']),
    ('bx_blackdist2', 'Brainworx', 'Pedals', ['Original']),
    ('bx_bluechorus2', 'Brainworx', 'Modulator', ['Original']),
    ('bx_boom', 'Brainworx', 'Saturators', ['Original']),
    ('bx_boom V3', 'Brainworx', 'Saturators', ['Original']),
    ('bx_cleansweep Pro', 'Brainworx', 'Equalizers', ['Original']),
    ('bx_cleansweep V2', 'Brainworx', 'Equalizers', ['Original']),
    ('bx_clipper', 'Brainworx', 'Saturators', ['Original']),
    ('bx_console AMEK 200', 'Brainworx', 'Channel Strips', ['1970s']),
    ('bx_console AMEK 9099', 'Brainworx', 'Channel Strips', ['1990s']),
    ('bx_control V2', 'Brainworx', 'Meters', ['Original']),
    ('bx_crispyscale', 'Brainworx', 'Utility', ['Original']),
    ('bx_crispytuner', 'Brainworx', 'Vocal Processing', ['Original']),
    ('bx_digital V3 mix', 'Brainworx', 'Equalizers', ['Original', 'Mid-Side']),
    ('bx_dynEQ V2 Mono', 'Brainworx', 'Equalizers', ['Original', 'Dynamic']),
    ('bx_enhancer', 'Brainworx', 'Saturators', ['Original']),
    ('bx_glue', 'Brainworx', 'Compressors', ['Original']),
    ('bx_hybrid V2 mix', 'Brainworx', 'Equalizers', ['Original', 'Mid-Side']),
    ('bx_limiter', 'Brainworx', 'Limiters', ['Original']),
    ('bx_masterdesk True Peak', 'Brainworx', 'Mastering', ['Original']),
    ('bx_megadual', 'Brainworx', 'Amplifiers', ['Original']),
    ('bx_megasingle', 'Brainworx', 'Amplifiers', ['Original']),
    ('bx_metal2', 'Brainworx', 'Amplifiers', ['Original']),
    ('bx_oberhausen', 'Brainworx', 'Synthesizers', ['Original']),
    ('bx_rockergain100', 'Brainworx', 'Amplifiers', ['Original']),
    ('bx_rockrack V3 Player', 'Brainworx', 'Suites', ['Original']),
    ('bx_rooMS', 'Brainworx', 'Reverbs', ['Original']),
    ('bx_solo', 'Brainworx', 'Utility', ['Original']),
    ('bx_stereomaker', 'Brainworx', 'Stereo Imagers', ['Original']),
    ('bx_tonebox', 'Brainworx', 'Saturators', ['Original']),
    ('bx_yellowdrive', 'Brainworx', 'Pedals', ['1970s']),
    # elysia plugins
    ('elysia alpha master', 'elysia', 'Compressors', ['2000s', 'Mastering', 'VCA']),
    ('elysia alpha mix', 'elysia', 'Compressors', ['2000s', 'VCA']),
    ('elysia karacter master', 'elysia', 'Saturators', ['2000s']),
    ('elysia karacter mix', 'elysia', 'Saturators', ['2000s']),
    ('elysia museq master', 'elysia', 'Equalizers', ['2000s', 'Mastering']),
    ('elysia nvelope', 'elysia', 'Transient Shapers', ['2000s']),
    ('elysia phils cascade', 'elysia', 'Compressors', ['2000s']),
    # fiedler plugins
    ('fiedler audio spacelab beam', 'fiedler audio', 'Reverbs', ['Original']),
    ('fiedler audio spacelab ignition', 'fiedler audio', 'Reverbs', ['Original']),
    ('fiedler audio splat', 'fiedler audio', 'Utility', ['Original']),
]

def make_id(name):
    # Convert to lowercase, replace spaces with underscores
    id = name.lower().replace(' ', '_').replace('-', '_')
    # Remove special chars
    id = re.sub(r'[^a-z0-9_]', '', id)
    return id

def make_display_name(name, brand):
    # Remove brand from display name if it starts with it
    if name.lower().startswith(brand.lower()):
        name = name[len(brand):].strip()
    # Also remove common prefixes
    if name.startswith('_'):
        name = name[1:]
    return name

added = 0
for vst_name, brand, category, tags in missing_plugins:
    plugin_id = make_id(vst_name)
    display_name = make_display_name(vst_name, brand)

    new_plugin = {
        'id': plugin_id,
        'displayName': display_name,
        'brand': brand,
        'vstFileName': vst_name,
        'url': '',
        'imageUrl': '',
        'description': '',
        'category': category,
        'tags': tags
    }
    data['plugins'].append(new_plugin)
    added += 1

print(f'Added {added} new plugins.')

with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=2, ensure_ascii=False)

print('Saved to plugins.json')
