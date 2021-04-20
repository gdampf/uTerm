/*
 * ps2 table.c
 *
 * Created: March-24-16, 4:54:14 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee 
 *
 * All tables replaced Oct 2017 by Madis Kaal
 * Copyright (c) 2017 Madis Kaal
 *
 
 	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.

	If not, see http://www.gnu.org/licenses/gpl-3.0.en.html
 */ 

#include "ps2 table.h"

const uint8_t Scancode_Translations[] =
{
 0xff,0x43,0x41,0x3f,0x3d,0x3b,0x3c,0x58,0x64,0x44,0x42,0x40,0x3e,0x0f,0x29,0x59,
 0x65,0x38,0x2a,0x70,0x1d,0x10,0x02,0x5a,0x66,0x71,0x2c,0x1f,0x1e,0x11,0x03,0x5b,
 0x67,0x2e,0x2d,0x20,0x12,0x05,0x04,0x5c,0x68,0x39,0x2f,0x21,0x14,0x13,0x06,0x5d,
 0x69,0x31,0x30,0x23,0x22,0x15,0x07,0x5e,0x6a,0x72,0x32,0x24,0x16,0x08,0x09,0x5f,
 0x6b,0x33,0x25,0x17,0x18,0x0b,0x0a,0x60,0x6c,0x34,0x35,0x26,0x27,0x19,0x0c,0x61,
 0x6d,0x73,0x28,0x74,0x1a,0x0d,0x62,0x6e,0x3a,0x36,0x1c,0x1b,0x75,0x2b,0x63,0x76,
 0x55,0x56,0x77,0x78,0x79,0x7a,0x0e,0x7b,0x7c,0x4f,0x7d,0x4b,0x47,0x7e,0x7f,0x6f,
 0x52,0x53,0x50,0x4c,0x4d,0x48,0x01,0x45,0x57,0x4e,0x51,0x4a,0x37,0x49,0x46,0x54,
 0x80,0x81,0x82,0x41,0x54,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f
};


const keymap_t Altgr_Regular[] = 
{
 { 0x08, '{'},// (7&) 
 { 0x09, '['},// (8*) 
 { 0x0a, ']'},// (9()
 { 0x0b, '}'},// (0))
 { 0x0c, '\\'},// (-_)
 { 0x10, '@'},// (Q)
 { 0x1b, '~'},// (]})
 { 0x1d, LEFT_CONTROL_KEY},
 { 0x2a, LEFT_SHIFT_KEY},
 { 0x36, RIGHT_SHIFT_KEY},
 { 0x38, LEFT_ALT_KEY},
 { 0x56, '|'} //unlabelled key to the left or to the right of the left Alt key #56
};

const uint8_t Unshifted_Regular[] = 
{
 0, // nothing #00
 27, // esc #01
 '1',// (1!) #02
 '2',// (2@) #03
 '3',// (3#) #04
 '4',// (4$E) #05 
 '5',// (5%) #06 
 '6',// (6^) #07 
 '7',// (7&) #08 
 '8',// (8*) #09 
 '9',// (9() # 0a
 '0',// (0)) # 0b
 'ß',// (-_) # 0c
 '´',// (=+) # 0d
 8,// (Backspace) # 0e 
 9,// (Tab) # 0f
 'q',// (Q) # 10
 'w',// (W) # 11
 'e',// (E) # 12
 'r',// (R) # 13
 't',// (T) # 14
 'z',// (Y) # 15
 'u',// (U) # 16
 'i',// (I) # 17
 'o',// (O) # 18
 'p',// (P) # 19
 'ü',// ([{) # 1a
 '+',// (]}) # 1b
 13,// (Enter) # 1c
 LEFT_CONTROL_KEY,// (LCtrl) # 1d
 'a',// (A) # 1e
 's',// (S) # 1f
 'd',// (D) # 20
 'f',// (F) # 21
 'g',// (G) # 22
 'h',// (H) # 23
 'j',// (J) # 24
 'k',// (K) # 25
 'l',// (L) # 26
 'ö',// (;:) # 27
 'ä',// ('") # 28
 '^',// (`~) # 29
 LEFT_SHIFT_KEY,// (LShift) # 2a
 '#',// (\|) on a 102-key keyboard # 2b
 'y',// (Z) # 2c
 'x',// (X) # 2d
 'c',// (C) # 2e
 'v',// (V) # 2f
 'b',// (B) # 30
 'n',// (N) # 31
 'm',// (M) # 32
 ',',// (,<) # 33
 '.',// (.>) # 34
 '-',// (/?) # 35
 RIGHT_SHIFT_KEY,// (RShift) # 36
 '*',// (Keypad-*) or (*/PrtScn) on a 83/84-key keyboard # 37
 LEFT_ALT_KEY,// (LAlt) # 38
 ' ',// (Space bar) # 39
 CAPS_LOCK_KEY,// (CapsLock) # 3a
 F1_KEY,// (F1) # 3b
 F2_KEY,// (F2) # 3c
 F3_KEY,// (F3) # 3d
 F4_KEY,// (F4) # 3e
 F5_KEY,// (F5) # 3f
 F6_KEY,// (F6) # 40
 F7_KEY,// (F7) # 41
 F8_KEY,// (F8) # 42
 F9_KEY,// (F9) # 43
 F10_KEY,// (F10) # 44
 NUM_LOCK_KEY,// (NumLock) # 45
 SCROLL_LOCK_KEY,// (ScrollLock) # 46
 KEYPAD_KEY,// (Keypad-7/Home) # 47 
 KEYPAD_KEY,// (Keypad-8/Up) # 48
 KEYPAD_KEY,// (Keypad-9/PgUp) # 49
 KEYPAD_KEY,// (Keypad--) # 4a
 KEYPAD_KEY,// (Keypad-4/Left) # 4b 
 KEYPAD_KEY,// (Keypad-5) # 4c
 KEYPAD_KEY,// (Keypad-6/Right) # 4d 
 KEYPAD_KEY,// (Keypad-+) # 4e
 KEYPAD_KEY,// (Keypad-1/End) # 4f 
 KEYPAD_KEY,// (Keypad-2/Down) # 50
 KEYPAD_KEY,// (Keypad-3/PgDn) # 51
 KEYPAD_KEY,// (Keypad-0/Ins) # 52
 KEYPAD_KEY,// (Keypad-./Del) # 53
 0,// (Alt-SysRq) on a 84+ key keyboard # 54
 '^',// less common # 55
 '<', //unlabelled key to the left or to the right of the left Alt key #56
 F11_KEY, // F11 # 57
 F12_KEY // F12 # 58
 // anything with higher number is not standard and not recognized
};

