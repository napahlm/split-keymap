# zmk-config - Aurora Lily58

ZMK firmware config for a wireless splitkb Aurora Lily58 (nice!nano v2, nice!view, underglow).
Keymap is tuned for shell work with the OS set to the Norwegian layout on every host.
The visual map is in `docs/keymap.html`.

## How this repo works

ZMK itself is not in this repo.
`config/west.yml` pulls ZMK and the `zmk-locales` module at build time, and `build.yaml` lists the three firmware images to build.
Every push triggers GitHub Actions, which builds the images and attaches them to the run as a `firmware` artifact.

## Flash

1. Push, wait for the Actions run to finish (about 5 to 10 minutes), download the `firmware` artifact and unzip it.
2. Plug the left half into USB. Double-tap the reset button. A drive named `NICENANO` appears.
3. Copy `splitkb_aurora_lily58_left-nice_nano_v2-zmk.uf2` onto it. The drive ejects itself when done.
4. Repeat for the right half with the `_right` image.
5. First time only, or if the halves stop talking: flash `settings_reset-nice_nano_v2-zmk.uf2` to both halves, then flash the real images again.

Pairing: hold FN and press 1 to 5 to pick a profile, then pair from the host.
The underglow colour follows the profile: red, green, blue, yellow, purple.

## Change the keymap

Edit `config/splitkb_aurora_lily58.keymap`, push, flash.
Symbols use the `NB_` key codes from `zmk-locales`, see `include/locale/keys_nb.h` in that repo for the full list.
