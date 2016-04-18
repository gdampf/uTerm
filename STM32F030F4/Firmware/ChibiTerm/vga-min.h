/*
 * vga-min.h
 *
 * Created: March-13-16, 8:10:22 PM
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

#ifndef _VGA_H_
#define _VGA_H_

#include <stdio.h>
#include <stdint.h>

#include "stm32f0xx.h"
#include "core_cm0.h"
#include "hardware.h"

enum DPMS
{ 
	DPMSModeOn,          // In use
  DPMSModeStandby,     // Hsync Off - Blanked, low power
  DPMSModeSuspend,     // Vsync off - Blanked, lower power
  DPMSModeOff          // Hsync, Vsync off - Shut off, awaiting activity
};

typedef struct
{
	void 			(*VerticalBlank)(void);
	uint8_t		*TextBuffer_Ptr;
	uint16_t	Line;											// Current VGA line
	uint8_t		Font_CurRow;							// Current font row
	uint8_t		Buffer:1;									// Ping pong buffer
	uint8_t		Render:1;									// rendering flag
	uint8_t		Display:1;								// display flag
	enum DPMS	DPMS_Mode:2;							// Power management mode
	} VGA_t;

extern VGA_t VGA;;
extern uint8_t  TextBuffer[];
extern volatile uint8_t MicroTimer0, MicroTimer1;

void   VGA_Init(void);
void   Delay(uint16_t Ticks);
	
#define ScanLine_Buf0			&ScanLineBuf[0]
#define ScanLine_Buf1			&ScanLineBuf[SPI_BUF_SIZE+1]

#define TICK							((VGA_PIX_X*1000000UL)/VGA_DOTCLK)  /* us*/
#define us_to_Tick(X)			((X)/TICK+1)
#define TIM3_IRQ_PRIORITY	0
#define PENDSV_PRIORITY		(TIM3_IRQ_PRIORITY+1)

// PB1 to show active video
#define VGA_BACKGROUND

// Using external 25MHz OSC.  #undef to use HSI
#define HSE

// #undef for crystal
//#define EXT_OSCILLATOR

// Use external oscillator

#ifdef EXT_OSCILLATOR
#define HSE_BYPASS	RCC_CR_HSEBYP
#else
#define HSE_BYPASS	0
#endif

// SPI using 16-bit transfer won't work becuse of byte ordering
//#define SPI_16BIT

// mess around with SPI
#ifndef SPI_CR1_EXTRA
#define SPI_CR1_EXTRA	0
#endif

//Default TI mode
#ifndef SPI_CR2_EXTRA
#define SPI_CR2_EXTRA	SPI_CR2_FRF
#endif

// VGA Mode (lines)
//#define VGA_400
//#define VGA_350
#define	VGA_480

/*
http://martin.hinner.info/vga/timing.html

"640 x 350 (EGA on VGA)"    "640 x 400 VGA text"        "VGA industry standard"
Clock frequency 25.175 MHz  Clock frequency 25.175 MHz  Clock frequency 25.175 MHz
Line  frequency 31469 Hz    Line  frequency 31469 Hz    Line  frequency 31469 Hz
Field frequency 70.086 Hz   Field frequency 70.086 Hz   Field frequency 59.94 Hz
One line:                   One line:                   One line:
  8 pixels front porch        8 pixels front porch        8 pixels front porch
 96 pixels horizontal sync   96 pixels horizontal sync   96 pixels horizontal sync
 40 pixels back porch        40 pixels back porch        40 pixels back porch
  8 pixels left border        8 pixels left border        8 pixels left border
640 pixels video            640 pixels video            640 pixels video
  8 pixels right border       8 pixels right border       8 pixels right border
---                         ---                         ---
800 pixels total per line   800 pixels total per line   800 pixels total per line                             
One field:                  One field:                  One field:
 31 lines front porch         5 lines front porch         2 lines front porch
  2 lines vertical sync       2 lines vertical sync       2 lines vertical sync
 54 lines back porch         28 lines back porch         25 lines back porch
  6 lines top border          7 lines top border          8 lines top border
350 lines video             400 lines video             480 lines video
  6 lines bottom border       7 lines bottom border       8 lines bottom border
---                         ---                         ---
449 lines total per field   449 lines total per field   525 lines total
per field                                                           
Sync polarity: H positive,  Sync polarity: H negative,  Sync polarity: H negative,
               V negative                  V positive                  V negative
Scan type: non interlaced.  Scan type: non interlaced.  Scan type: non interlaced. 

*/

#ifdef HSE
#define VGA_DOTCLK				25000000UL	//Hz
#define PLL_MULT					2
#define CFGR_PLL_MULT			RCC_CFGR_PLLMUL2
#else
#define VGA_DOTCLK				25175000UL	//Hz
#define HSI_CLK						8000000UL
#define PLL_MULT					13
#define CFGR_PLL_MULT			RCC_CFGR_PLLMUL13

// default trim = 0x10, steps are supposed to be 40kHz
#define HSI_TRIM					6

//HSI_TRIM should be ((2*VGA_DOTCLK)/PLL_MULT-HSI_CLK/2)/40000+16
#endif

