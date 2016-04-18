/*
 * ps2 table.c
 *
 * Created: March-24-16, 4:54:14 PM
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

#include "ps2 table.h"

const uint8_t Kbd_Code[]=
{ 
	// Unshifted	Shift
	0, 0,																// 00
	KEY_FN(9),KEY_FN(9),								// 01  F9
	0, 0,																// 02
	KEY_FN(5),KEY_FN(5), 								// 03  F5
	KEY_FN(3),KEY_FN(3), 								// 04  F3
	KEY_FN(1),KEY_FN(1), 								// 05  F1
	KEY_FN(2),KEY_FN(2), 								// 06  F2
	KEY_FN(12),KEY_FN(12),							// 07  F12
	0, 0,																// 08
	KEY_FN(10),KEY_FN(10), 							// 09  F10
	KEY_FN(8),KEY_FN(8), 								// 0A  F8
	KEY_FN(6),KEY_FN(6),								// 0B  F6
	KEY_FN(4),KEY_FN(4), 								// 0C  F4
	KEY_TAB,KEY_TAB, 										// 0D  TAB
	'`','~', 														// 0E  ` or ~
	0, 0,																// 0F
	0, 0,																// 10
	KEY_ALT,KEY_ALT, 										// 11  Left ALT
	KEY_SHIFT,KEY_SHIFT, 								// 12  Left SHIFT
	0, 0,																// 13
	KEY_CTRL,KEY_CTRL,	 								// 14  Left Ctrl
	'q','Q', 														// 15  Q
	'1','!',														// 16  1 or !
	0, 0,																// 17
	0, 0,																// 18
	0, 0,																// 19
	'z','Z',														// 1A  Z
	's','S',														// 1B  S
	'a','A',														// 1C  A
	'w','W',														// 1D  W
	'2','@',														// 1E  2 or @
	KEY_GUI_LEFT,KEY_GUI_LEFT,					// 1F
	0, 0,																// 20
	'c','C',														// 21  C
	'x','X',														// 22  X
	'd','D',														// 23  D
	'e','E',														// 24  E
	'4','$',														// 25  4 or $
	'3','#',														// 26  3 or #
	KEY_GUI_RIGHT,KEY_GUI_RIGHT,				// 27
	0, 0,																// 28
	' ',' ',														// 29  Space
	'v','V',														// 2A  V
	'f','F',														// 2B  F
	't','T',														// 2C  T
	'r','R',														// 2D  R
	'5','%',														// 2E  5 or %
	KEY_GUI_APPS,KEY_GUI_APPS,					// 2F
	0, 0,																// 30
	'n','N',														// 31  N
	'b','B',														// 32  B
	'h','H',														// 33  H
	'g','G',									 					// 34  G
	'y','Y',														// 35  Y
	'6','^',														// 36  6 or ^
	KEY_ACPI_POWER,KEY_ACPI_POWER,			// 37
	0, 0,																// 38
	0, 0,																// 39
	'm','M',														// 3A  M
	'j','J',														// 3B  J
	'u','U',														// 3C  U
	'7','&',														// 3D  7 or &
	'8','*',														// 3E  8 or *
	KEY_ACPI_SLEEP,KEY_ACPI_SLEEP,			// 3F
	0, 0,																// 40
	',','<',														// 41  , or <
	'k','K',														// 42  K
	'i','I',														// 43  I
	'o','O',														// 44  O
	'0',')',														// 45  0 or )
	'9','(',														// 46  9 or (
	0, 0,																// 47
	0, 0,																// 48
	'.','>',														// 49  . or >
	'/','?',														// 4A  / or ?
	'l','L',														// 4B  L
	';',':',														// 4C  // or :
	'p','P',														// 4D  P
	'-','_',														// 4E  - or _
	0, 0,																// 4F
	0, 0,																// 50
	0, 0,																// 51
	'\'','"',														// 52  ' or "
  0, 0,																// 53
	'[','{',														// 54  [ or {
	'=','+',														// 55  = OR +
	0, 0,																// 56
	0, 0,																// 57
	KEY_CAP,KEY_CAP,		 								// 58  Caps Lock
	KEY_SHIFT,KEY_SHIFT,								// 59  Right Shift
	KEY_ENTER,KEY_ENTER,								// 5A  Enter
	']','}',														// 5B  ] or }
	0, 0,																// 5C	
	'\\','|',														// 5D  \ or |
	KEY_ACPI_WAKE,KEY_ACPI_WAKE,				// 5E
	0, 0,																// 5F
	0, 0,																// 60
	0, 0,																// 61
	0, 0,																// 62
	0, 0,																// 63
	0, 0,																// 64
	0, 0,																// 65
	KEY_BACKSPACE,KEY_BACKSPACE, 				// 66  Backspace
	0, 0,																// 67
	0, 0,																// 68
	KEY_END,'1',												// 69  NUM - 1 or END
	0, 0,																// 6A
	KEY_LEFT,'4',												// 6B  NUM - 4 or LEFT
	KEY_HOME,'7',												// 6C  NUM - 7 or HOME
	0, 0,																// 6D
	0, 0,																// 6E
	0, 0,																// 6F
	KEY_INS,'0',     										// 70  NUM - 0 or INS
	KEY_DEL,'.',     										// 71  NUM - . or DEL
	KEY_DOWN,'2',     									// 72  NUM - 2 or DOWN
	KEY_NUM_5,'5',     									// 73  NUM - 5
	KEY_RIGHT,'6',     									// 74  NUM - 6 or RIGHT
	KEY_UP,'8',     										// 75  NUM - 8 or UP
	KEY_ESC,KEY_ESC,										// 76  ESC
	KEY_NUMLOCK,KEY_NUMLOCK,						// 77  NUM LOCK
	KEY_FN(11), KEY_FN(11),			  			// 78  F11
	'+', '+',						    						// 79  NUM - + (Plus)
	KEY_PGDN,'3',     									// 7A  NUM 3 or PAGE DOWN
	'-','-',     												// 7B  NUM - - (Minus)
	'*','*',						     						// 7C  NUM - *
	KEY_PGUP,'9',     									// 7D  NUM - 9 or PAGE UP
	KEY_SCROLL,KEY_SCROLL,							// 7E  SCROLL LOCK
	0, 0,  															// 7F	
	0, 0,  															// 80
	0, 0,  															// 81
	0, 0,  															// 82
	KEY_FN(7),   												// 83  F7
};

const uint8_t ANSI_FN_Code[] =
{
	// unshifted, shift, Ctrl,	Alt,	
	 59, 84, 94,104,		//F1
   60, 85, 95,105,		//F2
   61, 86, 96,106,		//F3
   62, 87, 97,107,		//F4
   63, 88, 98,108,		//F5
   64, 89, 99,109,		//F6
   65, 90,100,110,		//F7
   66, 91,101,111,		//F8
   67, 92,102,112,		//F9
   68, 93,103,113,		//F10
  133,135,137,139,		//F11
  134,136,138,140			//F12
};
