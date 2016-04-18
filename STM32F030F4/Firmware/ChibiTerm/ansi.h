/*
 * ansi.h
 *
 * Created: March-27-16, 2:52:12 PM
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

#ifndef _ANSI_H_
#define _ANSI_H_

#include <stdio.h>
#include <stdint.h>

void ANSI_Init(void);
void Cursor_Task(void);

void VGA_Cls(void);
void ScrollUp(void);
void ScrollDown(void);
void Cursor_MoveTo(int8_t New_X, int8_t New_Y);

void ASCII_Ch(uint8_t Ch);
void ANSI_FSM(uint8_t Ch);
void ESC_Sequence(void);
void CSI_Sequence(void);
void PutStr(char *string);
void Putint(uint8_t n);
void PutCSI(uint8_t Cmd);

#define FONT_CHAR(X)	((X)-FONT_START)

#define Char_HOME      			0x0b
#define Char_CLS        		0x0c
#define Char_BS        			0x08
#define Char_LF        			0x0a
#define Char_CR        			0x0d

#define Char_Cursor_Block		FONT_CHAR(0x7f)
#define Char_Cursor_Uline		FONT_CHAR('_')

typedef enum 
{ Cursor_Off, Cursor_Underline, Cursor_Block } 
CursorType;

typedef struct
{
	uint8_t			Char;
	uint8_t			X;
	uint8_t			Y;
  uint8_t 		Counter:5;
	uint8_t 		Update:1;
	CursorType	Type:2;
} Cursor_t;

// 1.875 blinks per second, 16 vertical blanks
#define CURSOR_UPDATE_MASK 	0x0f
#define CURSOR_CHAR					0x10

typedef struct
{
  uint8_t LineWrap:1;
  uint8_t Scroll:1;
  uint8_t AutoCR:1;
	uint8_t AutoLF:1;
} ANSI_Pref_t;

/* 
	DEC: There is no limit to the number of characters in the parameter 
	string, but a maximum of 16 parameters will be processed. All parameters 
	beyond the 16th will be silently ignored.
*/

#define CSI_PARM_MAX				16

typedef struct
{	
	uint8_t State:3;
	uint8_t Parm_Idx:5;
	uint8_t End;
  uint8_t Parm[CSI_PARM_MAX];
} CSI_t;

extern volatile Cursor_t Cursor;

#define Char_ESC						0x1b
#define Char_CSI_Start 			'['
#define Char_CSI_Delimiter	';'

enum ANSI_States
{
	ANSI_ASCII, ANSI_ESC, ANSI_CSI, 
};

#endif
