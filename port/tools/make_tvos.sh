#!/bin/bash
# Generates the Apple TV Xcode project (build/tvos/mssb.xcodeproj) and opens it.
#   bash port/tools/make_tvos.sh [TEAM_ID]
# The iPhone (build/ios) and Mac (build/port) builds are separate and untouched.
# Dawn has no tvOS package: its iOS package is downloaded once and retagged for tvOS
# (port/tools/retag_tvos.py; the Metal API is the same).
# Then in Xcode: scheme "mssb", your Apple TV as the destination, Run.
set -euo pipefail
cd "$(dirname "$0")/../.."
TEAM="${1:-${MSSB_IOS_TEAM:-}}"
DAWN_VER="$(grep -o 'AURORA_DAWN_VERSION "[^"]*"' port/extern/aurora/cmake/AuroraDependencyVersions.cmake | head -1 | cut -d'"' -f2)"
DEPS="$(pwd)/build/tvos-deps"
PKG="$DEPS/dawn-tvos-arm64.tar.gz"
if [ ! -f "$PKG" ]; then
    mkdir -p "$DEPS/dawn"
    echo "Fetching Dawn $DAWN_VER (iOS) and retagging it for tvOS..."
    curl -fL "https://github.com/encounter/dawn/releases/download/$DAWN_VER/dawn-ios-arm64.tar.gz" -o "$DEPS/dawn-ios.tar.gz"
    tar -xzf "$DEPS/dawn-ios.tar.gz" -C "$DEPS/dawn"
    find "$DEPS/dawn" -name '*.a' -exec python3 port/tools/retag_tvos.py {} +
    tar -czf "$PKG" -C "$DEPS/dawn" .
fi
TEAMARG=()
[ -n "$TEAM" ] && TEAMARG=(-DMSSB_IOS_TEAM="$TEAM") # remembered in build/tvos afterwards
cmake -S port -B build/tvos -G Xcode \
    -DCMAKE_SYSTEM_NAME=tvOS \
    -DCMAKE_OSX_SYSROOT=appletvos \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=17.0 \
    -DCMAKE_CONFIGURATION_TYPES=RelWithDebInfo \
    -DAURORA_DAWN_PROVIDER=package \
    -DAURORA_DAWN_PACKAGE_URL="file://$PKG" \
    ${TEAMARG[@]+"${TEAMARG[@]}"}
open build/tvos/mssb.xcodeproj
