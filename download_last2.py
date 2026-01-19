import urllib.request
import ssl
import os
from PIL import Image
from io import BytesIO

ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Last 2 images
image_urls = {
    'lindell_retro': 'https://www.plugin-alliance.com/cdn/shop/files/productimage-300175_b9f47d8b-15a3-4c65-9299-4baa15ee39cf.png',
    # Schoeps from KVR Audio or alternative
    'schoeps_double_ms': 'https://static.kvraudio.com/i/b/schoeps-double-ms.png',
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
