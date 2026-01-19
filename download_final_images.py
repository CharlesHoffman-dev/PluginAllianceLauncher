import urllib.request
import ssl
import os
from PIL import Image
from io import BytesIO

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Corrected image URLs from web scraping
image_urls = {
    'ada_std1': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300258_e4416d1c-8f75-4683-8195-cc03447e59a0.png',
    'brainworx_bx_delay_2500': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300340_a4f01894-db7b-4d8a-93f4-3ada49c34241.png',
    'brainworx_bx_refinement': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300274.png',
    'brainworx_bx_ssl_v2': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300262.png',
    'fiedler_audio_dolby_atmos_composer': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300410.png',
    'fiedler_audio_spacelab_interstellar': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300516_ba88f00a-b2dc-49af-be33-5cdf43d64d51.png',
    'fiedler_audio_spacelab_beam': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300516_ba88f00a-b2dc-49af-be33-5cdf43d64d51.png',
    'fiedler_audio_spacelab_ignition': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300516_ba88f00a-b2dc-49af-be33-5cdf43d64d51.png',
    'focusrite_red2_red3': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300241_9157b7c4-e2b9-4ad3-87f9-58e7e4ac1a02.png',
    'fuchs_train_45': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300256_c70e1be7-9dc5-4f18-8c76-b4e462f00e45.png',
    'gallien_krueger_800rb': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300351_9869025a-e5c3-4f1a-bb8c-8c5e7c1c1791.png',
    'lindell_retro': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300535_f4d5b9d7-aba0-4a31-8e0b-61cce47e0a4a.png',
    'looptrotter_monster': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300459_b4a9c7d4-0f1b-4e2e-8cef-daeee4f8e0a6.png',
    'schoeps_double_ms': 'https://schoeps.de/fileadmin/user_upload/_processed_/5/8/csm_DoubleMS_PlugIn_9e5c8e5c68.jpg',
    'three_body_technology_cenozoix_compressor': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300982_3397fcd0-2e7b-4b96-b08b-5d82fa4c3528.png',
}

thumb_dir = 'C:/Users/charl/PluginAllianceLauncher/Resources/Thumbnails'

def download_and_resize(url, output_path):
    """Download image and resize to thumbnail"""
    try:
        req = urllib.request.Request(url, headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'})
        with urllib.request.urlopen(req, context=ctx, timeout=30) as response:
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

downloaded = 0
failed = []

for plugin_id, url in image_urls.items():
    jpg_name = plugin_id + '.jpg'
    output_path = os.path.join(thumb_dir, jpg_name)

    # Check if already exists
    if os.path.exists(output_path):
        print(f'{plugin_id}: Already exists, skipping')
        continue

    print(f'Downloading: {plugin_id}...', end=' ')

    if download_and_resize(url, output_path):
        print('OK')
        downloaded += 1
    else:
        print('FAILED')
        failed.append(plugin_id)

print(f'\n=== Summary ===')
print(f'Downloaded: {downloaded}')
print(f'Failed: {len(failed)}')

if failed:
    print('\nStill missing:')
    for pid in failed:
        print(f'  {pid}')