const uint8_t Shifted_Regular[] =
{
 0, // nothing #00
 27, // esc #01
 '!',// (1!) #02
 '"',// (2@) #03
 '§',// (3#) #04
 '$',// (4$E) #05 
 '%',// (5%) #06 
 '&',// (6^) #07 
 '/',// (7&) #08 
 '(',// (8*) #09 
 ')',// (9() # 0a
 '=',// (0)) # 0b
 '?',// (-_) # 0c
 '`',// (=+) # 0d
 8,// (Backspace) # 0e 
 9,// (Tab) # 0f
 'Q',// (Q) # 10
 'W',// (W) # 11
 'E',// (E) # 12
 'R',// (R) # 13
 'T',// (T) # 14
 'Z',// (Y) # 15
 'U',// (U) # 16
 'I',// (I) # 17
 'O',// (O) # 18
 'P',// (P) # 19
 'Ü',// ([{) # 1a
 '*',// (]}) # 1b
 13,// (Enter) # 1c
 LEFT_CONTROL_KEY,// (LCtrl) # 1d
 'A',// (A) # 1e
 'S',// (S) # 1f
 'D',// (D) # 20
 'F',// (F) # 21
 'G',// (G) # 22
 'H',// (H) # 23
 'J',// (J) # 24
 'K',// (K) # 25
 'L',// (L) # 26
 'Ö',// (;:) # 27
 'Ä',// ('") # 28
 '°',// (`~) # 29
 LEFT_SHIFT_KEY,// (LShift) # 2a
 '\'',// (\|) on a 102-key keyboard # 2b
 'Y',// (Z) # 2c
 'X',// (X) # 2d
 'C',// (C) # 2e
 'V',// (V) # 2f
 'B',// (B) # 30
 'N',// (N) # 31
 'M',// (M) # 32
 ';',// (,<) # 33
 ':',// (.>) # 34
 '_',// (/?) # 35
 RIGHT_SHIFT_KEY,// (RShift) # 36
 '*',// (Keypad-*) or (*/PrtScn) on a 83/84-key keyboard # 37
 LEFT_ALT_KEY,// (LAlt) # 38
 ' ',// (Space bar) # 39
 CAPS_LOCK_KEY,// (CapsLock) # 3a
 F1_KEY,// (F1) # 3b
 F2_KEY,// (F2) # 3c
 F3_KEY,// (F3) # 3d
 F4_KEY,// (F4) # 3e
 F5_KEY,// (F5) # 3f
 F6_KEY,// (F6) # 40
 F7_KEY,// (F7) # 41
 F8_KEY,// (F8) # 42
 F9_KEY,// (F9) # 43
 F10_KEY,// (F10) # 44
 NUM_LOCK_KEY,// (NumLock) # 45
 SCROLL_LOCK_KEY,// (ScrollLock) # 46
 KEYPAD_KEY,// (Keypad-7/Home) # 47 
 KEYPAD_KEY,// (Keypad-8/Up) # 48
 KEYPAD_KEY,// (Keypad-9/PgUp) # 49
 KEYPAD_KEY,// (Keypad--) # 4a
 KEYPAD_KEY,// (Keypad-4/Left) # 4b 
 KEYPAD_KEY,// (Keypad-5) # 4c
 KEYPAD_KEY,// (Keypad-6/Right) # 4d 
 KEYPAD_KEY,// (Keypad-+) # 4e
 KEYPAD_KEY,// (Keypad-1/End) # 4f 
 KEYPAD_KEY,// (Keypad-2/Down) # 50
 KEYPAD_KEY,// (Keypad-3/PgDn) # 51
 '0',// (Keypad-0/Ins) # 52
 '.',// (Keypad-./Del) # 53
 0,// (Alt-SysRq) on a 84+ key keyboard # 54
 '\\',// less common # 55
 '>', //unlabelled key to the left or to the right of the left Alt key #56
 F11_KEY, // F11 # 57
 F12_KEY // F12 # 
 // anything with higher number is not standard and not recognized
};