#define CPU_CLOCK					(VGA_DOTCLK*2UL)

// Using separate VSYNC signal
// My Philips monitor would set to 640x350 instead of 640x400 when using CSync
#define VSYNC
#define VSYNC_PORT				GPIOA
#define VSYNC_PIN					PA5

// (pixels)
#define VGA_RES_X					640
#define VGA_BITS					1

#define VGA_PIX_X					800
#define VGA_BORDER_LEFT		8
#define VGA_BORDER_RIGHT	8
#define VGA_HSYNC_FP			8
#define VGA_HSYNC_BP			40
#define VGA_HSYNC					96

#ifdef VGA_400
#define VGA_RES_Y					400
#define VGA_VSYNC_FP			5
#define VGA_VSYNC_BP			28
#define VGA_VSYNC					2
#define VGA_BORDER_TOP		7
#define VGA_BORDER_BOT		7
#define VGA_LINES					449
#define VGA_SYNC_POS
#else 

#ifdef VGA_350
#define VGA_RES_Y					350
#define VGA_VSYNC_FP			31
#define VGA_VSYNC_BP			54
#define VGA_VSYNC					2
#define VGA_BORDER_TOP		6
#define VGA_BORDER_BOT		6
#define VGA_LINES					449
#define VGA_VSYNC_NEG
#else

#ifdef VGA_480
#define VGA_RES_Y					480
#define VGA_VSYNC_FP			2
#define VGA_VSYNC_BP			25
#define VGA_VSYNC					2
#define VGA_BORDER_TOP		8
#define VGA_BORDER_BOT		8
#define VGA_LINES					525
#define VGA_VSYNC_NEG

#endif
#endif
#endif

// (lines)
#define VGA_ACTIVE_VIDEO	(VGA_HSYNC+VGA_HSYNC_BP)

#define VGA_VSYNC_START		(VGA_VSYNC_FP)
#define VGA_VSYNC_STOP		(VGA_VSYNC_FP+VGA_VSYNC)
#define VGA_DISPLAY_START (VGA_VSYNC_STOP+VGA_VSYNC_BP+VGA_BORDER_TOP)
#define VGA_DISPLAY_STOP	(VGA_DISPLAY_START+VGA_RES_Y)

//  (clocks)
#define TIM3_PRESCALER		0
#define TIM3_CLK					(2-TIM3_PRESCALER)

#define VGA_DOTS_CNT			(TIM3_CLK*VGA_PIX_X)
#define VGA_HSYNC_CNT			(TIM3_CLK*VGA_HSYNC)
#define VGA_DISPLAY_ON		(TIM3_CLK*(VGA_HSYNC+VGA_HSYNC_BP+VGA_BORDER_LEFT))
#define VGA_DISPLAY_OFF		(TIM3_CLK*(VGA_HSYNC+VGA_HSYNC_BP+VGA_BORDER_LEFT+VGA_RES_X))
#define VGA_DMA_START			(TIM3_CLK*(VGA_ACTIVE_VIDEO+VGA_BORDER_LEFT)-VGA_IRQ_Latency)

// IRQ latency clock alignment tweak (clock cycles)
// Check with a logic analyzer or turn on background if IRQ code is altered or use different compiler.
#define VGA_IRQ_Latency 	78

#define VGA_TEXT_X				(VGA_RES_X/FONT_COL)
#define VGA_TEXT_Y				(VGA_RES_Y/FONT_Y)

#ifdef VGA_SYNC_POS
#define VSYNC_ASSERT()		VSYNC_PORT->BSRR = PIN_SET(VSYNC_PIN)
#define VSYNC_DEASSERT()	VSYNC_PORT->BSRR = PIN_CLR(VSYNC_PIN)
#else
#define VSYNC_ASSERT()		VSYNC_PORT->BSRR = PIN_CLR(VSYNC_PIN)
#define VSYNC_DEASSERT()	VSYNC_PORT->BSRR = PIN_SET(VSYNC_PIN)
#endif

#ifdef	SPI_16BIT
#define SPI_WORDSIZE			16
#define SPI_CR2_DATASIZE	(SPI_CR2_DS_3|SPI_CR2_DS_2|SPI_CR2_DS_1|SPI_CR2_DS_0)
#define SPI_DMA_CCR_SIZE	(DMA_CCR_MSIZE_0|DMA_CCR_PSIZE_0)
#define SPI_BUF_SIZE			(SPI_DMA_WORDS*2)
#else
#define SPI_WORDSIZE			8
#define SPI_CR2_DATASIZE	(SPI_CR2_DS_2|SPI_CR2_DS_1|SPI_CR2_DS_0)
#define SPI_DMA_CCR_SIZE	(0)
#define SPI_BUF_SIZE			SPI_DMA_WORDS
#endif

#define SPI_DMA_WORDS			((VGA_RES_X*VGA_BITS)/SPI_WORDSIZE+2)
#define SPI_DMA_COUNT			SPI_DMA_WORDS

#define TEXT_BUF(X,Y)			TextBuffer[(X)+(Y)*VGA_TEXT_X]

#endif
