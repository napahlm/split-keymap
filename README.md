# split-keymap

One keymap for two split keyboards:

- **Aurora Lily58** (splitkb, nice!nano v2, nice!view, wireless) running **ZMK** - `config/`
- **Keebio Iris rev7** (ATmega32U4, wired) running **QMK** - `qmk/keebio_iris/`

BASE, NAV, SYM and FN are identical on the main 4x6 block of both boards.
Only the thumb row differs: the Iris has three thumb keys per half, the Lily58 four.
The OS is set to the Norwegian layout on every host; the firmware emits Norwegian scancodes so symbols land where the map says.
The visual map is `docs/keymap.html`.

## Layers

| Layer | Hold | Content |
|---|---|---|
| BASE | - | QWERTY, number row, `; '` `, . /`, Shift/Ctrl on the left pinky column, Backspace/Delete top-right |
| NAV | left thumb | Arrows on S D F V (left hand, mouse stays in the right), Home/End on A/G, PgUp/PgDn on R/B, word jumps on X/C, word delete on W/E, media on the right |
| SYM | right thumb | Right home row `" - _ =` then Ø Æ; `^ @ # ! ? Å` above; `+` `` ` `` `€` below. Left: `~ < > $ %` / `| ( ) { }` / `\ [ ] & *` |
| FN | right outer thumb | F1-F12 left, numpad right. Lily58: Bluetooth host 1-5 with underglow colour, LED controls. Iris: RGB controls |
| MAC | FN + MAC toggle | Swaps Ctrl and Cmd |

Both shifts together: Caps Word.

## Build

### Lily58 (ZMK)

```sh
brew install cmake ninja dtc python3   # macOS, once
./build.sh
```

First run downloads ZMK, Zephyr and the Zephyr SDK into `.build-ws/` (a few GB, 10 to 20 minutes).
Output: `firmware/splitkb_aurora_lily58_left.uf2`, `..._right.uf2`, `settings_reset.uf2`.

### Iris rev7 (QMK)

```sh
brew install qmk/qmk/qmk   # macOS, once; brings avr-gcc
./qmk/build.sh
```

Output: `firmware/keebio_iris_rev7.hex`.

## Flash

### Lily58

1. Plug a half into USB, double-tap reset. A drive named `NICENANO` appears.
2. Copy the matching `.uf2` onto it (Finder may report error -36 when the board reboots mid-copy; the flash still went through).
3. Repeat for the other half.
4. If the halves stop talking: flash `settings_reset.uf2` to both, then the real images again.

Pairing: hold FN and press 1 to 5 to pick a profile, then pair from the host.
Underglow follows the profile: red, green, blue, yellow, purple.

### Iris rev7

The Iris is an ATmega32U4 with the Atmel DFU bootloader, so it takes a `.hex`, not a `.uf2`.

1. Open QMK Toolbox, load `firmware/keebio_iris_rev7.hex`, tick Auto-Flash.
2. Plug in the left half alone and press its reset button. Toolbox flashes it.
3. Repeat with the right half alone.
4. Reconnect the TRRS cable, plug USB into either half.

Or from a terminal: `qmk flash firmware/keebio_iris_rev7.hex` and press reset when prompted.

## Change the keymap

Lily58: edit `config/splitkb_aurora_lily58.keymap`; symbols use `NB_` key codes from `zmk-locales` (`include/locale/keys_nb.h`).
Iris: edit `qmk/keebio_iris/keymap.c`; symbols use `NO_` keycodes from QMK's `keymap_norwegian.h`.
Keep the main block identical on both.
