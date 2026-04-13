// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

static bool is_alt_tab_active = false;
static uint16_t alt_tab_timer = 0;

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    ALT_SHIFT_TAB
};

enum layers {
    BASE,
    NAV,
    SYM,
    NUM
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    register_code(KC_LALT);
                    is_alt_tab_active = true;
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            }
            return false;

        case ALT_SHIFT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    register_code(KC_LALT);
                    is_alt_tab_active = true;
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active && timer_elapsed(alt_tab_timer) > 400) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, 1, 2, 3);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX, XXXXXXX,                      XXXXXXX,          XXXXXXX,    XXXXXXX,   XXXXXXX,      XXXXXXX,      XXXXXXX,
        XXXXXXX, KC_Q,       KC_W,       KC_E,          KC_R,    KC_T,                         KC_Y,             KC_U,       KC_I,      KC_O,         KC_P,         XXXXXXX,
        XXXXXXX, KC_A,       KC_S,       KC_D,          KC_F,    KC_G,                         KC_H,             KC_J,       KC_K,      KC_L,         KC_SCLN,      XXXXXXX,
        XXXXXXX, KC_Z,       KC_X,       KC_C,          KC_V,    KC_B,                         KC_N,             KC_M,       KC_COMM,   KC_DOT,       KC_SLSH,      XXXXXXX,
                                         MO(1),         KC_LSFT, KC_SPC,                       KC_BACKSPACE,     KC_ENTER,   MO(2)
    ),
    [NAV] = LAYOUT(
        _______, _______,    _______,    _______,       _______,      _______,                 _______,          _______,    _______,   _______,      _______,      _______,
        _______, KC_ESCAPE,  LCTL(KC_W), LCTL(KC_Y),    ALT_TAB,      ALT_SHIFT_TAB,           KC_PRINT_SCREEN,  KC_HOME,    KC_UP,     KC_END,       KC_BACKSPACE, _______,
        _______, LCTL(KC_A), LCTL(KC_S), LCTL(KC_F),    LCTL(KC_TAB), LCTL(LSFT(KC_TAB)),      LALT(LSFT(KC_F)), KC_LEFT,    KC_DOWN,   KC_RIGHT,     KC_ENTER,     _______,
        _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C),    KC_TAB,       LSFT(KC_TAB),            KC_CAPS,          KC_PAGE_UP, KC_DELETE, KC_PAGE_DOWN, XXXXXXX,      _______,
                                         _______,       _______,      _______,                 _______,          _______,    _______
    ),
    [SYM] = LAYOUT(
        _______, _______,    _______,    _______,       _______,       _______,                _______,          _______,    _______,   _______,      _______,      _______,
        _______, KC_ESCAPE,  KC_HASH,    KC_LBRC,       KC_RBRC,       KC_DQUO,                KC_LT,            KC_GT,      KC_EQL,    KC_EXLM,      KC_ASTR,      _______,
        _______, KC_AT,      KC_DLR,     LSFT(KC_LBRC), LSFT(KC_RBRC), KC_QUOT,                KC_UNDS,          KC_MINS,    KC_PLUS,   KC_SCLN,      KC_COLN,      _______,
        _______, KC_PERC,    KC_CIRC,    KC_LPRN,       KC_RPRN,       KC_GRV,                 KC_AMPR,          KC_DOT,     KC_COMM,   KC_BSLS,      KC_SLSH,      _______,
                                         _______,       _______,       _______,                _______,          _______,    _______
    ),
    [NUM] = LAYOUT(
        _______, _______,    _______,    _______,       _______,       _______,                _______,          _______,    _______,   _______,      _______,      _______,
        _______, KC_1,       KC_2,       KC_3,          KC_4,          KC_5,                   KC_6,             KC_7,       KC_8,      KC_9,         KC_0,         _______,
        _______, KC_LSFT,    KC_LCTL,    KC_LALT,       KC_LGUI,       KC_F11,                 KC_F12,           KC_RGUI,    KC_RALT,   KC_RSFT,      KC_RCTL,      _______,
        _______, KC_F1,      KC_F2,      KC_F3,         KC_F4,         KC_F5,                  KC_F6,            KC_F7,      KC_F8,     KC_F9,        KC_F10,       _______,
                                         _______,       _______,       _______,                _______,          _______,    _______
    )
};
