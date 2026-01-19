import os

thumb_dir = 'C:/Users/charl/PluginAllianceLauncher/Resources/Thumbnails'
files = sorted(os.listdir(thumb_dir))

print('      <GROUP id="thumbnailsGroup" name="Thumbnails">')
for f in files:
    if f.endswith(('.jpg', '.jpeg', '.png')):
        name = os.path.splitext(f)[0]
        # Create a valid XML id from the filename
        file_id = 'img_' + name.replace('-', '_').replace('.', '_')
        print(f'        <FILE id="{file_id}" name="{f}" compile="0" resource="1" file="Resources/Thumbnails/{f}"/>')
print('      </GROUP>')
