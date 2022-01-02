/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _ESC,
  _TAB,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV
};

// TODO (someday?): TERM_ON, TERM_OFF, MIDI_ON, MIDI_OFF, VOICE+, VOICE-, AUDIO_ON, AUDIO_OFF

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab/2|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc/1|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Ent/Sh|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  |   \  |   [  |    Space    |   ]  |   /  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    LT(2, KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LT(1, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   RSFT_T(KC_ENT),
    KC_LCTL,       KC_LALT, KC_LGUI, KC_BSLS, KC_LBRC, KC_SPC,  KC_SPC,  KC_RBRC, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Esc
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | xxxx |      |      |RGB_MD| Sat+ | Brt+ | Hue+ |Mac2Rc|MacStp|Mac2Pl|   -  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Debug| Reset| RGB  | Sat- | Brt- | Hue- |Mac1Rc|MacStp|Mac1Pl| PgUp | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Brite | Prev |    Play     | Next |      | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_ESC] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    _______, _______, _______, RGB_MOD, RGB_SAI, RGB_VAI, RGB_HUI, DM_REC2, DM_RSTP, DM_PLY2, KC_MINS, KC_EQL,
    _______, DEBUG,   RESET,   RGB_TOG, RGB_SAD, RGB_VAD, RGB_HUD, DM_REC1, DM_RSTP, DM_PLY1, KC_PGUP, KC_ENT,
    _______, _______, _______, BACKLIT, KC_MPRV, KC_MPLY, KC_MPLY, KC_MNXT, _______, KC_HOME, KC_PGDN, KC_END
),

/* Tab
 * ,-----------------------------------------------------------------------------------.
 * | xxxx |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  F11 |  F12 |      |      |      |      |      |      | MBck | MClk | MFwd |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Debug| Reset|      |      |      |      |MusTog|MusMod| LClk | MsUp | RClk |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Vol- |    Mute     | Vol+ |      | MsLt | MsDn | MsRt |
 * `-----------------------------------------------------------------------------------'
 */
[_TAB] = LAYOUT_planck_grid(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,      KC_F10,     KC_DEL,
    KC_ESC,  KC_F11,  KC_F12,  _______, _______,  _______, _______, _______, _______, KC_MS_BTN4, KC_MS_BTN3, KC_MS_BTN5,
    _______, DEBUG,   RESET,   _______, _______,  _______, _______, MU_TOG,  MU_MOD,  KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,
    _______, _______, _______, _______, KC_VOLD,  KC_MUTE, KC_MUTE, KC_VOLU, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}
