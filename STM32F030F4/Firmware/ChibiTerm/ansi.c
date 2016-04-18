/*
 * ansi.c
 *
 * Created: March-27-16, 2:51:50 PM
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

#include <string.h>
#include <ctype.h>
#include "vga-min.h"
#include "font.h"
#include "ansi.h"
#include "serial.h"

volatile Cursor_t Cursor;
static CSI_t CSI;
static ANSI_Pref_t ANSI_Prefs;

static uint8_t Saved_Cursor_X, Saved_Cursor_Y;

// Vertical blanking call back
void VerticalBlank_CB(void)
{ 
	// update the lower counter field to save RAM	
	Cursor.Counter++;
	
	// update cursor in task to simplify sharing.
	if(!(Cursor.Counter & CURSOR_UPDATE_MASK))
    Cursor.Update=1;
}

void Clear_CSI(void)
{
	memset(&CSI.Parm,0,sizeof(CSI.Parm));
	CSI.Parm_Idx = CSI.End = 0;
}

void ANSI_Init(void)
{	
	VGA.VerticalBlank = VerticalBlank_CB;
	ANSI_Prefs.LineWrap = ANSI_Prefs.Scroll = 
	ANSI_Prefs.AutoCR = ANSI_Prefs.AutoLF = 1;
	Cursor.Type = Cursor_Underline;
	CSI.State = ANSI_ASCII;
}

void Cursor_Task(void)
{
	Cursor.Update = 0;
	
	if(Cursor.Counter & CURSOR_CHAR)
		TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;			
	else if(Cursor.Type)
    TEXT_BUF(Cursor.X,Cursor.Y) = (Cursor.Type==Cursor_Underline)
	                                ?Char_Cursor_Uline:Char_Cursor_Block;
}

void Cursor_MoveTo(int8_t New_X, int8_t New_Y)
{
	TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;		// restore character under cursor
	
	if(New_X > VGA_TEXT_X-1)
	{	
		if(ANSI_Prefs.LineWrap)	
	  {
	    New_X -= VGA_TEXT_X;
			New_Y++;
		}
		else
			return;
	}
	if(New_Y > VGA_TEXT_Y-1)
  {
	  if(ANSI_Prefs.Scroll)
	  { 
			New_Y = VGA_TEXT_Y-1;
		  ScrollUp();			
		}
		else
		  return;						
	}
	if(New_X<0)
	{ 
		New_X += VGA_TEXT_X;
		New_Y--;
	}
	if(New_Y<0)
		New_Y = 0;
	
  Cursor.Char = TEXT_BUF(New_X,New_Y);
  Cursor.X = New_X;
	Cursor.Y = New_Y;
}

void VGA_Putch(uint8_t Ch)
{
	Cursor.Char = (Ch>=FONT_START)&&(Ch<=FONT_END)?FONT_CHAR(Ch):FONT_CHAR(' ');
	Cursor_MoveTo(Cursor.X+1,Cursor.Y);
}

void VGA_Cls(void)
{
	memset(TextBuffer,FONT_CHAR(' '),VGA_TEXT_X*VGA_TEXT_Y);
}

void ScrollUp(void)
{
	memmove(&TEXT_BUF(0,0),&TEXT_BUF(0,1),VGA_TEXT_X*(VGA_TEXT_Y-1));
	memset(&TEXT_BUF(0,VGA_TEXT_Y-1),FONT_CHAR(' '),VGA_TEXT_X);
}

void ScrollDown(void)
{
	memmove(&TEXT_BUF(0,1),&TEXT_BUF(0,0),VGA_TEXT_X*(VGA_TEXT_Y-1));
	memset(&TEXT_BUF(0,0),FONT_CHAR(' '),VGA_TEXT_X);
}

void ControlCode(uint8_t Ch)
{ 
	switch(Ch)
	{
		case Char_BS:
			Cursor_MoveTo(Cursor.X-1,Cursor.Y);	// X--					
			break;
		
		case Char_CR:
			if(ANSI_Prefs.AutoLF)
				Cursor_MoveTo(0,Cursor.Y+1);					
			else
				Cursor_MoveTo(0,Cursor.Y);	
			break;
		
		case Char_LF:
			if(ANSI_Prefs.AutoCR)
				Cursor_MoveTo(0,Cursor.Y+1);					
			else
				Cursor_MoveTo(Cursor.X,Cursor.Y);	
			break;

		case Char_HOME:
			Cursor_MoveTo(0,0);
			break;

		case Char_CLS:
			VGA_Cls();													// CLS
			Cursor.Char = 0;
			Cursor_MoveTo(0,0);			
			break;
		
		case Char_ESC:
			CSI.State = ANSI_ESC;
			break;
	 }
 }

void ANSI_FSM(uint8_t Ch)
{
	if(Ch==Char_ESC)
		CSI.State = ANSI_ESC;
	else if (Ch< FONT_START)
		ControlCode(Ch);
	else
	{
		switch(CSI.State)
		{
			case ANSI_ASCII:
				VGA_Putch(Ch);			 
				break;
				
			case ANSI_ESC:												// Escape sequence
				if(Ch == Char_CSI_Start)
				{ 
					Clear_CSI();				
					CSI.State = ANSI_CSI;;
				}
				else
				{
					ESC_Sequence();
					CSI.State = ANSI_ASCII;
				}
		    break;
				
			case ANSI_CSI:
				if(isdigit(Ch))
				{ 
					if(CSI.Parm_Idx < CSI_PARM_MAX)
					  CSI.Parm[CSI.Parm_Idx] = CSI.Parm[CSI.Parm_Idx]*10 + (Ch-'0');
				}
				else if(Ch == Char_CSI_Delimiter)
				{ 
					if(CSI.Parm_Idx < CSI_PARM_MAX)
					  CSI.Parm_Idx++;
				}
				else
				{
					CSI.End = Ch;
					CSI_Sequence();
					CSI.State = ANSI_ASCII;
				}
				break;
		}
	}
 }

void ESC_Sequence(void)
{
}
  
void CSI_Sequence(void)
{
	PutCSI(CSI.End);
}
void PutStr(char *string)
{
	while(*string)
	  Putchar(*string++);
}
 
void Putint(uint8_t n)
{	
  if(n>100)
    Putchar(n/100+'0');
  else
	{
		Putchar(n/10+'0');
		Putchar((n%10)+'0');
	}		
}

void PutCSI(uint8_t Cmd)
{
	uint8_t i;
	
  PutStr("^[");
	
	for(i=0;i<= CSI.Parm_Idx;i++)
	{
		if(CSI.Parm[i])
		  Putint(CSI.Parm[i]);
		
		if(i<CSI.Parm_Idx)
			Putchar(';');
	}
	Putchar(Cmd);
}
