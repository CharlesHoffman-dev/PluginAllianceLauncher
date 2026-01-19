import urllib.request
import ssl
import os
from PIL import Image
from io import BytesIO

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Remaining images from various sources
image_urls = {
    'fiedler_audio_dolby_atmos_composer': 'https://fiedler-audio.com/wp-content/uploads/2024/07/Composer_full.webp',
    'fiedler_audio_spacelab_interstellar': 'https://fiedler-audio.com/wp-content/uploads/2024/07/interstellar2.webp',
    'fiedler_audio_spacelab_beam': 'https://fiedler-audio.com/wp-content/uploads/2024/07/interstellar2.webp',
    'fiedler_audio_spacelab_ignition': 'https://fiedler-audio.com/wp-content/uploads/2024/07/interstellar2.webp',
    # Focusrite Red from B&H
    'focusrite_red2_red3': 'https://static.bhphoto.com/images/images1000x1000/1421685355_1117683.jpg',
    # Schoeps from their website
    'schoeps_double_ms': 'https://schoeps.de/fileadmin/user_upload/_processed_/5/8/csm_DoubleMS_PlugIn_3ad7b2f789.jpg',
    # Looptrotter - use SA2RATE 2 image as placeholder
    'looptrotter_monster': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300629_fe5b41c8-37fd-4fa6-a20e-831a09f0f481.png',
    # Lindell Retro - use ChannelX as placeholder
    'lindell_retro': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300456_0d993c3f-7a23-4d4e-9e9c-89e1ddd64a51.png',
}

thumb_dir = 'C:/Users/charl/PluginAllianceLauncher/Resources/Thumbnails'

def download_and_resize(url, output_path):
    """Download image and resize to thumbnail"""
    try:
        req = urllib.request.Request(url, headers={
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
            'Accept': 'image/*,*/*'
        })
        with urllib.request.urlopen(req, context=ctx, timeout=30) as response:
            image_data = response.read()

        with Image.open(BytesIO(image_data)) as img:
            if img.mode in ('RGBA', 'P', 'LA'):
                # Create white background for transparent images
                background = Image.new('RGB', img.size, (255, 255, 255))
                if img.mode == 'P':
                    img = img.convert('RGBA')
                background.paste(img, mask=img.split()[-1] if 'A' in img.mode else None)
                img = background
            elif img.mode != 'RGB':
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
