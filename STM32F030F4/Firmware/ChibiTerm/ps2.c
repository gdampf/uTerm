/*
 * ps2.c
 *
 * Created: March-11-16, 5:50:49 PM
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

#include <ctype.h>
#include <string.h>
#include "ps2.h"
#include "ps2 table.h"
#include "serial.h"

FIFO_DECL(PS2_Buf,PS2_FIFO_Size);

static volatile PS2_IF_t PS2_IF;
static PS2_Modifier_t PS2_Modifier;
static PS2_State_t PS2_Fsm;

static uint8_t PS2_Cmd,PS2_Cmd_Arg;

void PS2_Init(void)
{
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;		// EXTI1 = PA1 - PS/2 Clk
	EXTI->FTSR = EXTI_FTSR_TR1;											// Fall edge trigger PA1
	EXTI->IMR |= EXTI_IMR_MR1;											// Unmask PA1
	
	PS2_IF.Init = 0;
	PS2_Fsm.State = PS2_UNKNOWN;
	PS2_Modifier.Init = 0;
	FIFO_Clear((FIFO*)PS2_Buf);
	
	// NVIC IRQ
  NVIC_SetPriority(EXTI0_1_IRQn,PS2_IRQ_PRIORITY);// Lowest priority																	// Highest priority
  NVIC_EnableIRQ(EXTI0_1_IRQn);
}

// PS/2 IRQ handler at PA1
void EXTI0_1_IRQHandler(void)
{
	EXTI->PR = EXTI_PR_PR1;													// Clear interrupt

  if(PS2_IF.States.WriteMode)											// Send command
  { 
		if(++PS2_IF.States.BitCnt==PS2_TX_BITS)
		{ 
			PS2_PORT->BSRR = PIN_SET(PS2_DAT); 					// ACK bit = 1
			PS2_IF.Init =0;
		}
		else
		{
			PS2_PORT->BSRR = (PS2_IF.States.Code & 0x01)?PIN_SET(PS2_DAT):PIN_CLR(PS2_DAT);			
			PS2_IF.States.Code >>= 1;			
		}
  }
  else																						// receive key code
	{ 	
		if(!MicroTimer1)
			PS2_IF.Init = 0;
		
		MicroTimer1 = us_to_Tick(PS2_BIT_TIMEOUT);
		
		if(PS2_PORT->IDR & PS2_DAT_BIT)
			PS2_IF.States.Code |= (1<<PS2_IF.States.BitCnt);

		if(++PS2_IF.States.BitCnt==PS2_RX_BITS)
		{ 
			// Check for valid Start, Stop bits and parity bits
			if (!(PS2_IF.States.Code & PS2_START_BIT) && 
					 (PS2_IF.States.Code & PS2_STOP_BIT) &&
					 ((PS2_IF.States.Code & PS2_PARITY_BIT)==PS2_Parity(PS2_IF.States.Code>>1)))

				FIFO_Write((FIFO*)PS2_Buf,(PS2_IF.States.Code >>1)&0xff);
			else
				FIFO_Write((FIFO*)PS2_Buf,PS2_KBD_ERR_CODE);
			
			PS2_IF.Init =0;
		}
	}
}

uint8_t PS2_Send(uint8_t Cmd)
{ 
  uint8_t Timeout;
  
  // wait for bus idle
  for(Timeout=PS2_TIMEOUT;Timeout;Timeout--)
  {
    if((!PS2_IF.States.BitCnt)&&(PS2_PORT->IDR &PS2_CLK_BIT))
    { 
			NVIC_DisableIRQ(EXTI0_1_IRQn);

			// Format the bitstream to be send to the keyboard
      PS2_IF.States.Code = (Cmd<<1)|PS2_Parity(Cmd)|PS2_STOP_BIT;
			PS2_IF.States.WriteMode = 1;
			
			NVIC_EnableIRQ(EXTI0_1_IRQn);
			
      // Wait at least 100us
			Delay(us_to_Tick(PS2_CMD_START_us));
			
      // Set Clk low
			PS2_PORT->BSRR = PIN_CLR(PS2_CLK);

      // Wait at least 100us
			Delay(us_to_Tick(PS2_CMD_START_us));

      // Set Clk high
			PS2_PORT->BSRR = PIN_SET(PS2_CLK);

      return(1);
    }
    Delay(us_to_Tick(PS2_BUSY_WAIT_us));
   }
  return (0);
}

// Calculate parity
uint16_t PS2_Parity(uint8_t byte)
{ uint8_t parity =0, i;
  
  for(i=8;i;i--)
  { parity += byte & 0x01;
    byte >>=1;
  }
  return((parity & 0x01)?0:PS2_PARITY_BIT);
}

void PS2_Update_LED(uint8_t LED)
{	
	PS2_Fsm.State = PS2_CMD;	
	PS2_Cmd = PS2_KBD_CMD_LED;
	PS2_Cmd_Arg = LED;			
	PS2_Send(PS2_Cmd);
}

void PS2_Task(void)
{
	uint8_t ps2_data;

	ps2_data = Getc((FIFO*)PS2_Buf);
	
	if (ps2_data ==PS2_KBD_ERR_CODE)
	{ 
		PS2_Fsm.State = PS2_UNKNOWN;
		PS2_Send(PS2_CMD_RESET);
	  return;
	}
	else if (ps2_data == PS2_RESPOND_INIT_OK)
	{
		PS2_Fsm.State = PS2_KBD_RDY;						// Power on reset
		return;
	}
	
	switch(PS2_Fsm.State)
	{
		case PS2_UNKNOWN:
		  if(ps2_data ==PS2_RESPOND_ACK)
			{
		    PS2_Send(PS2_CMD_RESET);
				break;
			}
			else			
				// uP came out of reset while keyboard already up
				PS2_Fsm.State = PS2_KBD_RDY;
				// fall through
	
		case PS2_KBD_RDY:		
		  switch(ps2_data)
			{
				case PS2_KBD_CODE_EXTENDED:
					PS2_Modifier.Attr.Extend = 1;
				  break;
				
				case PS2_KBD_CODE_RELEASE:
					PS2_Modifier.Attr.Release = 1;
				  break;
				
				default:
					if (ps2_data >0)
			    { 
						PS2_Decode(ps2_data);
					}
				}		
		  break;
			
		case PS2_CMD:					
			switch(ps2_data)
			{
				case PS2_RESPOND_ACK:
					PS2_Send(PS2_Cmd_Arg);
					PS2_Fsm.State = PS2_CMD_ACK;
					break;
				case PS2_RESPOND_RESEND:
					PS2_Send(PS2_Cmd);		
				  break;
				default:
					PS2_Fsm.State = PS2_UNKNOWN;
				}
			break;		
			
		case PS2_CMD_ACK:
			if (ps2_data == PS2_RESPOND_ACK)	
		    PS2_Fsm.State = PS2_KBD_RDY;
			else
				PS2_Fsm.State = PS2_UNKNOWN;
			break;
	}
}

void PS2_Decode(uint8_t key_code)
{
	uint8_t key;
	
	if (key_code <= MAX_KEYTBL)
	  key = Kbd_Code[key_code*2];	
	
  if(KEY_TYPE(key)==KEY_MODIFERS)
		Key_Modifers(key);		
	else if(!PS2_Modifier.Attr.Release)														// Only make events
	{
		switch(KEY_TYPE(key))
		{			
			case KEY_FN_KEYS:
				Key_FN(key);
				break;
			
			case KEY_CURSORS:
				Key_Cursor(key);
				break;
			
			case KEY_OTHERS:
				Key_Other(key);
				break;
			
			default:
			  if(PS2_Modifier.Attr.Ctrl)														// Control keys
			  {
					const char Ctrl_Str[] = "[\\]`/";
					char *pos= strchr(Ctrl_Str,key);
					
					if (key ==' ')																			// Ctrl-Space
						key = 0;
					else if(isalpha(key))																// A-Z
						key = key - 'a' + 1;			
			    else if (pos)
						key = (pos - Ctrl_Str)+KEY_ESC;
					else
						return;
				}
				// handles Alt here
				
				else if(isprint(key))
				{
					if(isalpha(key))																		// Logical XOR caps lock & Shift
          {
            if(!!(PS2_Modifier.Attr.LED & PS2_MOD_CAPS)!= !!PS2_Modifier.Attr.Shift)
						  key = Kbd_Code[key_code*2+1];
					}
					else if (PS2_Modifier.Attr.Shift)										// ignore caps lock
					  key = Kbd_Code[key_code*2+1];			
				}
					
				Putchar(key);						
		}
	}
	PS2_Modifier.Attr.Extend = PS2_Modifier.Attr.Release = 0;
}	
	
void Key_Modifers(uint8_t key)	
{	
	switch(key)
	{
		case KEY_SCROLL:
		case KEY_NUMLOCK:
		case KEY_CAP:
			if (PS2_Modifier.Attr.Release)
				PS2_Fsm.PrevKey = 0;
			else if (PS2_Fsm.PrevKey != PREV_MODKEY(key))
			{	
				PS2_Fsm.PrevKey = PREV_MODKEY(key);
				PS2_Modifier.Attr.LED ^= MODIFIER(key);
				PS2_Update_LED(PS2_Modifier.Attr.LED);
			}
			break;

		case KEY_SHIFT:
			PS2_Modifier.Attr.Shift = !PS2_Modifier.Attr.Release;
		  break;
		case KEY_CTRL:
			PS2_Modifier.Attr.Ctrl = !PS2_Modifier.Attr.Release;
			break;
		case KEY_ALT:
			PS2_Modifier.Attr.Alt = !PS2_Modifier.Attr.Release;
			break;
	}
}
	
void Key_FN(uint8_t key)
{
}

void Key_Cursor(uint8_t key)
{
}

void Key_Other(uint8_t key)
{
}
