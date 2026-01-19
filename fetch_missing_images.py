import json
import os
import re
import urllib.request
import ssl
import time
from PIL import Image
from io import BytesIO

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Plugin ID to URL slug mapping for fetching fresh images
url_slugs = {
    'acme_opticom_xla3': 'acme_opticom_xla-3',
    'ada_flanger': 'ada_flanger',
    'ada_std1': 'ada_std-1',
    'adptr_metricab': 'adptr_metricab',
    'adptr_sculpt': 'adptr_sculpt',
    'adptr_streamliner': 'adptr_streamliner',
    'amek_eq200': 'amek_eq_200',
    'amek_mastering_compressor': 'amek_mastering_compressor',
    'ampeg_b15n': 'ampeg_b15n',
    'ampeg_svt3pro': 'ampeg_svt3pro',
    'ampeg_svtvr': 'ampeg_svtvr',
    'ampeg_v4b': 'ampeg_v4b',
    'bettermaker_eq232d': 'bettermaker_eq232d',
    'black_box_hg2': 'black_box_analog_design_hg-2',
    'black_box_analog_design_hg_q': 'black_box_analog_design_hg-q',
    'brainworx_bx_aura': 'bx_aura',
    'brainworx_bx_bassdude': 'bx_bassdude',
    'brainworx_bx_console_focusrite': 'bx_console_focusrite_sc',
    'brainworx_bx_console_n': 'bx_console_n',
    'brainworx_bx_console_ssl_4000_e': 'bx_console_ssl_4000_e',
    'brainworx_bx_console_ssl_4000_g': 'bx_console_ssl_4000_g',
    'brainworx_bx_console_ssl_9000_j': 'bx_console_ssl_9000_j',
    'brainworx_bx_delay_2500': 'bx_delay_2500',
    'brainworx_bx_digital_v3': 'bx_digital_v3',
    'brainworx_bx_distorange': 'bx_distorange',
    'brainworx_bx_dynEQ_v2': 'bx_dyneq_v2',
    'brainworx_bx_greenscreamer': 'bx_greenscreamer',
    'brainworx_bx_hybrid_v2': 'bx_hybrid_v2',
    'brainworx_bx_limiter_true_peak': 'bx_limiter_true_peak',
    'brainworx_bx_masterdesk_classic': 'bx_masterdesk_classic',
    'brainworx_bx_masterdesk_pro': 'bx_masterdesk_pro',
    'brainworx_bx_meter': 'bx_meter',
    'brainworx_bx_opto': 'bx_opto',
    'brainworx_bx_opto_pedal': 'bx_opto_pedal',
    'brainworx_bx_panEQ': 'bx_paneq',
    'brainworx_bx_refinement': 'bx_refinement',
    'brainworx_bx_rockrack_v3': 'bx_rockrack_v3',
    'brainworx_bx_saturator_v2': 'bx_saturator_v2',
    'brainworx_bx_shredspread': 'bx_shredspread',
    'brainworx_bx_ssl_v2': 'bx_ssl_4000_e',
    'brainworx_bx_subfilter': 'bx_subfilter',
    'brainworx_bx_subsynth': 'bx_subsynth',
    'brainworx_bx_townhouse': 'bx_townhouse_buss_compressor',
    'brainworx_bx_tuner': 'bx_tuner',
    'brainworx_bx_xl_v2': 'bx_xl_v2',
    'brainworx_bx_xl_v3': 'bx_xl_v3',
    'dangerous_bax_eq': 'dangerous_bax_eq',
    'diezel_herbert': 'diezel_herbert',
    'ds_audio_thorn': 'ds_thorn',
    'elysia_alpha_compressor': 'elysia_alpha_compressor',
    'elysia_mpressor': 'elysia_mpressor',
    'elysia_museq': 'elysia_museq',
    'engl_savage_120': 'engl_savage_120',
    'fiedler_audio_dolby_atmos_composer': 'fiedler_audio_dolbyatmos_composer',
    'fiedler_audio_spacelab_interstellar': 'fiedler_audio_spacelab_interstellar',
    'fiedler_audio_stage': 'fiedler_audio_stage',
    'focusrite_red2_red3': 'focusrite_red_2_red_3',
    'friedman_buxom_betty': 'friedman_buxom_betty',
    'friedman_ds40': 'friedman_ds40',
    'fuchs_train_45': 'fuchs_train_45',
    'gallien_krueger_800rb': 'gallien-krueger_800rb',
    'hum_audio_laal': 'hum_audio_devices_laal',
    'kiive_xtcomp': 'kiive_xtcomp',
    'knif_audio_soma': 'knif_audio_soma',
    'lindell_254e': 'lindell_254e',
    'lindell_6x500': 'lindell_6x-500',
    'lindell_80_series': 'lindell_80_series',
    'lindell_pex500': 'lindell_pex-500',
    'lindell_retro': 'lindell_retro',
    'looptrotter_monster': 'looptrotter_monster_compressor',
    'maag_eq4': 'maag_eq4',
    'maag_audio_eq4_ms': 'maag_eq4_ms',
    'millennia_nseq2': 'millennia_nseq-2',
    'schoeps_double_ms': 'schoeps_double_ms',
    'spl_big': 'spl_big',
    'spl_machine_head': 'spl_machine_head',
    'three_body_technology_cenozoix_compressor': 'tbt_cenozoix',
    'unfiltered_audio_battalion': 'unfiltered_audio_battalion',
    'vertigo_vss_2': 'vertigo_vss-2',
    'fiedler_audio_spacelab_beam': 'fiedler_audio_spacelab_interstellar',
    'fiedler_audio_spacelab_ignition': 'fiedler_audio_spacelab_ignition',
}

