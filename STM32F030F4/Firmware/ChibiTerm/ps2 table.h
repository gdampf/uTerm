/*
 * ps2 table.h
 *
 * Created: March-24-16, 6:31:56 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee 
 *
 * All tables replaced and decoding method changed by Madis Kaal
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

#ifndef _PS2_TABLE_H_
#define _PS2_TABLE_H_

#include <stdint.h>
#include "ps2.h"

typedef struct 
{
	uint8_t key;
	uint8_t character;
} keymap_t;

extern const uint8_t Scancode_Translations[];
extern const uint8_t Shifted_Regular[];
extern const uint8_t Unshifted_Regular[];
extern const keymap_t Keypad_Regular[];
extern const keymap_t Keypad_Numeric[];
extern const keymap_t Escaped_Regular[];
extern const char *Ansi_Key_Sequences[];

#define SCROLL_LOCK_MODIFIER 0x0001
#define NUMLOCK_MODIFIER     0x0002
#define CAPSLOCK_MODIFIER    0x0004
#define CONTROL_MODIFIER     0x0008
#define SHIFT_MODIFIER       0x0010
#define ALT_MODIFIER         0x0020
#define FAKESHIFT_MODIFIER   0x0040
#define EXTEND_MODIFIER      0x0080
#define RELEASE_MODIFIER     0x0100
#define ALTGR_MODIFIER       0x0200

enum 
{
  F1_KEY=0x80,F2_KEY,F3_KEY,F4_KEY,F5_KEY,F6_KEY,F7_KEY,F8_KEY,F9_KEY,F10_KEY,F11_KEY,F12_KEY,
  HOME_KEY,UP_KEY,PAGE_UP_KEY,LEFT_KEY,RIGHT_KEY,END_KEY,DOWN_KEY,PAGE_DOWN_KEY,INSERT_KEY,DELETE_KEY
};

enum
{ 
  LEFT_CONTROL_KEY=0xe0,LEFT_SHIFT_KEY,RIGHT_SHIFT_KEY,LEFT_ALT_KEY,CAPS_LOCK_KEY,
  NUM_LOCK_KEY,SCROLL_LOCK_KEY,FAKE_LSHIFT_KEY,FAKE_RSHIFT_KEY,KEYPAD_KEY,
  CONTROL_PRINTSCREEN_KEY,RIGHT_ALT_KEY,CONTROL_BREAK_KEY,RIGHT_CONTROL_KEY
};

#endif
