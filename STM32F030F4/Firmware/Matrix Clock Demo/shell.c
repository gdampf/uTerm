/*
 * Shell.c
 *
 * Created: 08/09/2012 10:09:46 PM
 *  Author: K. C. Lee
 
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

#include "serial.h"
#include "shell.h"
#include "lib.h"

static char LineBuffer[LINEBUFSIZE];
char *LinePtr;
static uint8_t Line_Pos;

void Shell_Init(void)
{ 
  Puts(PROMPT);  
  LineBuffer[0]=0;
  Line_Pos=0;
  LinePtr=NULL;
}

void Shell_Term_Task(void)
{ char ch;
  
  LinePtr=NULL; 
  ch=Getc(&FIFO_Rx);

  if ((ch>=' ') && (Line_Pos < LINEBUFSIZE-1))
  { Putchar(ch);
    LineBuffer[Line_Pos++]=ch;
   }
  else if (ch==Char_BS)
  { if (Line_Pos)
    { 
      LineBuffer[Line_Pos--]=0;
      Puts("\x08 \x08");
     }
   }
  else if(ch==Char_CR)
  { LineBuffer[Line_Pos]=0;
    LinePtr=LineBuffer;
    NewLine();
   }
 }

void Shell_Exec(void)
{ 
  if(*LinePtr && !ExecCmd())
  { Puts("???\n");
    Help();
   }
  Shell_Init();       
 }

void SkipSpace(void)		/* Skip to first non-space character in line buffer */
{
  for(;*LinePtr&&IsWhiteSpc(*LinePtr);LinePtr++)
  /* */;
 }

// Match against strings in program space
char *Buf_FMatch(const char *string)
{ char *Buf=LinePtr; 

  while(*Buf && !IsWhiteSpc(*Buf))
    if(ToUpper(*Buf++)!=*string++)
      return(0);

  return(*string?NULL:Buf);
 }

uint8_t ExecCmd(void)
{ const CMD_TBL *tbl_ptr;
  char *Parm;

  for(tbl_ptr=Command_Table;tbl_ptr->Token;tbl_ptr++)
  { 
    Parm=Buf_FMatch(tbl_ptr->Token);
    
    if(Parm)
    { 
      LinePtr=Parm;
      SkipSpace();
      tbl_ptr->func();
      NewLine();
      return(1);
     }
   }
  return(0);
 }
 
// Get hex argument from line buffer
uint32_t GetHexParm(void)
{ uint32_t n=0;

  while(*LinePtr && !IsWhiteSpc(*LinePtr))
    n=(n<<4)|Hex(*LinePtr++);

  SkipSpace();
  return(n);
 }

 uint8_t DEC(char ch)
 {
	 if((ch>='0')&&(ch<='9'))
	   return (ch-'0');
	 else
		 return 0;
 }
 
// Get hex argument from line buffer
uint32_t GetIntParm(void)
{ uint32_t n=0;

  while(*LinePtr && !IsWhiteSpc(*LinePtr))
    n= n*10+DEC(*LinePtr++);

  SkipSpace();
  return(n);
 }
 
 
void Help(void)
{ uint8_t Col;
  const CMD_TBL *tbl_ptr;

  Puts("Available commands:\n");
  
  for(tbl_ptr=Command_Table;tbl_ptr->Token;tbl_ptr++)
  { Col=Puts((char *)tbl_ptr->Token);
    FillSpc(Desc_Col-Col);
    Puts((char *)tbl_ptr->Description);
    NewLine();
   }
 }
