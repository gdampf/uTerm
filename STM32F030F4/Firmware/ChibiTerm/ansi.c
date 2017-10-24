/*
 * ansi.c
 *
 * Created: March-27-16, 2:51:50 PM
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

#include <string.h>
#include <ctype.h>
#include "vga-min.h"
#include "ansi.h"
#include "serial.h"
#include "ps2.h"
#include "vgafont.h"

#define noCS_DEBUG // if defined, disables decoding of escape sequences and prints them instead

volatile Cursor_t Cursor;
volatile ANSI_Pref_t ANSI_Prefs;
volatile uint8_t wrap_next;

static Cursor_t Saved_Cursor;
static CSI_t CSI;
static ANSI_Pref_t Saved_Prefs;

#define BLINKFRAMES 30  // cursor blinking half-period in number of vertical syncs

// ----- cursor control ------------------------------------------------

// Vertical blanking call back
void VerticalBlank_CB(void)
{ 
	Cursor.Counter++;
	// update cursor in task to simplify sharing.
	if(Cursor.Counter>=BLINKFRAMES) {
    Cursor.Update=1;
		Cursor.Counter=0;
	}
}

void Cursor_Task(void)
{
	Cursor.Update = 0;
	if(Cursor.State) {
		TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;			
	}
	else {
		if(Cursor.Type)
      TEXT_BUF(Cursor.X,Cursor.Y) = (Cursor.Type==Cursor_Underline)
	                                ?Char_Cursor_Uline:Cursor.Char^0x80;
	}
  Cursor.State=!Cursor.State;
}

void Cursor_Disable(void)
{
  Cursor.Type=Cursor_Off;
  TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;
}

void Cursor_Enable(void)
{
  Cursor.Type=Cursor_Block;
}


void Cursor_SavePosition(void)
{
	Saved_Cursor=Cursor;
	Saved_Prefs=ANSI_Prefs;
}

void Cursor_RestorePosition(void)
{
	Cursor.Type=Saved_Cursor.Type;
	ANSI_Prefs=Saved_Prefs;
  PhysicalCursor_MoveTo(Saved_Cursor.X,Saved_Cursor.Y);
}

// gets the character under cursor and restarts timer, cursor will be put back
// after the blink period
void Cursor_Reset(void)
{
  Cursor.Counter=BLINKFRAMES-5;	
	Cursor.Update = 0;
	Cursor.Char=TEXT_BUF(Cursor.X,Cursor.Y);
}

// ----- clearing ------------------------------------------------

uint8_t BlankChar(void)
{
  return ANSI_Prefs.Inverse?FONT_CHAR(' ')+0x80:FONT_CHAR(' ');
}

void VGA_ClearScreen(void)
{
	memset(TextBuffer,BlankChar(),VGA_TEXT_X*VGA_TEXT_Y);
  Cursor_Reset();
}

void VGA_ClearScreenToEnd(void)
{
  memset(&TEXT_BUF(Cursor.X,Cursor.Y),BlankChar(),VGA_TEXT_X*(VGA_TEXT_Y-1-Cursor.Y)+(80-Cursor.X));
	Cursor_Reset();
}

void VGA_ClearScreenToStart(void)
{
  memset(&TEXT_BUF(0,0),BlankChar(),VGA_TEXT_X*Cursor.Y+Cursor.X+1);
	Cursor_Reset();
}

void VGA_ClearLine(void)
{
  memset(&TEXT_BUF(0,Cursor.Y),BlankChar(),VGA_TEXT_X);
	Cursor_Reset();
}

void VGA_ClearLineToEnd(void)
{
  memset(&TEXT_BUF(Cursor.X,Cursor.Y),BlankChar(),VGA_TEXT_X-Cursor.X);
	Cursor_Reset();
}

void VGA_ClearLineToStart(void)
{
  memset(&TEXT_BUF(0,Cursor.Y),BlankChar(),Cursor.X+1);
	Cursor_Reset();
}

// ----- scrolling ------------------------------------------------

void ScrollRegionUp(uint8_t top,uint8_t bottom)
{
  TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;

	if (bottom>top)
	  memmove(&TEXT_BUF(0,top),&TEXT_BUF(0,top+1),VGA_TEXT_X*(bottom-top));
  memset(&TEXT_BUF(0,bottom),BlankChar(),VGA_TEXT_X);
	Cursor_Reset();
}

void ScrollRegionDown(uint8_t top,uint8_t bottom)
{
  TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;
	if (bottom>top)
	  memmove(&TEXT_BUF(0,top+1),&TEXT_BUF(0,top),VGA_TEXT_X*(bottom-top));
  memset(&TEXT_BUF(0,top),BlankChar(),VGA_TEXT_X);
	Cursor_Reset();
}

void ScrollUp(uint8_t Lines)
{
	if (!Lines)
		Lines=1;
	while (Lines--)
	{
		ScrollRegionUp(ANSI_Prefs.ScrollingTop,ANSI_Prefs.ScrollingBottom);
	  memset(&TEXT_BUF(0,ANSI_Prefs.ScrollingBottom),BlankChar(),VGA_TEXT_X);
	}
}

void ScrollDown(uint8_t Lines)
{
	if (!Lines)
		Lines=1;
	while (Lines--)
	{
		ScrollRegionDown(ANSI_Prefs.ScrollingTop,ANSI_Prefs.ScrollingBottom);
	}
}

// ----- cursor positioning

// This function has a side effect of storing Cursor.Char into screen buffer at current
// cursor location even if the cursor does not move, so for writing character at current cursor
// location can be done by setting Cursor.Char and then calling this function
//
void PhysicalCursor_MoveTo(uint8_t New_X, uint8_t New_Y)
{
	TEXT_BUF(Cursor.X,Cursor.Y) = Cursor.Char;		// restore character under cursor
	if (New_X>(VGA_TEXT_X-1))
	  return;
	if (New_Y>(VGA_TEXT_Y-1))
	  return;
	Cursor.X=New_X;
	Cursor.Y=New_Y;
	Cursor_Reset();
	wrap_next=0;
}

// ANSI cursor positions start from 1, but escape sequence may leave the number out for default
// positioning cursor outside screen boundaries does not move the cursor
//
void ANSICursor_MoveTo(uint8_t New_X,uint8_t New_Y)
{
  if (!New_X)
    New_X=1;
	if (!New_Y)
	  New_Y=1;
	New_X--;
	New_Y--;
	// if origin is set to scrolling region then add to row
	if (ANSI_Prefs.ScrollingOrigin)
	  New_Y+=ANSI_Prefs.ScrollingTop;
  if (New_Y>ANSI_Prefs.ScrollingBottom)
    return;
	PhysicalCursor_MoveTo(New_X,New_Y);
}

// get zero-based cursor row number within active scrolling region
uint8_t OriginRow(void)
{
  if (ANSI_Prefs.ScrollingOrigin)
    return Cursor.Y-ANSI_Prefs.ScrollingTop;
	return Cursor.Y;
}

// move up, but limited to scroll area
uint8_t Cursor_Up(uint8_t Count)
{
uint8_t New_Y;
  if (!Count)
    Count=1;
	if (Count>OriginRow())
	  return 0;
	New_Y=Cursor.Y-Count;
	PhysicalCursor_MoveTo(Cursor.X,New_Y);
	return 1;
}

// move down, but limited to scroll area
uint8_t Cursor_Down(uint8_t Count)
{
uint8_t New_Y;
  if (!Count)
    Count=1;
	if (Count>(ANSI_Prefs.ScrollingBottom-ANSI_Prefs.ScrollingTop))
	  return 0;
	New_Y=Cursor.Y+Count;
	if (New_Y>ANSI_Prefs.ScrollingBottom)
	  return 0;
	PhysicalCursor_MoveTo(Cursor.X,New_Y);
	return 1;
}

void Cursor_Left(int8_t Count)
{
  if (!Count)
    Count=1;
	if (Count>Cursor.X)
	  return;
	PhysicalCursor_MoveTo(Cursor.X-Count,Cursor.Y);
}

void Cursor_Right(int8_t Count)
{
  if (!Count)
    Count=1;
	if ((Cursor.X+Count)>(VGA_TEXT_X-1))
	  return;
	PhysicalCursor_MoveTo(Cursor.X+Count,Cursor.Y);
}

void Cursor_NextLine(int8_t Count)
{
  if (Cursor_Down(Count))
    PhysicalCursor_MoveTo(0,Cursor.Y);
}

void Cursor_PreviousLine(int8_t Count)
{
  if (Cursor_Up(Count))
    PhysicalCursor_MoveTo(0,Cursor.Y);
}

void Cursor_HorizontalAbsolute(int8_t Pos)
{
  if (!Pos)
    Pos=1;
	PhysicalCursor_MoveTo(Pos-1,Cursor.Y);
}

// ------ actual output ----------------------------------------------

void VGA_Putch(uint8_t Ch)
{
  if (ANSI_Prefs.Graphics)
  {
    if (Ch>0x5f && Ch<0x80)
      Ch-=0x60;
  }
  if (ANSI_Prefs.Inverse)
    Ch|=0x80;

	if (wrap_next) {
	  // if wrapping is not allowed just stay at current location
		// keep the wrap flag to make sure we get here on next char
	  if (!ANSI_Prefs.LineWrap) 
	  {
			Cursor.Char = Ch;
	    PhysicalCursor_MoveTo(Cursor.X,Cursor.Y);
			wrap_next=1;
	    return;
	  }
	  // if not at bottom, move cursor to beginning of next line
		// the move has to happen first so that the rightmost character
		// is set correctly, and then new character is stored to cursor
	  if (Cursor.Y<(ANSI_Prefs.ScrollingBottom)) 
	  {
	    PhysicalCursor_MoveTo(0,Cursor.Y+1);
			Cursor.Char = Ch;
	    return;
	  }
	  // at bottom of screen, if scrolling enabled then scroll 
	  if (ANSI_Prefs.Scroll)
	  {
	    ScrollUp(1);
		  PhysicalCursor_MoveTo(0,Cursor.Y);
			Cursor.Char = Ch;
		  return;
	  }
	}
	// set character at current cursor location now
	Cursor.Char = Ch;
	// if room to move, then move right
	if (Cursor.X<VGA_TEXT_X-1) 
	{
	  PhysicalCursor_MoveTo(Cursor.X+1,Cursor.Y);
	}
	else
	{
  	PhysicalCursor_MoveTo(Cursor.X,Cursor.Y);
		wrap_next=1;
	}
}

void VGA_PutStr(char *string)
{
  while (string && *string)
    VGA_Putch(*string++);
}

void VGA_Puthex(uint8_t n)
{
 uint8_t c;
  c=(n>>4)+'0';
	if (c>'9')
		c+=7;
	VGA_Putch(c);
	c=(n&0x0f)+'0';
	if (c>'9')
		c+=7;
	VGA_Putch(c);
}

void VGA_Putint(uint8_t n)
{	
  if(n>9)
    VGA_Putint(n/10);
	VGA_Putch((n%10)+'0');
}
// ----------------------------------------------------

void ANSI_Init(void)
{	
	VGA.VerticalBlank = VerticalBlank_CB;
#ifdef CS_DEBUG
	ANSI_Prefs.LineWrap = 1;
#else
	ANSI_Prefs.LineWrap = 0;
#endif
	ANSI_Prefs.Scroll = 1; 
	ANSI_Prefs.Inverse = 0;
	ANSI_Prefs.ScrollingOrigin=0;
	ANSI_Prefs.ScrollingTop=0;
	ANSI_Prefs.ScrollingBottom=VGA_TEXT_Y-1;
	Cursor.Type = Cursor_Block;
	Cursor.X=0;
	Cursor.Y=0;
	Saved_Cursor=Cursor;
	Saved_Prefs=ANSI_Prefs;
	CSI.State = ANSI_ASCII;
	wrap_next=0;
	VGA_ClearScreen();
}

void ControlCode(uint8_t Ch)
{
	switch(Ch)
	{
	  case Char_NUL: // completely ignore
	    return;
	  case Char_ENQ:
	    Putchar(Char_ACK);
	    break;
		case Char_BEL: // TODO: add speaker?
		  break;
		case Char_BS:
		  if (Cursor.X>0)
			{
  		  Cursor_Left(1);
      }
			else
			{
			  if (ANSI_Prefs.LineWrap) 
			  {
			    if (OriginRow()>0)
			      PhysicalCursor_MoveTo(VGA_TEXT_X-1,Cursor.Y-1);
			  }
			}
			break;
		case Char_HT:
		  {
				uint8_t i;
				i=8-(Cursor.X%8);
				while (i--)
					  VGA_Putch(' ');
			}
		  break;
		case Char_LF:
		case Char_VT:
		case Char_FF:
  		if (!Cursor_Down(1))
			  if (ANSI_Prefs.Scroll)
			    ScrollUp(1);
			if (ANSI_Prefs.AutoCR)
			  Cursor_HorizontalAbsolute(1);
			break;
		case Char_CR:
		  Cursor_HorizontalAbsolute(1);
#ifdef CS_DEBUG
			if (!Cursor_Down(1))
			  ScrollUp(1);
#endif
			break;
		case Char_SO: // invoke G1 character set, this is graphic symbols at lowercase letters
		  ANSI_Prefs.Graphics=1;
		  break;
		case Char_SI: // invoke G0 character set, this is normal ascii
		  ANSI_Prefs.Graphics=0;
		  break;
		case Char_XON: // flow control
		case Char_XOFF:
		  break;
		case Char_CAN: // on vt100 these just breaks current esc sequence
		case Char_SUB:
		  break;
		case Char_ESC:
			CSI.State = ANSI_ESC;
			return;
		default:
			VGA_Putch('^');
  		VGA_Putch(Ch+'@');
	    break;
	}
  CSI.State = ANSI_ASCII; 
}

void Clear_CSI(void)
{
	memset(&CSI.Parm,0,sizeof(CSI.Parm));
	CSI.Parm_Idx = CSI.End = 0;
}

// Non-ANSI escape sequence received. The received character cannot
// be a control character because that would have cancelled the escape
// sequence instead.
void ESC_Sequence(uint8_t Ch)
{
	switch (Ch)
	{
#ifndef CS_DEBUG
		case 'c': // initialize
      ANSI_Init();
			break;
		case '<': // in VT52 mode this is 'enter ANSI mode'
      break;
		case '>': // in VT52 mode this is 'exit alternate keypad'
			break;
		case '=': // in VT52 mode this is 'enter alternate keypad'
			break;
		case 'D':
		  ScrollUp(1);
			break;
		case 'M':
			ScrollDown(1);
			break;
		case 'E':
			Cursor_HorizontalAbsolute(1);
			if (!Cursor_Down(1))
				ScrollUp(1);
			break;
		case '7':
			Cursor_SavePosition();
			break;
		case '8':
			Cursor_RestorePosition();
			break;
		case '5': // <ESC>5n status report
			CSI.State=ANSI_DISCARD;
		  return;
		case '6': // <ESC>6n report cursor position
			CSI.State=ANSI_DISCARD;
			return;
		case ')': // select character set for G0
		case '(': // select character set for G1
			CSI.State=ANSI_DISCARD;
			return;
		case 'N': // select G2 for one character
		case 'O': // select G3 for one character
			break;
#endif
		default:
      VGA_PutStr("<ESC><");
      VGA_Puthex(Ch);
      VGA_Putch('>');
	}
	CSI.State=ANSI_ASCII;
}

// decode received escape sequence
void CSI_Sequence(void)
{
uint8_t i;
	switch (CSI.End)
	{
#ifndef CS_DEBUG
	  case 'A': // cursor up
	    Cursor_Up(CSI.Parm[0]);
	    break;
	  case 'B': // cursor down
	    Cursor_Down(CSI.Parm[0]);
	    break;
	  case 'C': // cursor right
	    Cursor_Right(CSI.Parm[0]);
	    break;
	  case 'D': // cursor left
	    Cursor_Left(CSI.Parm[0]);
	    break;
		case 'E': // cursor next line
	    Cursor_NextLine(CSI.Parm[0]);
		  break;
		case 'F': // cursor previous line
	    Cursor_PreviousLine(CSI.Parm[0]);
		  break;
		case 'G': // cursor horizontal absolute
		  Cursor_HorizontalAbsolute(CSI.Parm[0]);
		  break;
	  case 'H': // set cursor position
	  case 'f':
	    ANSICursor_MoveTo(CSI.Parm[1],CSI.Parm[0]);
	    break;
		case 'J': // erase in display
		  switch (CSI.Parm[0]) 
		  {
		    case 0:
		      VGA_ClearScreenToEnd();
		      break;
		    case 1:
		      VGA_ClearScreenToStart();
		      break;
		    case 2:
		      VGA_ClearScreen();
		      break;
			}
		  break;
		case 'K': // erase in line
		  switch (CSI.Parm[0])
		  {
		    case 0:
		      VGA_ClearLineToEnd();
		      break;
		    case 1:
		      VGA_ClearLineToStart();
		      break;
		    case 2:
		      VGA_ClearLine();
		      break;
		  }
		  break;
		case 'L': // insert lines at cursor row, scrolling existing lines down. cursor to first column
			ScrollRegionDown(Cursor.Y,ANSI_Prefs.ScrollingBottom);
			Cursor_HorizontalAbsolute(1);
			break;
		case 'M': // delete lines at cursor row, scrolling below lines up. cursor to first column.
			ScrollRegionUp(Cursor.Y,ANSI_Prefs.ScrollingBottom);
			Cursor_HorizontalAbsolute(1);
			break;
		case 'S': // scroll up
		  ScrollUp(CSI.Parm[0]);
		  break;
		case 'T': // scroll down
		  ScrollDown(CSI.Parm[0]);
		  break;
		case 'm': // select graphic rendition
		  for (i=0;i<=CSI.Parm_Idx;i++)
		  {
		    switch (CSI.Parm[i]) 
		    {
		      case 0: // reset
		        ANSI_Prefs.Inverse=0;
		        break;
					case 7: // inverse
					  ANSI_Prefs.Inverse=1;
					  break;
					case 27: // inverse off
		        ANSI_Prefs.Inverse=0;
					  break;
		    }
		  }
		  break;
		case 'n': // device status report
		  switch (CSI.Parm[0])
		  {
		    case 6: // cursor position
					Putchar(27);
					Putchar('[');
					Putint(OriginRow()+1);
					Putchar(';');
					Putint(Cursor.X+1);
					Putchar('R');		
				  break;
				case 5: // status
				  Putchar(27);
				  PutStr("[0n");
				  break;
			  case 66: // this is for aiding automated testing, reads character at cursor location, as stored in screen buffer
					Putchar(27);
					Putchar('[');
					Putint(Cursor.Char);
					Putchar('R');
					break;
			}
		  break;
		case 's': // save cursor position (and attributes)
		  Cursor_SavePosition();
		  break;
		case 'u': // restore cursor position
	    PhysicalCursor_MoveTo(Saved_Cursor.X,Saved_Cursor.Y);
		  break;
		case 'l': // DEC specials
			for (i=0;i<=CSI.Parm_Idx;i++)
			{
				switch (CSI.Parm[i])
				{
					case 4: // reset insert mode
						break;
					case 6:
						if (CSI.DEC)
						{
							ANSI_Prefs.ScrollingOrigin=0;
							ANSICursor_MoveTo(1,1);
						}
						break;
					case 7:
						ANSI_Prefs.LineWrap=0;
						break;
					case 20:
						ANSI_Prefs.AutoCR=0;
						break;
					case 25:
						if (CSI.DEC)
							Cursor_Disable();
						break;
				}
			}
		  break;
		case 'h': // DEC special
			for (i=0;i<=CSI.Parm_Idx;i++)
			{
				switch (CSI.Parm[i])
				{
					case 4: // set insert mode
						break;
					case 6:
						if (CSI.DEC)
						{
						  ANSI_Prefs.ScrollingOrigin=1;
						  ANSICursor_MoveTo(1,1);
						}
						break;
					case 7:
					  ANSI_Prefs.LineWrap=1;
						break;
					case 20:
						ANSI_Prefs.AutoCR=1;
						break;
					case 25:
						if (CSI.DEC)
						  Cursor_Enable();
						break;
				}
			}
		  break;
		case 'c': // identify terminal
		  Putchar(27);
		  PutStr("[?1;0c"); // 80x24 vanilla VT100 with inverse attribute
		  break;
		case 'r': // scrolling region
		  ANSI_Prefs.ScrollingTop=CSI.Parm[0];
		  if (ANSI_Prefs.ScrollingTop<1 || ANSI_Prefs.ScrollingTop>VGA_TEXT_Y)
		    ANSI_Prefs.ScrollingTop=1;
		  ANSI_Prefs.ScrollingBottom=CSI.Parm[1];
		  if (ANSI_Prefs.ScrollingBottom<1 || ANSI_Prefs.ScrollingBottom>VGA_TEXT_Y)
		    ANSI_Prefs.ScrollingBottom=VGA_TEXT_Y;
			// make zero-based and make sure top is above bottom
			ANSI_Prefs.ScrollingTop--;
			ANSI_Prefs.ScrollingBottom--;
			if (ANSI_Prefs.ScrollingBottom<ANSI_Prefs.ScrollingTop) 
			{
			  i=ANSI_Prefs.ScrollingTop;
			  ANSI_Prefs.ScrollingTop=ANSI_Prefs.ScrollingBottom;
			  ANSI_Prefs.ScrollingBottom=i;
			}
			PhysicalCursor_MoveTo(0,ANSI_Prefs.ScrollingTop);
		  break;
#endif
    default:
			VGA_PutStr("<ESC>[");
			if (CSI.DEC)
				VGA_Putch('?');
		  for (i=0;i<=CSI.Parm_Idx;i++)
		  {
			  VGA_Putint(CSI.Parm[i]);
				if (i<CSI.Parm_Idx)
					VGA_Putch(';');
			}
			VGA_Putch(CSI.End);
			break;
	}
}


void ANSI_FSM(uint8_t Ch)
{
	if (!Ch)
		 return; // ignore padding
	if (Ch<' ')
	{
		if (Ch!=27)
			ControlCode(Ch);
		else
			CSI.State=ANSI_ESC;
	}
	else
	{
		switch(CSI.State)
		{
			case ANSI_DISCARD:
				CSI.State=ANSI_ASCII;
				break;
			case ANSI_ASCII:
				VGA_Putch(Ch);
				break;
			case ANSI_ESC: // Have received ESC
				if(Ch == '[')
				{ 
					Clear_CSI(); // received valid CSI start
					CSI.DEC = 0; 				
					CSI.State = ANSI_CSI0;
				}
				else // non-ANSI escape sequence
				{
					ESC_Sequence(Ch);
				}
		    break;
			// DEC extensions use '?' after CSI start, check for it	
			case ANSI_CSI0:
			  CSI.State= ANSI_CSI;
			  if (Ch=='?')
			  {
			    CSI.DEC=1; // if DEC special, set flag and done 
			    break;
			  }
			  // otherwise fall through to normal processing  
			case ANSI_CSI:
				if(isdigit(Ch))
				{ 
					if(CSI.Parm_Idx < CSI_PARM_MAX)
					  CSI.Parm[CSI.Parm_Idx] = CSI.Parm[CSI.Parm_Idx]*10 + (Ch-'0');
				}
				else if(Ch == ';')
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

