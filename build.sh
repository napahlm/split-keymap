#!/usr/bin/env bash
# Build all three firmware images locally, no GitHub Actions needed.
# First run downloads ZMK, Zephyr and the Zephyr SDK (~2 GB) into ./.build-ws; later runs reuse it.
# Requires: python3, cmake, ninja, dtc (brew install cmake ninja dtc python3)
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
WS="$ROOT/.build-ws"
OUT="$ROOT/firmware"
BOARD="nice_nano@2.0.0//zmk"

mkdir -p "$WS" "$OUT"
cd "$WS"

python3 -m venv .venv >/dev/null 2>&1 || true
# shellcheck disable=SC1091
source .venv/bin/activate
pip install -q west

if [ ! -d .west ]; then
  ln -sfn "$ROOT/config" config
  west init -l config
fi
west update --narrow -o=--depth=1
west zephyr-export
pip install -q -r zephyr/scripts/requirements-base.txt

SDK_VER="$(cat zephyr/SDK_VERSION)"
if [ ! -d "$WS/zephyr-sdk" ]; then
  case "$(uname -s)-$(uname -m)" in
    Darwin-arm64)  PLAT=macos-aarch64 ;;
    Darwin-x86_64) PLAT=macos-x86_64 ;;
    Linux-x86_64)  PLAT=linux-x86_64 ;;
    Linux-aarch64) PLAT=linux-aarch64 ;;
    *) echo "unsupported host"; exit 1 ;;
  esac
  curl -L -o sdk.tar.xz "https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${SDK_VER}/zephyr-sdk-${SDK_VER}_${PLAT}_minimal.tar.xz"
  mkdir -p zephyr-sdk && tar -xf sdk.tar.xz -C zephyr-sdk --strip-components=1 && rm sdk.tar.xz
  (cd zephyr-sdk && ./setup.sh -t arm-zephyr-eabi -h -c)
fi
export ZEPHYR_SDK_INSTALL_DIR="$WS/zephyr-sdk"
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr

build() { # name shields
  west build -p -s zmk/app -d "build/$1" -b "$BOARD" -- -DSHIELD="$2" -DZMK_CONFIG="$ROOT/config"
  cp "build/$1/zephyr/zmk.uf2" "$OUT/$1.uf2"
}
build splitkb_aurora_lily58_left  "splitkb_aurora_lily58_left nice_view_adapter nice_view"
build splitkb_aurora_lily58_right "splitkb_aurora_lily58_right nice_view_adapter nice_view"
build settings_reset              "settings_reset"

echo
echo "Firmware in $OUT:"
ls -1 "$OUT"
