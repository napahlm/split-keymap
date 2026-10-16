#pragma once

/* Both shifts together: Caps Word, for ENV_VARS and CONSTANTS. */
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000

/* Solid colour at boot instead of the rainbow swirl, dimmed to save the USB budget. */
#undef RGBLIGHT_DEFAULT_MODE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE 120
#define RGB_MATRIX_DEFAULT_VAL 60
