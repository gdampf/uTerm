/*
 * vga-min.c
 *
 * Created: March-16-2016, 3:50:27 PM
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

__align(4) uint8_t TextBuffer[VGA_TEXT_X*VGA_TEXT_Y];
__align(4) uint8_t ScanLineBuf[SPI_BUF_SIZE*2+1];

uint16_t VGA_Line;					// current VGA line
uint8_t  Display_Flags;

volatile uint16_t MicroTimer0;
void (* VerticalBlank)(void);

#define ScanLine_Buf0		&ScanLineBuf[0]
#define ScanLine_Buf1		&ScanLineBuf[SPI_BUF_SIZE+1]

void VGA_Init(void)
{
	// GPIO default: input
	// PA13, PA14 = SWD
	
	// Enable GPIO and DMA clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN|RCC_AHBENR_GPIOFEN|RCC_AHBENR_DMAEN;
	// Enable SPI, UART1 clock
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN|RCC_APB2ENR_USART1EN|							// Enable SPI, UART, SYSCFG
	                RCC_APB2ENR_SYSCFGCOMPEN;
	// Enable TIM3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
  // Select pin types
	GPIOA->MODER = GPIOA_MODER|PIN_ALT(PA7)|PIN_ALT(PA6)|PIN_OUTPUT(PA5); // MOSI, VSync, HSync
	GPIOA->AFR[0] = PIN_AFRL(PA7,0)|PIN_AFRL(PA6,1);											// MOSI,TIM3 CH1

	GPIOA->OTYPER = GPIOA_OTYPER;
	GPIOA->BSRR = GPIOA_BSRR;	
	GPIOA->AFR[1] = GPIOA_AFR1;
	
	// SPI: (SCK, MOSI) slew rate = 11 (fastest)
  // Don't seems to have an effect on the video quality.  Use default for EMI control
	
// GPIOA->OSPEEDR = PIN_OSPEED(PA7,GPIO_OSPEEDR_OSPEEDR0_1|GPIO_OSPEEDR_OSPEEDR0_1)|
//	                 PIN_OSPEED(PA5,GPIO_OSPEEDR_OSPEEDR0_1|GPIO_OSPEEDR_OSPEEDR0_1);

#ifdef DMA_SPI_TIMING_TWEAK
  GPIOB->MODER  = PIN_ALT(PB1);																			// TIM3 CH4 (Display enable)
	GPIOB->AFR[0] = PIN_AFRL(PB1,1);																	// TIM3 CH4
#else	
	GPIOB->MODER  = PIN_OUTPUT(PB1);
#endif	
	
  GPIOF->MODER  = PIN_OUTPUT(PF1)|PIN_INPUT(PF0);
  // TIM3 CH4 slew rate = 11 (fastest)
	GPIOB->OSPEEDR = PIN_OSPEED(PB1,GPIO_OSPEEDR_OSPEEDR0_1|GPIO_OSPEEDR_OSPEEDR0_1);
		
/*
         0                                  VGA_PIX_X
 				       _______________________________
  HSync   ____/                               \			  TIM3 C1: VGA_HSYNC
																															 
	SPI DMA   |																					TIM3 C2: tweak for IRQ latency for TIM1 C3	
          ______ _______________________________
	Display ______X_______________________________ 			TIM3 C4: VGA_HSYNC+VGA_HSYNC_BP+VGA_BORDER_LEFT

*/
	VGA_Line = 0;
	
	// TIM3 CH1: HSync
  TIM3->CCR1 =  VGA_HSYNC_CNT;																					// set rising edge
  TIM3->CCMR1 = TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1PE;			// OC1 PWM1, preload																					
								
	// TIM3 CH2 -> IRQ -> SPI DMA 3
  TIM3->CCR2 = VGA_DMA_START;
	
#ifdef DMA_SPI_TIMING_TWEAK
	// TIM3 CH4 -> Display Enable (tweaking only)
	TIM3->CCR4 = VGA_DISPLAY_ON;
  TIM3->CCMR2 = TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_0|TIM_CCMR2_OC4PE;			// OC4 toggle on match
  TIM3->CCER = TIM_CCER_CC1E|TIM_CCER_CC1P|TIM_CCER_CC4E; 							// OC1, OC2, OC4 enabled
#else
  TIM3->CCER = TIM_CCER_CC1E|TIM_CCER_CC1P; 														// OC1, OC2 enabled
