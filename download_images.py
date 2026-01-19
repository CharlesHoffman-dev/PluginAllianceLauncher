import json
import urllib.request
import ssl
import os
import re
import time

# Create SSL context
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

# Load plugins.json
with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'r', encoding='utf-8') as f:
    data = json.load(f)

output_dir = 'C:/Users/charl/PluginAllianceLauncher/Resources/Images'
os.makedirs(output_dir, exist_ok=True)

def sanitize_filename(name):
    """Convert plugin ID to safe filename"""
    return re.sub(r'[^a-zA-Z0-9_]', '_', name)

downloaded = 0
failed = []

for plugin in data['plugins']:
    plugin_id = plugin['id']
    image_url = plugin.get('imageUrl', '')

    if not image_url:
        failed.append((plugin_id, 'No URL'))
        continue

    # Determine file extension
    if '.png' in image_url.lower():
        ext = '.png'
    elif '.jpg' in image_url.lower() or '.jpeg' in image_url.lower():
        ext = '.jpg'
    else:
        ext = '.png'  # Default to PNG

    filename = sanitize_filename(plugin_id) + ext
    filepath = os.path.join(output_dir, filename)

    # Skip if already downloaded
    if os.path.exists(filepath):
        print(f'Skipping (exists): {plugin_id}')
        downloaded += 1
        continue

    try:
        print(f'Downloading: {plugin_id}...', end=' ')
        req = urllib.request.Request(image_url, headers={'User-Agent': 'Mozilla/5.0'})
        with urllib.request.urlopen(req, context=ctx, timeout=15) as response:
            image_data = response.read()
            with open(filepath, 'wb') as img_file:
                img_file.write(image_data)
        print('OK')
        downloaded += 1
        time.sleep(0.2)  # Be nice to the server
    except Exception as e:
        print(f'FAILED: {e}')
        failed.append((plugin_id, str(e)))

print(f'\n=== Summary ===')
print(f'Downloaded: {downloaded}')
print(f'Failed: {len(failed)}')

if failed:
    print('\nFailed downloads:')
    for pid, reason in failed:
        print(f'  {pid}: {reason}')

# Update plugins.json with local image paths
print('\nUpdating plugins.json with local image references...')
for plugin in data['plugins']:
    plugin_id = plugin['id']
    image_url = plugin.get('imageUrl', '')

    if image_url:
        if '.png' in image_url.lower():
            ext = '.png'
        elif '.jpg' in image_url.lower() or '.jpeg' in image_url.lower():
            ext = '.jpg'
        else:
            ext = '.png'

        # Store original URL and set local filename
        plugin['imageUrlRemote'] = image_url
        plugin['imageFile'] = sanitize_filename(plugin_id) + ext

with open('C:/Users/charl/PluginAllianceLauncher/plugins.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=2, ensure_ascii=False)

print('Done!')