const keymap_t Keypad_Numeric[] =
{
  { 0x37, '*'},// (Keypad-*) or (*/PrtScn) on a 83/84-key keyboard # 37
  { 0x47, '7'},// (Keypad-7/Home) # 47 
  { 0x48, '8'},// (Keypad-8/Up) # 48
  { 0x49, '9'},// (Keypad-9/PgUp) # 49
  { 0x4a, '-'},// (Keypad--) # 4a
  { 0x4b, '4'},// (Keypad-4/Left) # 4b 
  { 0x4c, '5'},// (Keypad-5) # 4c
  { 0x4d, '6'},// (Keypad-6/Right) # 4d 
  { 0x4e, '+'},// (Keypad-+) # 4e
  { 0x4f, '1'},// (Keypad-1/End) # 4f 
  { 0x50, '2'},// (Keypad-2/Down) # 50
  { 0x51, '3'},// (Keypad-3/PgDn) # 51
  { 0x52, '0'},// (Keypad-0/Ins) # 52
  { 0x53, '.'} // (Keypad-./Del) # 53
};

const keymap_t Keypad_Regular[] =
{
  { 0x37, '*'},// (Keypad-*) or (*/PrtScn) on a 83/84-key keyboard # 37
  { 0x47, HOME_KEY },// (Keypad-7/Home) # 47 
  { 0x48, UP_KEY },// (Keypad-8/Up) # 48
  { 0x49, PAGE_UP_KEY },// (Keypad-9/PgUp) # 49
  { 0x4a, '-'},// (Keypad--) # 4a
  { 0x4b, LEFT_KEY},// (Keypad-4/Left) # 4b 
  { 0x4c, '5'},// (Keypad-5) # 4c
  { 0x4d, RIGHT_KEY},// (Keypad-6/Right) # 4d 
  { 0x4e, '+'},// (Keypad-+) # 4e
  { 0x4f, END_KEY},// (Keypad-1/End) # 4f 
  { 0x50, DOWN_KEY},// (Keypad-2/Down) # 50
  { 0x51, PAGE_DOWN_KEY},// (Keypad-3/PgDn) # 51
  { 0x52, INSERT_KEY},// (Keypad-0/Ins) # 52
  { 0x53, DELETE_KEY} // (Keypad-./Del) # 53
};

// codes after 0xe0
const keymap_t Escaped_Regular[] =
{
  { 0x1c, 13 },  // (keypad Enter)
  { 0x1d, RIGHT_CONTROL_KEY}, // (RCtrl)
  { 0x2a, FAKE_LSHIFT_KEY}, // (fake lshift)
  { 0x35, '/' }, // (keypad-/)
  { 0x36, FAKE_RSHIFT_KEY}, // (fake rshift)
  { 0x37, CONTROL_PRINTSCREEN_KEY}, // (Ctrl-PrtScn)
  { 0x38, RIGHT_ALT_KEY}, // (RAlt)
  { 0x46, CONTROL_BREAK_KEY}, // (Ctrl-Break)
  { 0x47, HOME_KEY }, // (Home)
  { 0x48, UP_KEY }, // (Up)
  { 0x49, PAGE_UP_KEY }, // (PgUp)
  { 0x4b, LEFT_KEY }, // (Left)
  { 0x4d, RIGHT_KEY }, // (Right)
  { 0x4f, END_KEY }, // (End)
  { 0x50, DOWN_KEY }, // (Down)
  { 0x51, PAGE_DOWN_KEY }, // (PgDn)
  { 0x52, INSERT_KEY }, // (Insert)
  { 0x53, DELETE_KEY }  // (Delete)

};

// pseudo-keycodes 0x80..0xE0 range are mapped to string from this table
// the string is sent out to serial port prefixed with "<Esc>"
const char *Ansi_Key_Sequences[] =
{
  "1", // F1 #82 VT100 only has 4 function keys, the remaining behave as VT220
  "2", // F2 #83
  "3", // F3 #84
  "4", // F4 #85
  "5",  // F5 #86
  "6", // F6 #87
  "7", // F7 #88
  "8", // F8 #89
  "9", // F9 #8a
  "0", // F10 #8b
  "!", // F11 #8c
  "@", // F12 #8d
  "[1~", // HOME_KEY
  "OA", // UP_KEY
  "[5~", // PAGE_UP_KEY
  "OD", // LEFT_KEY
  "OC", // RIGHT_KEY
  "[4~", // END_KEY
  "OB", // DOWN_KEY
  "[6~", // PAGE_DOWN_KEY
  "[2~", // INSERT_KEY
  "[3~", // DELETE_KEY
};

