# zmk-config - Aurora Lily58

ZMK firmware config for a wireless splitkb Aurora Lily58 (nice!nano v2, nice!view, underglow).
Keymap is tuned for shell work with the OS set to the Norwegian layout on every host.
The visual map is in `docs/keymap.html`.

## How this repo works

ZMK itself is not in this repo.
`config/west.yml` pulls ZMK and the `zmk-locales` module at build time.
`config/splitkb_aurora_lily58.keymap` is the keymap, `config/splitkb_aurora_lily58.conf` the feature flags.

## Build

Locally, on macOS or Linux:

```sh
brew install cmake ninja dtc python3   # macOS, once
./build.sh
```

The first run downloads ZMK, Zephyr and the Zephyr SDK into `.build-ws/` (a few GB, 10 to 20 minutes).
Later runs take a minute or two.
The three images land in `firmware/`.

GitHub Actions is also wired up (`build.yaml` + `.github/workflows/build.yml`) and builds the same images on push, if you ever want that instead.

## Flash

1. Plug the left half into USB. Double-tap the reset button. A drive named `NICENANO` appears.
2. Copy `firmware/splitkb_aurora_lily58_left.uf2` onto it. The drive ejects itself when done.
3. Repeat for the right half with `splitkb_aurora_lily58_right.uf2`.
4. First time only, or if the halves stop talking: flash `settings_reset.uf2` to both halves, then flash the real images again.

Pairing: hold FN and press 1 to 5 to pick a profile, then pair from the host.
The underglow colour follows the profile: red, green, blue, yellow, purple.

## Change the keymap

Edit `config/splitkb_aurora_lily58.keymap`, run `./build.sh`, flash.
Symbols use the `NB_` key codes from `zmk-locales`, see `include/locale/keys_nb.h` in that repo for the full list.
