import json
import urllib.request
import re
import ssl
import time

# Create SSL context
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Plugin to URL slug mapping
url_slugs = {
    'AMEK EQ 250': 'amek_eq_250',
    'Ampeg SVTVR Classic': 'ampeg_svtvr_classic',
    'Arousor': 'spl_arousor',
    'Arousor Lt': 'spl_arousor_lt',
    'Bettermaker BM60': 'bettermaker_bm60',
    'Bettermaker Bus Compressor': 'bettermaker_bus_compressor',
    'Bettermaker Bus Compressor DSP': 'bettermaker_bus_compressor',
    'Bettermaker C502V DSP': 'bettermaker_c502v',
    'Bettermaker Mastering Compressor DSP': 'bettermaker_mastering_compressor',
    'Bettermaker Passive Equalizer': 'bettermaker_peq1',
    'Dangerous BAX EQ Master': 'dangerous_bax_eq',
    'ENGL E765 RT': 'engl_e765_rt',
    'Friedman BE100': 'friedman_be100',
    'Fuchs Train II': 'fuchs_train_ii',
    'Kiive Tape Face': 'kiive_tape_face',
    'Kiive Xtressor': 'kiive_xtressor',
    'Knif Audio Knifonium': 'knif_knifonium',
    'Lindell 354E': 'lindell_354e',
    'Lindell 50 Buss': 'lindell_50_series',
    'Lindell 50 Channel': 'lindell_50_series',
    'Lindell 69 Buss': 'lindell_69_series',
    'Lindell 69 Channel': 'lindell_69_series',
    'Lindell 80 Bus': 'lindell_80_series',
    'Lindell 80 Channel': 'lindell_80_series',
    'Lindell 902 De-esser': 'lindell_902_de-esser',
    'Lindell ChannelX': 'lindell_channelx',
    'Lindell MBC': 'lindell_mbc',
    'Lindell MU-66': 'lindell_mu-66',
    'Lindell SBC': 'lindell_sbc',
    'Lindell TE-100': 'lindell_te-100',
    'Looptrotter SA2RATE2': 'looptrotter_sa2rate_2',
    'Maag EQ2': 'maag_eq2',
    'Maag MAGNUM-K': 'maag_magnum-k',
    'Millennia TCL-2': 'millennia_tcl-2',
    'NEOLD OLDTIMER': 'neold_oldtimer',
    'NEOLD WUNDERLICH': 'neold_wunderlich',
    'SPL De-Esser': 'spl_de-esser',
    'SPL De-Esser Dual-Band': 'spl_de-esser_dual-band',
    'SPL Passeq Single': 'spl_passeq',
    'Schoeps Mono Upmix 1to2': 'schoeps_mono_upmix',
    'Shadow Hills Class A Mastering Comp': 'shadow_hills_class_a_mastering_comp',
    'TBTECH Kirchhoff-EQ': 'tbt_kirchhoff-eq',
    'TBTECH Trinity Shaper': 'tbt_trinity_shaper',
    'Unfiltered Audio Bass Mint': 'unfiltered_audio_bass_mint',
    'Unfiltered Audio Dent 2': 'unfiltered_audio_dent_2',
    'bx_2098 EQ': 'bx_2098_eq',
    'bx_blackdist2': 'bx_blackdist2',
    'bx_bluechorus2': 'bx_bluechorus2',
    'bx_boom': 'bx_boom',
    'bx_boom V3': 'bx_boom',
    'bx_cleansweep Pro': 'bx_cleansweep_pro',
    'bx_cleansweep V2': 'bx_cleansweep_v2',
    'bx_clipper': 'bx_clipper',
    'bx_console AMEK 200': 'bx_console_amek_200',
    'bx_console AMEK 9099': 'bx_console_amek_9099',
    'bx_control V2': 'bx_control_v2',
    'bx_crispyscale': 'bx_crispytuner',
    'bx_crispytuner': 'bx_crispytuner',
    'bx_digital V3 mix': 'bx_digital_v3',
    'bx_dynEQ V2 Mono': 'bx_dyneq_v2',
    'bx_enhancer': 'bx_enhancer',
    'bx_glue': 'bx_glue',
    'bx_hybrid V2 mix': 'bx_hybrid_v2',
    'bx_limiter': 'bx_limiter',
    'bx_masterdesk True Peak': 'bx_masterdesk',
    'bx_megadual': 'bx_megadual',
    'bx_megasingle': 'bx_megasingle',
    'bx_metal2': 'bx_metal2',
    'bx_oberhausen': 'bx_oberhausen',
    'bx_rockergain100': 'bx_rockergain100',
    'bx_rockrack V3 Player': 'bx_rockrack_v3',
    'bx_rooMS': 'bx_rooms',
    'bx_solo': 'bx_solo',
    'bx_stereomaker': 'bx_stereomaker',
    'bx_tonebox': 'bx_tonebox',
    'bx_yellowdrive': 'bx_yellowdrive',
    'elysia alpha master': 'elysia_alpha_compressor',
    'elysia alpha mix': 'elysia_alpha_compressor',
    'elysia karacter master': 'elysia_karacter',
    'elysia karacter mix': 'elysia_karacter',
    'elysia museq master': 'elysia_museq',
    'elysia nvelope': 'elysia_nvelope',
    'elysia phils cascade': 'elysia_phil_s_cascade',
    'fiedler audio spacelab beam': 'fiedler_audio_spacelab_interstellar',
    'fiedler audio spacelab ignition': 'fiedler_audio_spacelab_ignition',
    'fiedler audio splat': 'fiedler_audio_splat',
}

def fetch_image_url(slug):
    url = f'https://www.plugin-alliance.com/en/products/{slug}.html'
    try:
        req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
        with urllib.request.urlopen(req, context=ctx, timeout=10) as response:
            html = response.read().decode('utf-8')
            match = re.search(r'https://www\.plugin-alliance\.com/cdn/shop/files/productimage[^\"\'>\s]+', html)
            if match:
                return match.group(0)
    except Exception as e:
        pass
    return None

# Load JSON
with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

# Fetch and update images
updated = 0
for plugin in data['plugins']:
    vst_name = plugin['vstFileName']
    if vst_name in url_slugs and not plugin.get('imageUrl'):
        slug = url_slugs[vst_name]
        img = fetch_image_url(slug)
        if img:
            plugin['imageUrl'] = img
            plugin['url'] = f'https://www.plugin-alliance.com/en/products/{slug}.html'
            updated += 1
            print(f"Updated: {vst_name}")
        else:
            print(f"Failed: {vst_name}")
        time.sleep(0.3)

# Save
with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=2, ensure_ascii=False)

print(f"\nUpdated {updated} plugins with images.")
