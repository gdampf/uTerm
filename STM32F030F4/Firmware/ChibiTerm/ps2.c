/*
 * ps2.c
 *
 * Created: March-11-16, 5:50:49 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee 
 *
 * Keystroke decoding and VT output sequences by Madis Kaal
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

#include <ctype.h>
#include <string.h>
#include "ps2.h"
#include "ps2 table.h"
#include "serial.h"
#include "ansi.h"

FIFO_DECL(PS2_Buf,PS2_FIFO_Size);

#ifndef COUNTOF
#define COUNTOF(arr) (sizeof(arr)/sizeof(arr[0]))
#endif
#define toupper(c) (c-((c>='a' && c<='z')?('a'-'A'):0))
#define isletter(c) ((c>='A' && c<='Z')||(c>='a' && c<='z'))
#define isctrl(c) ((c>='@' && c<='_')||(c>='a' && c<='z'))

static uint16_t Modifiers;
static volatile PS2_IF_t PS2_IF;
static PS2_State_t PS2_Fsm;
static uint8_t PS2_Cmd,PS2_Cmd_Arg;

#include "ps2 table.c"

void PS2_Init(void)
{
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;		// EXTI1 = PA1 - PS/2 Clk
	EXTI->FTSR = EXTI_FTSR_TR1;											// Fall edge trigger PA1
	EXTI->IMR |= EXTI_IMR_MR1;											// Unmask PA1
	
	PS2_IF.Init = 0;
	PS2_Fsm.State = PS2_UNKNOWN;
	Modifiers=0;
	FIFO_Clear((FIFO*)PS2_Buf);
	
	// NVIC IRQ
  NVIC_SetPriority(EXTI0_1_IRQn,PS2_IRQ_PRIORITY);
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
	PS2_Cmd_Arg = LED&7;
	PS2_Send(PS2_Cmd);
}

// ------------------------------------------------------------------

void NumLockOn(void)
{
  Modifiers&=~NUMLOCK_MODIFIER;
	PS2_Update_LED(Modifiers);
}

void NumLockOff(void)
{
  Modifiers|=NUMLOCK_MODIFIER;
	PS2_Update_LED(Modifiers);
}

static uint8_t Lookup_Key(const keymap_t *table,uint8_t count,uint8_t k)
{
uint8_t i;
  for (i=0;i<count;i++)
  {
    if (k==table->key)
      return table->character;
		table++;
	}
	return 0;
}

static uint8_t Remap_Key(const uint8_t *table,uint8_t count,uint8_t k)
{
	if (k<count)
		return table[k];
	return k;
}

static void Send_Key(uint8_t c)
{
	if (!c)
    return;
	if (c<0x80)
	{
	  if (Modifiers&CONTROL_MODIFIER)
		{
			if isctrl(c)
				Putchar(toupper(c)-'@');
			return;
		}
		if (isletter(c))
		{
	    if (Modifiers&CAPSLOCK_MODIFIER)
			  c=toupper(c);
		}
		Putchar(c);
		return;
	}
	if (c<0xe0)
	{
		c-=0x80;
		if (c<(sizeof(Ansi_Key_Sequences)/sizeof(Ansi_Key_Sequences[0])))
		{
			Putchar(27);
			PutStr(Ansi_Key_Sequences[c]);
		}
		return;
	}
}

static void Key_Up(uint8_t key)
{
	uint8_t c;
	key=Remap_Key(Scancode_Translations,COUNTOF(Scancode_Translations),key);
	if (Modifiers&EXTEND_MODIFIER) 
	{
		c=Lookup_Key(Escaped_Regular,COUNTOF(Escaped_Regular),key);
	}
	else {
		if ((Modifiers&SHIFT_MODIFIER || Modifiers&FAKESHIFT_MODIFIER))
			c=Remap_Key(Shifted_Regular,COUNTOF(Shifted_Regular),key); 
		else
			c=Remap_Key(Unshifted_Regular,COUNTOF(Unshifted_Regular),key);
	}
  switch (c) 
  {
    case LEFT_CONTROL_KEY:
      Modifiers&=~CONTROL_MODIFIER;
      return;
    case LEFT_SHIFT_KEY:
    case RIGHT_SHIFT_KEY:
      Modifiers&=~SHIFT_MODIFIER;
      return;
    case LEFT_ALT_KEY:
      Modifiers&=~ALT_MODIFIER;
      return;
    case FAKE_LSHIFT_KEY:
    case FAKE_RSHIFT_KEY:
      Modifiers&=~FAKESHIFT_MODIFIER;
      return;
	}
}

static void Key_Down(uint8_t key)
{
uint8_t c;
	key=Remap_Key(Scancode_Translations,COUNTOF(Scancode_Translations),key);
	if ((Modifiers&SHIFT_MODIFIER || Modifiers&FAKESHIFT_MODIFIER))
		c=Remap_Key(Shifted_Regular,COUNTOF(Shifted_Regular),key); 
	else
		c=Remap_Key(Unshifted_Regular,COUNTOF(Unshifted_Regular),key);
	if (!c)
	  return;
  switch (c) 
  {
    case LEFT_CONTROL_KEY:
      Modifiers|=CONTROL_MODIFIER;
      return;
    case LEFT_SHIFT_KEY:
    case RIGHT_SHIFT_KEY:
      Modifiers|=SHIFT_MODIFIER;
      return;
    case LEFT_ALT_KEY:
      Modifiers|=ALT_MODIFIER;
      return;
    case CAPS_LOCK_KEY:
      Modifiers^=CAPSLOCK_MODIFIER;
			PS2_Update_LED(Modifiers);
		  return;
    case NUM_LOCK_KEY:
      Modifiers^=NUMLOCK_MODIFIER;
			PS2_Update_LED(Modifiers);
      return;
    case SCROLL_LOCK_KEY:
      Modifiers^=SCROLL_LOCK_MODIFIER;
			PS2_Update_LED(Modifiers);
      return;    
    case FAKE_LSHIFT_KEY:
    case FAKE_RSHIFT_KEY:
      Modifiers|=FAKESHIFT_MODIFIER;
      return;
    case CONTROL_PRINTSCREEN_KEY:
    case RIGHT_ALT_KEY:
    case CONTROL_BREAK_KEY:
      break;
    default:
			if (c==KEYPAD_KEY)
			{
		    if (Modifiers&NUMLOCK_MODIFIER)
		      c=Lookup_Key(Keypad_Numeric,COUNTOF(Keypad_Numeric),key);
			  else
			  	c=Lookup_Key(Keypad_Regular,COUNTOF(Keypad_Regular),key);
			}
			Send_Key(c);
			break;
  }
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
				case PS2_KBD_CODE_EXTENDED: // e0
					Modifiers|=EXTEND_MODIFIER;
				  break;
				
				case PS2_KBD_CODE_RELEASE:  // f0
					Modifiers|=RELEASE_MODIFIER;
				  break;
				
				default:
					if (ps2_data>0)
			    {
						//PS2_Decode(ps2_data);
						if (Modifiers&RELEASE_MODIFIER)
						  Key_Up(ps2_data);
						else
						  Key_Down(ps2_data);
						Modifiers&=~(RELEASE_MODIFIER|EXTEND_MODIFIER);
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

