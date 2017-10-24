/*
 * ansi.h
 *
 * Created: March-27-16, 2:52:12 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee 
 *
 * VT100/ANSI terminal emulation by Madis Kaal <mast@nomad.ee>
 * Copyright (c) 2017 by Madis Kaal
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

#ifndef _ANSI_H_
#define _ANSI_H_

#include <stdio.h>
#include <stdint.h>

void ANSI_Init(void);
void Cursor_Task(void);
void ANSI_FSM(uint8_t Ch);
void PhysicalCursor_MoveTo(uint8_t New_X, uint8_t New_Y);

#define FONT_CHAR(X)	((X)-FONT_START)

#define Char_NUL  0
#define Char_ENQ  5
#define Char_ACK  6
#define Char_BEL  7
#define Char_BS   8
#define Char_HT   9
#define Char_LF   10
#define Char_VT   11
#define Char_FF   12
#define Char_CR   13
#define Char_SO   14
#define Char_SI   15
#define Char_XON  17
#define Char_XOFF 19
#define Char_CAN  24
#define Char_SUB  26
#define Char_ESC  27
#define Char_DEL  127

#define Char_Cursor_Uline		FONT_CHAR('_')

typedef enum 
{
	Cursor_Off, 
	Cursor_Underline, 
	Cursor_Block 
} CursorType;

typedef struct
{
	uint8_t			Char;
	uint8_t			X;
	uint8_t			Y;
  uint8_t 		Counter:5;
	uint8_t 		Update:1;
	uint8_t     State:1;
	CursorType	Type:2;
} Cursor_t;

typedef struct
{
  uint8_t LineWrap:1;
  uint8_t Scroll:1;
  uint8_t AutoCR:1;
	uint8_t Inverse:1;
	uint8_t Graphics:1;
	uint8_t ScrollingOrigin:1;
	uint8_t ScrollingTop;
	uint8_t ScrollingBottom;
} ANSI_Pref_t;

/* 
	DEC: There is no limit to the number of characters in the parameter 
	string, but a maximum of 16 parameters will be processed. All parameters 
	beyond the 16th will be silently ignored.
*/

#define CSI_PARM_MAX				16

typedef struct
{	
	uint8_t State:4;
	uint8_t Parm_Idx:5;
	uint8_t DEC:1;
	uint8_t End;
  uint8_t Parm[CSI_PARM_MAX];
} CSI_t;

extern volatile Cursor_t Cursor;
extern volatile ANSI_Pref_t ANSI_Prefs;

enum ANSI_States
{
	ANSI_ASCII, ANSI_ESC, ANSI_CSI0, ANSI_CSI, ANSI_DISCARD
};

#endif