#endif

	// TIM1 Init
	TIM3->PSC = TIM3_PRESCALER;																						// prescaler = pclk/2
  TIM3->ARR = VGA_DOTS_CNT;																							// timer reload = # of pixels per line
	TIM3->DIER |= TIM_DIER_UIE|TIM_DIER_CC2IE;														// TIM1 update interrupt, CC3 DMA, CC4 IRQ
	TIM3->EGR |= TIM_EGR_UG;	
	TIM3->BDTR |= TIM_BDTR_MOE;																						// Main output enable
  TIM3->CR1 |= TIM_CR1_CEN|TIM_CR1_URS;						 			 								// enable TIM, under/over flow updates only
									 	
  // SPI init
	SPI1->CR1 = SPI_CR1_MSTR|SPI_CR1_SSM|SPI_CR1_SSI|SPI_CR1_EXTRA; 			// Master, BR: Fpclk/2
	SPI1->CR2 = SPI_CR2_DATASIZE|SPI_CR2_TXDMAEN|SPI_CR2_EXTRA;						// set Data Size, SPI TX DMA enable 
																																				// TI mode: MOSI idle at 0.
	SPI1->CR1 |= SPI_CR1_SPE;

  // DMA Ch3 - SPI
	DMA1_Channel3->CPAR = (uint32_t) &SPI1->DR;

  // NVIC IRQ
  NVIC_SetPriority(TIM3_IRQn,TIM3_IRQ_PRIORITY);												// Highest priority
  NVIC_EnableIRQ(TIM3_IRQn);
	
	NVIC_SetPriority(PendSV_IRQn,PENDSV_PRIORITY);
	NVIC_EnableIRQ(PendSV_IRQn);
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR & TIM_SR_CC2IF)
	{
		DMA1_Channel3->CCR = DMA_CCR_PL_1|DMA_CCR_PL_0|DMA_CCR_MINC|				// Very high priority, memory increment
												 DMA_CCR_DIR|SPI_DMA_CCR_SIZE|DMA_CCR_EN;				// trigger DMA transfer

		if(Display_Flags & VGA_RENDER)																			// render loop
		{ 
			uint8_t i,*textbuf,*scanline,*font;
			uint16_t line = VGA_Line-(VGA_DISPLAY_START-1);
			
	    scanline = (Display_Flags & VGA_BUFFER)?ScanLine_Buf0+1:ScanLine_Buf1+1;			
	    font = (uint8_t *) &FONT_TABLE[line%FONT_ROW];			
			textbuf = &TEXT_BUF(0,line/FONT_ROW);

	    for(i=0;i<VGA_TEXT_X/2;i++)
		  {
	      *scanline++ = font[(*textbuf++)*FONT_ROW];
			  *scanline++ = font[(*textbuf++)*FONT_ROW];
		  }	
		}
		TIM3->SR &= ~TIM_SR_CC2IF;
	}
  else if(TIM3->SR & TIM_SR_UIF)
	{
	  VGA_Line++;
		
		switch(VGA_Line)
    {
			case VGA_VSYNC_START:
#ifdef VSYNC 
				VSYNC_ASSERT();																	// Set VSync
#else									
	      TIM3->CCER &= ~TIM_CCER_CC1P;										// CSync: flip polarity
#endif
				break;
			
			case VGA_VSYNC_STOP:							
#ifdef VSYNC 				
        VSYNC_DEASSERT();																// Reset VSync
#else
	      TIM3->CCER |= TIM_CCER_CC1P;
#endif			
				break;

			case VGA_DISPLAY_START-1:		
				Display_Flags = VGA_RENDER|VGA_BUFFER0;
				break;			

			case VGA_DISPLAY_START:	
				Display_Flags |= VGA_DISPLAY;
				break;						
			
			case VGA_DISPLAY_STOP-1:
			  Display_Flags &= ~VGA_RENDER;
			  break;
			
			case VGA_DISPLAY_STOP:
				Display_Flags = 0;
			  break;
			
			case VGA_LINES:																			// Reach bottom of display
				VGA_Line=0;
			
			  if (VerticalBlank)																// Callback code
			    (* VerticalBlank)();
				break;
			}
		
		if(Display_Flags)
		{
      if(Display_Flags & VGA_DISPLAY)
			{
				DMA1_Channel3->CCR &= ~DMA_CCR_EN;
				DMA1_Channel3->CNDTR = SPI_DMA_WORDS;							// # of transfers					
				DMA1_Channel3->CMAR = (uint32_t)((Display_Flags&VGA_BUFFER)?ScanLine_Buf0:ScanLine_Buf1);
				
				// Set PendAV
				SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
			}
			
			Display_Flags ^= VGA_BUFFER;
		}
		
		if (MicroTimer0) 
		  MicroTimer0--;
					
		TIM3->SR = ~TIM_SR_UIF;																// clear interrupt flag
	}
}

// Put ARM core to sleep and wait for TIM3 OC2 IRQ to wake it up.
void PendSV_Handler(void)
{
	NVIC_DisableIRQ(USART1_IRQn);
  NVIC_DisableIRQ(EXTI0_1_IRQn);
	
	// Clear pendSV flag
	SCB->ICSR |= SCB_ICSR_PENDSVCLR_Msk;
	
	__WFI();		// Sleep here
	
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_EnableIRQ(EXTI0_1_IRQn);	
 }

// Time delay in 32us ticks - Hsync
void Delay(uint16_t Ticks)
{
	MicroTimer0 = Ticks;
	
	while(MicroTimer0)
		/* Busy wait */;
}
