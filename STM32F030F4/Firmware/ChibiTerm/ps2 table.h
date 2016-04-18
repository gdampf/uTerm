/*
 * ps2 table.h
 *
 * Created: March-24-16, 6:31:56 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee 
 
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

extern const uint8_t Kbd_Code[], ANSI_FN_Code[];

#define MAX_KEYTBL		0x83

#define KEY_MODIFERS	0x80
#define KEY_FN_KEYS		0x90
#define KEY_CURSORS		0xa0
#define KEY_OTHERS		0xb0

#define KEY_TYPE(X)		((X)&0xf0)
#define KEY_FN(X)			((X)+KEY_FN_KEYS)

#define MODIFIER(X)		(1<<((X)&0x07))

// Use same mapping as LED

enum ModifierKeys
{
	KEY_SCROLL 	= KEY_MODIFERS,
	KEY_NUMLOCK,
	KEY_CAP,
  KEY_SHIFT,
  KEY_CTRL,
  KEY_ALT
};

enum CursorKeys
{
  KEY_HOME = KEY_CURSORS,
	KEY_END,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_PGDN,
	KEY_PGUP,
	KEY_INS,
	KEY_NUM_5,
	KEY_CURSOR_LAST
};


enum OtherKeys
{ 
	KEY_BACKSPACE = 0x08,
  KEY_TAB	=	0x09,	
	KEY_ENTER = 0x0d,
	KEY_ESC = 0x1b,
	KEY_DEL = 0x7f,
	//-----------------------
	KEY_GUI_LEFT = KEY_OTHERS,
	KEY_GUI_RIGHT,
	KEY_GUI_APPS,
	KEY_ACPI_POWER,
	KEY_ACPI_WAKE,
	KEY_ACPI_SLEEP,
};

#endif
