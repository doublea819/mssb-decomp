#!/bin/bash
# Generates the iPhone Xcode project (build/ios/mssb.xcodeproj) and opens it.
#   port/tools/make_ios.sh [TEAM_ID]
# TEAM_ID: your Apple developer team (Xcode > Settings > Accounts, or leave it
# out and pick the team in the target's Signing & Capabilities tab).
# Then in Xcode: scheme "mssb", your iPhone as the destination, Run.
# The disc image (../Mario Superstar Baseball (USA).iso) is copied into the app.
set -euo pipefail
cd "$(dirname "$0")/../.."
TEAM="${1:-${MSSB_IOS_TEAM:-}}"
TEAMARG=()
[ -n "$TEAM" ] && TEAMARG=(-DMSSB_IOS_TEAM="$TEAM") # remembered in build/ios afterwards
cmake -S port -B build/ios -G Xcode \
    -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_SYSROOT=iphoneos \
    -DCMAKE_OSX_ARCHITECTURES=arm64 \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=17.0 \
    -DCMAKE_CONFIGURATION_TYPES=RelWithDebInfo \
    "${TEAMARG[@]}"
open build/ios/mssb.xcodeproj
