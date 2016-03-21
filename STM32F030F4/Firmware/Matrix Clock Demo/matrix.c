/*
 * matrix.c
 *
 * Created: March-16-16, 3:54:37 PM
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

#include "vga-min.h"
#include "vga font.h"
#include "stdlib.h"
#include "matrix.h"

#include "serial.h"
#include "shell.h"
#include "lib.h"

volatile uint8_t hour, minute, second, back_update, rain_update, sec_update=1;
uint8_t tick, time_count;

// keep track of time
void VerticalBlank_CB(void)
{
	if(tick)
	{	tick--;
		
		back_update = 1;
		
		if(!(tick%RAIN_RATE))
		  rain_update = 1;
	}
	else
	{
		tick = TICK_RELOAD;
    sec_update=1;
		
    if(second++>=60)
    { second = 0;

			if(minute++>=60)
			{ minute = 0;
				
				if(hour++ > HOUR_FORMAT)
					hour = 0;
			}
		}
	}
}

void PutAnyText(uint8_t ch , uint8_t *pos)
{
	if(pos < &TextBuffer[VGA_TEXT_X*VGA_TEXT_Y])
	*pos = ch;
}

void PutText(uint8_t ch , uint8_t *pos)
{
	if(ch<(FONT_END-FONT_START))
		PutAnyText(ch,pos);
}

void RandomText(uint32_t range, uint8_t *pos)
{	
	PutText((rand()>range)?rand():0,pos);
}

void RandomText1(uint8_t *pos)
{	
	PutText(rand()%(FONT_END-FONT_START-1)+1,pos);
}

void PutBlockChar(uint8_t Ch, uint8_t X, uint8_t Y)
{
  uint8_t i, j;
	
	for(i=2;i<12;i++)
	  for(j=0;j<FONT_COL;j++)
		{
			if(FONT_TABLE[Ch*FONT_ROW+i] & (1<<j))
			  RandomText1(&TEXT_BUF(X+j,Y+i));
			else
				PutText(0,&TEXT_BUF(X+j,Y+i));
			
		}
}

void PutNumber(uint8_t n, uint8_t X, uint8_t Y)
{
  PutBlockChar('0'-FONT_START+n/10,X+FONT_COL,Y);
  PutBlockChar('0'-FONT_START+n%10,X,Y);	
}

void Gen_Backdrop(void)
{	
	uint16_t i;

  for(i=0;i<VGA_TEXT_X*VGA_TEXT_Y;i++)
	{
	  RandomText(BACKGROUND,&TextBuffer[i]);
	}
}

int main(void)
{	
	uint16_t back_loc;
	uint8_t i, j;
	Raindrop raindrops[RAIN_DROPS];
	
	VerticalBlank = VerticalBlank_CB;;
	VGA_Init();
	USART_Init();
	Shell_Init();
	
  back_update = 1;
	srand(TIM3->CNT);
	Gen_Backdrop();
	
	while(1)
	{
		if(FIFO_ReadAvail(&FIFO_Rx))
		  Shell_Term_Task();
				
		if(LinePtr)                       // Task: Shell
		{ 
			NewLine();
			Shell_Exec();
		 }
		
		if(back_update)							// slow update
		{ back_update = 0;
			
			for(j=0;j<BACKGROUND_RATE;j++)
			{
        back_loc++;
				
				// update backdrop
				if(back_loc == VGA_TEXT_X*CLOCK_Y)
					back_loc=VGA_TEXT_X*(CLOCK_Y+13);
				
				// update backdrop
				if(back_loc >=VGA_TEXT_X*VGA_TEXT_Y)
					back_loc=0;
				
				RandomText(BACKGROUND,&TextBuffer[back_loc]);
		  }
		}
		
		if(rain_update)							// slow update
		{ 
			rain_update = 0;		
			for(i=0;i<RAIN_DROPS;i++)
			{
				if(!raindrops[i].length)
				{ 
					PutAnyText(0,&TEXT_BUF(raindrops[i].X_pos,raindrops[i].Y_pos));
					raindrops[i].length = rand()%RAIN_DROP_LENGTH + RAIN_DROP_LENGTH_MIN;
					raindrops[i].X_pos = (RAIN_DROP_X_INC *i + rand()%RAIN_DROP_X)%VGA_TEXT_X;
					raindrops[i].Y_pos = rand()%RAIN_DROP_Y;
				}
				else
				{
					PutAnyText(0,&TEXT_BUF(raindrops[i].X_pos,raindrops[i].Y_pos));					
					RandomText(BACKGROUND,&TEXT_BUF(raindrops[i].X_pos,raindrops[i].Y_pos));
					PutAnyText(BLOCK_CURSOR,&TEXT_BUF(raindrops[i].X_pos,++raindrops[i].Y_pos));
					raindrops[i].length--;
				}
			}
		}

		if(sec_update)		
		{ sec_update=0;
			
			PutNumber(hour,CLOCK_X+FONT_COL*6,CLOCK_Y);
			PutBlockChar(':'-FONT_START,CLOCK_X+FONT_COL*5,CLOCK_Y);
			PutNumber(minute,CLOCK_X+FONT_COL*3,CLOCK_Y);			
			PutBlockChar(':'-FONT_START,CLOCK_X+FONT_COL*2,CLOCK_Y);
			PutNumber(second,CLOCK_X,CLOCK_Y);
		}
			
	}
}