def fetch_image_from_pa(slug):
    """Fetch image URL from Plugin Alliance product page"""
    url = f'https://www.plugin-alliance.com/en/products/{slug}.html'
    try:
        req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
        with urllib.request.urlopen(req, context=ctx, timeout=15) as response:
            html = response.read().decode('utf-8')
            # Try multiple patterns
            patterns = [
                r'https://www\.plugin-alliance\.com/cdn/shop/files/productimage[^"\'\s>]+',
                r'https://www\.plugin-alliance\.com/cdn/shop/files/[^"\'\s>]+\.(?:png|jpg|jpeg)',
            ]
            for pattern in patterns:
                match = re.search(pattern, html)
                if match:
                    return match.group(0)
    except Exception as e:
        pass
    return None

def download_and_resize(url, output_path):
    """Download image and resize to thumbnail"""
    try:
        req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0'})
        with urllib.request.urlopen(req, context=ctx, timeout=15) as response:
            image_data = response.read()

        with Image.open(BytesIO(image_data)) as img:
            if img.mode in ('RGBA', 'P'):
                img = img.convert('RGB')
            img.thumbnail((300, 300), Image.Resampling.LANCZOS)
            img.save(output_path, 'JPEG', quality=85, optimize=True)
        return True
    except Exception as e:
        print(f'    Error: {e}')
        return False

# Load plugins
with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

thumb_dir = 'C:/Users/charl/PluginAllianceLauncher/Resources/Thumbnails'
existing = set(os.listdir(thumb_dir))

# Find missing thumbnails
missing = []
for plugin in data['plugins']:
    plugin_id = plugin['id']
    jpg_name = plugin_id.replace('-', '_') + '.jpg'
    if jpg_name not in existing:
        missing.append(plugin)

print(f'Attempting to download {len(missing)} missing images...\n')

downloaded = 0
failed = []

for plugin in missing:
    plugin_id = plugin['id']
    jpg_name = plugin_id.replace('-', '_') + '.jpg'
    output_path = os.path.join(thumb_dir, jpg_name)

    print(f'Processing: {plugin_id}...', end=' ')

    # Try to get fresh URL from PA
    slug = url_slugs.get(plugin_id)
    if slug:
        img_url = fetch_image_from_pa(slug)
        if img_url:
            if download_and_resize(img_url, output_path):
                print('OK')
                downloaded += 1
                time.sleep(0.3)
                continue

    # Try existing URL from JSON
    img_url = plugin.get('imageUrl', '')
    if img_url and download_and_resize(img_url, output_path):
        print('OK (from JSON)')
        downloaded += 1
        time.sleep(0.3)
        continue

    print('FAILED')
    failed.append(plugin_id)

print(f'\n=== Summary ===')
print(f'Downloaded: {downloaded}')
print(f'Failed: {len(failed)}')

if failed:
    print('\nStill missing:')
    for pid in failed:
        print(f'  {pid}')
