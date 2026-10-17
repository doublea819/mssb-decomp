#!/bin/bash
# Builds "Mario Superstar Baseball.app" (double-click / Dock) from build/port/mssb.
#   port/tools/make_mac_app.sh [icon.png]
# - The app goes in /Applications (or ~/Applications if that isn't writable).
# - The disc isn't copied: a link to it goes in the game's user folder
#   (~/Library/Application Support/Mario Superstar Baseball), where the game looks for it.
# - Saves (career.sav, the memory card) stay in that user folder, as before.
# Rerun after rebuilding the game to refresh the app.
set -euo pipefail
cd "$(dirname "$0")/../.."
REPO="$(pwd)"
ICON="${1:-}"
NAME="Mario Superstar Baseball"
ISO="$(cd .. && pwd)/Mario Superstar Baseball (USA).iso"
USERDIR="$HOME/Library/Application Support/$NAME"

ninja -C build/port

DEST=/Applications
[ -w "$DEST" ] || DEST="$HOME/Applications"
mkdir -p "$DEST"
APP="$DEST/$NAME.app"
rm -rf "$APP"
mkdir -p "$APP/Contents/MacOS" "$APP/Contents/Resources"
cp build/port/mssb "$APP/Contents/MacOS/mssb"
cp build/port/initial_pipeline_cache.db "$APP/Contents/Resources/"

ICONKEY=""
if [ -n "$ICON" ]; then
    SET="$(mktemp -d)/AppIcon.iconset"
    mkdir -p "$SET"
    for s in 16 32 128 256 512; do
        sips -s format png -z $s $s "$ICON" --out "$SET/icon_${s}x${s}.png" >/dev/null
        sips -s format png -z $((s * 2)) $((s * 2)) "$ICON" --out "$SET/icon_${s}x${s}@2x.png" >/dev/null
    done
    iconutil -c icns "$SET" -o "$APP/Contents/Resources/AppIcon.icns"
    cp "$ICON" "$REPO/port/tools/app_icon.png" 2>/dev/null || true # reused by later runs
    ICONKEY="<key>CFBundleIconFile</key><string>AppIcon</string>"
elif [ -f "$REPO/port/tools/app_icon.png" ]; then
    exec "$0" "$REPO/port/tools/app_icon.png"
fi

cat > "$APP/Contents/Info.plist" <<PLIST
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleName</key><string>$NAME</string>
  <key>CFBundleDisplayName</key><string>$NAME</string>
  <key>CFBundleIdentifier</key><string>com.doublea819.mssb</string>
  <key>CFBundleExecutable</key><string>mssb</string>
  <key>CFBundlePackageType</key><string>APPL</string>
  <key>CFBundleShortVersionString</key><string>1.0</string>
  <key>CFBundleVersion</key><string>$(date +%Y%m%d%H%M)</string>
  <key>LSMinimumSystemVersion</key><string>13.0</string>
  <key>LSApplicationCategoryType</key><string>public.app-category.sports-games</string>
  <key>NSHighResolutionCapable</key><true/>
  $ICONKEY
</dict>
</plist>
PLIST

# The disc, where the game looks for one (find_disc: the user folder).
mkdir -p "$USERDIR"
if [ -f "$ISO" ]; then
    find "$USERDIR" -maxdepth 1 -type l -name '*.iso' -delete
    ln -s "$ISO" "$USERDIR/$NAME (USA).iso"
else
    echo "warning: disc not found at $ISO (put the .iso in $USERDIR)"
fi

codesign --force --deep -s - "$APP" >/dev/null 2>&1 || true
touch "$APP"
echo "Built: $APP"
open -R "$APP"
