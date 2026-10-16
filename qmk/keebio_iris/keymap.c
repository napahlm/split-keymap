/*
 * Keebio Iris rev7 - Børge's dev keymap (QMK)
 *
 * Same layers as the Aurora Lily58 in ../../config/, except the thumb row:
 * the Iris has three thumb keys per half, so Alt moves to the inner row-4 key
 * and the duplicate thumb Backspace is dropped.
 *
 * OS keyboard layout on every host: Norwegian. Symbols use NO_ keycodes so
 * the firmware sends the right (AltGr) scancodes.
 *
 * Layers: BASE, NAV, SYM, FN, MAC, MAC_NAV (NAV + MAC, automatic)
 */

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers { BASE, NAV, SYM, FN, MAC, MAC_NAV };

/* Dead keys on the Norwegian layout: tap the key, then space, so the plain symbol comes out. */
enum custom_keycodes { NO_TILD_S = SAFE_RANGE, NO_CIRC_S, NO_GRV_S };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    switch (keycode) {
        case NO_TILD_S: tap_code16(NO_TILD); tap_code(KC_SPC); return false;
        case NO_CIRC_S: tap_code16(NO_CIRC); tap_code(KC_SPC); return false;
        case NO_GRV_S:  tap_code16(NO_GRV);  tap_code(KC_SPC); return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,-----------------------------------------.                ,-----------------------------------------.
 * | ESC  |  1   |  2   |  3   |  4   |  5   |                |  6   |  7   |  8   |  9   |  0   | BSPC |
 * | TAB  |  Q   |  W   |  E   |  R   |  T   |                |  Y   |  U   |  I   |  O   |  P   | DEL  |
 * | SHFT |  A   |  S   |  D   |  F   |  G   |                |  H   |  J   |  K   |  L   |  ;   |  '   |
 * | CTRL |  Z   |  X   |  C   |  V   |  B   | ALT  |  |  -   |  N   |  M   |  ,   |  .   |  /   | SHFT |
 * `--------------------------' GUI  | NAV  | SPC  |  | ENT  | SYM  | FN   '--------------------------'
 */
[BASE] = LAYOUT(
  KC_ESC,  NO_1,    NO_2,    NO_3,    NO_4,    NO_5,                        NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    KC_BSPC,
  KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,                        NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    KC_DEL,
  KC_LSFT, NO_A,    NO_S,    NO_D,    NO_F,    NO_G,                        NO_H,    NO_J,    NO_K,    NO_L,    NO_SCLN, NO_QUOT,
  KC_LCTL, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    KC_LALT,   NO_MINS, NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_SLSH, KC_RSFT,
                                KC_LGUI, MO(NAV), KC_SPC,            KC_ENT,  MO(SYM), MO(FN)
),

/* NAV (hold left thumb) - arrows on the left hand so the right hand stays on the mouse
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      |      |      |      |      |      |                |      |      |      |      |      |      |
 * | WIN  | INS  |C+BSP |C+DEL | PGUP | DEL  |                | PLAY | VOL- | VOL+ | MUTE | BRI- | BRI+ |
 * |      | HOME |  <-  |  ->  |  ^   | END  |                |ZOOM0 |      |      |      |      |      |
 * |      |PRTSC | C+<- | C+-> |  v   | PGDN |ZOOM+ |  |ZOOM- |      |      |      |      |      |      |
 * `--------------------------'      | HELD |      |  |      |      |      '--------------------------'
 * WIN = next window of the same app (Alt+` on Linux/GNOME).
 */
[NAV] = LAYOUT(
  _______,    _______, _______,    _______,    _______, _______,                        _______,    _______, _______, _______, _______, _______,
  A(NO_PIPE), KC_INS,  C(KC_BSPC), C(KC_DEL),  KC_PGUP, KC_DEL,                         KC_MPLY,    KC_VOLD, KC_VOLU, KC_MUTE, KC_BRID, KC_BRIU,
  _______,    KC_HOME, KC_LEFT,    KC_RGHT,    KC_UP,   KC_END,                         C(NO_0),    _______, _______, _______, _______, _______,
  _______,    KC_PSCR, C(KC_LEFT), C(KC_RGHT), KC_DOWN, KC_PGDN, C(NO_PLUS), C(NO_MINS), _______,   _______, _______, _______, _______, _______,
                                      _______, _______, _______,            _______, _______, _______
),

/* SYM (hold right thumb) - bracket pairs under ring+middle on the left, - _ = on the right home row
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      |      |      |      |      |      |                |      |      |      |      |      |      |
 * |      |  ~   |  <   |  >   |  $   |  %   |                |  ^   |  @   |  #   |  !   |  ?   |  Å   |
 * |      |  |   |  (   |  )   |  {   |  }   |                |  "   |  -   |  _   |  =   |  Ø   |  Æ   |
 * |      |  \   |  [   |  ]   |  &   |  *   |      |  |      |  +   |  `   |      |      |  €   |      |
 * `--------------------------'      |      |      |  |      | HELD |      '--------------------------'
 */
[SYM] = LAYOUT(
  _______, _______,   _______, _______, _______, _______,                     _______,   _______, _______, _______, _______, _______,
  _______, NO_TILD_S, NO_LABK, NO_RABK, NO_DLR,  NO_PERC,                     NO_CIRC_S, NO_AT,   NO_HASH, NO_EXLM, NO_QUES, NO_ARNG,
  _______, NO_PIPE,   NO_LPRN, NO_RPRN, NO_LCBR, NO_RCBR,                     NO_DQUO,   NO_MINS, NO_UNDS, NO_EQL,  NO_OSTR, NO_AE,
  _______, NO_BSLS,   NO_LBRC, NO_RBRC, NO_AMPR, NO_ASTR, _______,   _______, NO_PLUS,   NO_GRV_S,_______, _______, NO_EURO, _______,
                                   _______, _______, _______,            _______, _______, _______
),

/* FN (hold right outer thumb) - F-keys left, numpad right, RGB on the top row (wired board: no BT)
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      | RGB  | MODE | HUE+ | SAT+ | BRI+ |                |      |      |      |      |      | MAC  |
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                |  /   |  7   |  8   |  9   |  -   | BSPC |
 * |      |  F6  |  F7  |  F8  |  F9  | F10  |                |  *   |  4   |  5   |  6   |  +   | ENT  |
 * |      | F11  | F12  |      |      |      |      |  |      |  0   |  1   |  2   |  3   |  .   |  =   |
 * `--------------------------'      |      |      |  |      |      | HELD '--------------------------'
 */
[FN] = LAYOUT(
  _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU,                     _______, _______, _______, _______, _______, TG(MAC),
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_BSPC,
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_ENT,
  _______, KC_F11,  KC_F12,  _______, _______, _______, _______,   _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   NO_DOT,  NO_EQL,
                                   _______, _______, _______,            _______, _______, _______
),

/* MAC (toggle with FN + MAC) - Apple modifier order: inner row-4 key becomes Cmd, outer thumb becomes Opt,
 * so Cmd+Tab, Cmd+C/V, Cmd+-/+ sit where Alt+Tab, Ctrl+C/V, Ctrl+-/+ live on the other hosts. Pinky stays Ctrl.
 * TODO: Norwegian macOS layout uses different Option combos for @ $ { } [ ] | \ ; add a mac SYM when needed.
 */
[MAC] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_LGUI,   _______, _______, _______, _______, _______, _______, _______,
                                   KC_LALT, _______, _______,            _______, _______, _______
),

/* MAC_NAV (automatic while MAC and NAV are both held) - Cmd/Opt versions of the OS-specific NAV keys */
[MAC_NAV] = LAYOUT(
  _______,    _______, _______,    _______,    _______, _______,                        _______,    _______, _______, _______, _______, _______,
  G(NO_LABK), _______, A(KC_BSPC), A(KC_DEL),  _______, _______,                        _______,    _______, _______, _______, _______, _______,
  _______,    _______, _______,    _______,    _______, _______,                        G(NO_0),    _______, _______, _______, _______, _______,
  _______,    _______, A(KC_LEFT), A(KC_RGHT), _______, _______, G(NO_PLUS), G(NO_MINS), _______,   _______, _______, _______, _______, _______,
                                      _______, _______, _______,            _______, _______, _______
)
};

/* MAC + NAV together activate MAC_NAV. */
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, NAV, MAC, MAC_NAV);
}
