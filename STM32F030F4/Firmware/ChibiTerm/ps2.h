/*
 * ps2.h
 *
 * Created: March-11-16, 5:51:16 PM
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

#ifndef _PS2_H_
#define _PS2_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f0xx.h"
#include "system_stm32f0xx.h"
#include "gpio.h"
#include "fifo.h"
#include "vga-min.h"

#define PS2_RX_DEBUG

#define PS2_IRQ_PRIORITY  			3
#define PS2_FIFO_Size						4

#define PS2_PORT								GPIOA
#define PS2_CLK									PA1
#define PS2_DAT									PA0

#define PS2_CLK_BIT							(1<<PS2_CLK)
#define PS2_DAT_BIT							(1<<PS2_DAT)

void    	PS2_Init(void);
int16_t 	PS2_Get(void);
uint8_t 	PS2_Send(uint8_t Cmd);
void 			PS2_Task(void);
uint16_t 	PS2_Parity(uint8_t byte);
void    	PS2_Decode(uint8_t key_code);

void 			Key_Modifers(uint8_t key)	;
void 			Key_FN(uint8_t key);
void 			Key_Cursor(uint8_t key);
void 			Key_Other(uint8_t key);

extern  	FIFO_Data_t PS2_Buf[];

typedef union
{
	uint16_t		Init;
	struct
	{
		uint16_t	Code:11;
		uint8_t 	BitCnt:4;
		uint8_t		WriteMode:1;
	} States;
} PS2_IF_t;

typedef union
{	struct
	{
		uint8_t LED:3;
		uint8_t Shift:1;
		uint8_t Ctrl:1;
		uint8_t Alt:1;
		uint8_t Extend:1;
		uint8_t Release:1;
	} Attr;
	uint8_t Init;
} PS2_Modifier_t;

typedef struct 
{
  uint8_t State:2;
  uint8_t PrevKey:2;
	
} PS2_State_t;

#define PREV_MODKEY(X)					(X-KEY_MODIFERS+1)

//#define PS2_RX_DEBUG

#define PS2_WRITE_MASK          0x80
#define PS2_RX_BITS             11
#define PS2_TX_BITS             12

#define PS2_START_BIT           (1<<0)
#define PS2_PARITY_BIT         	(1<<9)
#define PS2_STOP_BIT           	(1<<10)
#define PS2_ACK_BIT            	(1<<11)

#define PS2_BIT_TIMEOUT					275			// Toshiba keyboard last 2 bits are slow
#define PS2_BUSY_WAIT_us        200
#define PS2_CMD_START_us        125
#define PS2_TIMEOUT             255

// Common PS2 command
#define PS2_GET_DEVICEID        0xf2
#define PS2_CMD_RESEND          0xfe
#define PS2_CMD_RESET           0xff

// Common PS/2 response
#define PS2_RESPOND_INIT_OK     0xaa
#define PS2_RESPOND_ACK         0xfa
#define PS2_RESPOND_RESEND      0xfe
#define PS2_RESPOND_FAIL        0xfc
#define PS2_RESPOND_FAIL2       0xfd
#define PS2_RESPOND_MS_ID       0x00

// pseudo keyboard code return for garbled data
#define PS2_KBD_ERR_CODE				0xff

// Keyboard Modifier/LED
#define PS2_KBD_CMD_LED         0xed
#define PS2_KBD_LED_MASK        0x07
#define PS2_KBD_LED_SCROLL      0x01
#define PS2_KBD_LED_NUM         0x02
#define PS2_KBD_LED_CAPS        0x04

#define PS2_MOD_SCROLL					PS2_KBD_LED_SCROLL
#define PS2_MOD_NUM							PS2_KBD_LED_NUM
#define PS2_MOD_CAPS						PS2_KBD_LED_CAPS

#define PS2_KBD_CODE_EXTENDED   0xe0
#define PS2_KBD_CODE_RELEASE    0xf0

/*
#define PS2_KBD_TYPEMATIC       0xf3
#define PS2_KBD_MF2_ID1         0xab
#define PS2_KBD_MF2_ID2         0x83
*/

enum PS2_States 
{ 
  PS2_UNKNOWN, PS2_KBD_RDY, PS2_CMD, PS2_CMD_ACK
};

#endif
