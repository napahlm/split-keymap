#!/usr/bin/env bash
# Build the Keebio Iris rev7 firmware (QMK) locally.
# First run clones qmk_firmware into ../.build-ws/qmk_firmware and needs avr-gcc on PATH
# (macOS: brew install qmk/qmk/qmk, which brings the AVR toolchain; or `qmk setup`).
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
WS="$ROOT/.build-ws"
OUT="$ROOT/firmware"
KB=keebio/iris/rev7
KM=borge

mkdir -p "$WS" "$OUT"
cd "$WS"

if ! command -v qmk >/dev/null; then
  python3 -m venv .qmk-venv
  # shellcheck disable=SC1091
  source .qmk-venv/bin/activate
  pip install -q "setuptools<72" wheel qmk
fi

if [ ! -d qmk_firmware ]; then
  git clone -q --depth 1 https://github.com/qmk/qmk_firmware
  (cd qmk_firmware && git submodule update --init --depth 1 lib/lufa lib/printf)
fi

rm -rf "qmk_firmware/keyboards/keebio/iris/keymaps/$KM"
cp -r "$ROOT/qmk/keebio_iris" "qmk_firmware/keyboards/keebio/iris/keymaps/$KM"

(cd qmk_firmware && qmk compile -kb "$KB" -km "$KM")
cp "qmk_firmware/keebio_iris_rev7_${KM}.hex" "$OUT/keebio_iris_rev7.hex"

echo
echo "Firmware in $OUT:"
ls -1 "$OUT"
