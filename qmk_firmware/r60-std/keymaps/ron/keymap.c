/* Copyright 2017 Ron Pedde <ron@pedde.com>
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
#include "r60-std.h"
#include "config.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#endif

#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer
     * ,-------------------------------------------------------------------------.
     * |Esc~|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   =|Backspac|
     * |-------------------------------------------------------------------------|
     * | Tab  |   Q|   W|   E|   R|   T|   Y|   U|   I|   O|   P|   [|   ]|   \  |
     * |-------------------------------------------------------------------------|
     * | Ctrl  |   A|   S|   D|   F|   G|   H|   J|   K|   L|   ;|   '| Return   |
     * |-------------------------------------------------------------------------|
     * |  Shift  |   Z|   X|   C|   V|   B|   N|   M|   ,|   .|   /|    Shift    |
     * |-------------------------------------------------------------------------|
     * |Ctrl |Meta |Supr |            Space            | FN1  | FN2  |Supr |Meta |
     * `-------------------------------------------------------------------------'
     */

    KEYMAP( /* Base */
        KC_GESC, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,  KC_6,  KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,  KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
        KC_LCTL, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,  KC_H,  KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,  KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
        KC_LCTL, KC_LALT, KC_LGUI,                 KC_SPC,                MO(1),   MO(2),   KC_RGUI, KC_RALT \
        ),
    /* Funcation
     * ,-------------------------------------------------------------------------.
     * |   `|  F1|  F2|  F3|  F4|  F5|  F6|  F7|  F8|  F9| F10| F11| F12| Del    |
     * |-------------------------------------------------------------------------|
     * |      |    |    |    |    |    |    |    |    |    |PWD |    |    |      |
     * |-------------------------------------------------------------------------|
     * |       |    |    |    |    |    |    |    |    |    |    |    |          |
     * |-------------------------------------------------------------------------|
     * |         |    |    |    |    |    |    |    |    |    |    |             |
     * |-------------------------------------------------------------------------|
     * |     |     |     |                             |      |      |     |RESET|
     * `-------------------------------------------------------------------------'
     */

    KEYMAP(
        KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL, \
        ______, ______, ______, KC_UP,  ______, ______, ______, ______, ______, ______, M(0),   ______, ______, ______, \
        ______, ______,KC_LEFT,KC_DOWN,KC_RGHT, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______,                 ______,                 ______, ______, ______, RESET \
        ),

    KEYMAP(
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______,KC_PGUP, ______, ______, ______, ______, ______, ______, ______,   ______, ______, ______, \
        ______, ______,KC_HOME,KC_PGDN, KC_END, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, \
        ______, ______, ______,                 ______,                 ______, ______, ______, ______ \
        ),
};

#ifdef AUDIO_ENABLE
float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_goodbye[][2]    = SONG(GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif



const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                SEND_STRING("@@password0@@");
                return false;
        }
    }
    return MACRO_NONE;
};


void matrix_scan_user(void) {
};

void matrix_init_user(void) {
#ifdef AUDIO_ENABLE
        startup_user();
#endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif
