import re

# Read the original .jucer file
with open('C:/Users/charl/PluginAllianceLauncher/PluginAllianceLauncher.jucer', 'r', encoding='utf-8') as f:
    content = f.read()

# Read the new resources section
with open('C:/Users/charl/PluginAllianceLauncher/resources_section.txt', 'r', encoding='utf-8') as f:
    new_resources = f.read().strip()

# Find and replace the old Thumbnails group
# Pattern matches from <GROUP id="thumbnailsGroup" to its closing </GROUP>
pattern = r'<GROUP id="thumbnailsGroup" name="Thumbnails">.*?</GROUP>'
replacement = new_resources

# Replace using DOTALL to match across lines
new_content = re.sub(pattern, replacement, content, flags=re.DOTALL)

# Write the updated .jucer file
with open('C:/Users/charl/PluginAllianceLauncher/PluginAllianceLauncher.jucer', 'w', encoding='utf-8') as f:
    f.write(new_content)

print('Updated .jucer file with 232 thumbnail resources')
