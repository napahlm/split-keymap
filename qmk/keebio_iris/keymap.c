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
 * MAC is toggled with FN + MAC and remembered in EEPROM across unplugging.
 */

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

enum layers { BASE, NAV, SYM, FN, MAC, MAC_NAV };

enum custom_keycodes {
    NO_TILD_S = SAFE_RANGE, /* dead keys on the Norwegian layout: tap the key, then space */
    NO_CIRC_S,
    NO_GRV_S,
    MAC_TOG,                /* toggle MAC and remember it */
};

typedef union {
    uint32_t raw;
    struct { bool mac : 1; };
} user_config_t;
static user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.raw = 0;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.mac) layer_on(MAC);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    switch (keycode) {
        case NO_TILD_S: tap_code16(NO_TILD); tap_code(KC_SPC); return false;
        case NO_CIRC_S: tap_code16(NO_CIRC); tap_code(KC_SPC); return false;
        case NO_GRV_S:  tap_code16(NO_GRV);  tap_code(KC_SPC); return false;
        case MAC_TOG:
            layer_invert(MAC);
            user_config.mac = layer_state_is(MAC);
            eeconfig_update_user(user_config.raw);
            return false;
    }
    return true;
}

/* MAC + NAV together activate MAC_NAV. */
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, NAV, MAC, MAC_NAV);
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
 * |PRTSC |      |      |      |      |      |                |      |      |      |      |      |      |
 * | WIN  | INS  |DELW< |DELW> | HOME | END  |                | PLAY | VOL+ | VOL- | MUTE | BRI+ | BRI- |
 * |      |      |  <-  |  ->  |  ^   | PGUP |                |      |ZOOM+ |ZOOM- |ZOOM0 |      |      |
 * |      | DEL  |WORD< |WORD> |  v   | PGDN |      |  |      |      |      |      |      |      |      |
 * `--------------------------'      | HELD |      |  |      |      |      '--------------------------'
 * DELW< / DELW> = delete word left / right. WORD< / WORD> = jump a word. WIN = next window of the same app (Alt+`).
 */
[NAV] = LAYOUT(
  KC_PSCR,    _______, _______,    _______,    _______, _______,                     _______, _______,    _______,    _______, _______, _______,
  A(NO_PIPE), KC_INS,  C(KC_BSPC), C(KC_DEL),  KC_HOME, KC_END,                      KC_MPLY, KC_VOLU,    KC_VOLD,    KC_MUTE, KC_BRIU, KC_BRID,
  _______,    _______, KC_LEFT,    KC_RGHT,    KC_UP,   KC_PGUP,                     _______, C(NO_PLUS), C(NO_MINS), C(NO_0), _______, _______,
  _______,    KC_DEL,  C(KC_LEFT), C(KC_RGHT), KC_DOWN, KC_PGDN, _______,   _______, _______, _______,    _______,    _______, _______, _______,
                                      _______, _______, _______,            _______, _______, _______
),

/* SYM (hold right thumb)
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      |      |      |      |      |      |                |      |      |      |      |      |      |
 * |      |  <   |  >   |  ~   |  $   |  %   |                |  `   |  !   |  ?   |      |  Å   |  €   |
 * |      |  (   |  )   |  {   |  }   |  |   |                |  "   |  +   |  -   |  =   |  Ø   |  ^   |
 * |      |  [   |  ]   |  \   |  &   |  *   |      |  |      |      |  @   |  _   |  #   |  Æ   |      |
 * `--------------------------'      |      |      |  |      | HELD |      '--------------------------'
 * Bracket pairs on resting finger pairs: < > above ( ) on Q W / A S, { } on D F, [ ] on Z X.
 * Right home row: " + - = from the inner reach outward, _ under the -. Å Ø Æ in one column under 0.
 */
[SYM] = LAYOUT(
  _______, _______, _______, _______,   _______, _______,                     _______,  _______, _______, _______, _______, _______,
  _______, NO_LABK, NO_RABK, NO_TILD_S, NO_DLR,  NO_PERC,                     NO_GRV_S, NO_EXLM, NO_QUES, _______, NO_ARNG, NO_EURO,
  _______, NO_LPRN, NO_RPRN, NO_LCBR,   NO_RCBR, NO_PIPE,                     NO_DQUO,  NO_PLUS, NO_MINS, NO_EQL,  NO_OSTR, NO_CIRC_S,
  _______, NO_LBRC, NO_RBRC, NO_BSLS,   NO_AMPR, NO_ASTR, _______,   _______, _______,  NO_AT,   NO_UNDS, NO_HASH, NO_AE,   _______,
                                   _______, _______, _______,            _______, _______, _______
),

/* FN (hold right outer thumb) - F-keys left, numpad right, RGB on the top row (wired board: no BT)
 * ,-----------------------------------------.                ,-----------------------------------------.
 * |      | RGB  | MODE | HUE+ | SAT+ | BRI+ |                |      |      |      |      |      | MAC  |
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                |  /   |  7   |  8   |  9   |  -   | BSPC |
 * |      |  F6  |  F7  |  F8  |  F9  | F10  |                |  *   |  4   |  5   |  6   |  +   | ENT  |
 * |      | F11  | F12  |  ´   |  ¨   |      |      |  |      |  0   |  1   |  2   |  3   |  .   |  =   |
 * `--------------------------'      |      |      |  |      |      | HELD '--------------------------'
 * Numpad sends plain digits so NumLock does not matter. ´ and ¨ are dead keys for accents (´ e = é).
 */
[FN] = LAYOUT(
  _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU,                     _______, _______, _______, _______, _______, MAC_TOG,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       NO_SLSH, NO_7,    NO_8,    NO_9,    NO_MINS, KC_BSPC,
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                      NO_ASTR, NO_4,    NO_5,    NO_6,    NO_PLUS, KC_ENT,
  _______, KC_F11,  KC_F12,  NO_ACUT, NO_DIAE, _______, _______,   _______, NO_0,    NO_1,    NO_2,    NO_3,    NO_DOT,  NO_EQL,
                                   _______, _______, _______,            _______, _______, _______
),

/* MAC (FN + MAC, remembered) - a flag layer. GUI thumb is Cmd and the inner ALT key is Opt on macOS already,
 * so nothing moves; with NAV held this enables MAC_NAV, the Cmd/Opt variant of the OS-specific NAV keys.
 * TODO: Norwegian macOS layout uses different Option combos for @ $ { } [ ] | \ ; add a mac SYM when needed.
 */
[MAC] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,            _______, _______, _______
),

/* MAC_NAV (automatic while MAC and NAV are both on) - Cmd/Opt versions of the OS-specific NAV keys */
[MAC_NAV] = LAYOUT(
  _______,    _______, _______,    _______,    _______, _______,                     _______, _______,    _______,    _______, _______, _______,
  G(NO_LABK), _______, A(KC_BSPC), A(KC_DEL),  _______, _______,                     _______, _______,    _______,    _______, _______, _______,
  _______,    _______, _______,    _______,    _______, _______,                     _______, G(NO_PLUS), G(NO_MINS), G(NO_0), _______, _______,
  _______,    _______, A(KC_LEFT), A(KC_RGHT), _______, _______, _______,   _______, _______, _______,    _______,    _______, _______, _______,
                                      _______, _______, _______,            _______, _______, _______
)
};
