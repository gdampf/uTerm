/*
 * vga-min.c
 *
 * March-13-16, 8:10:22 PM
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
#include "font.h"

VGA_t VGA;
uint8_t TextBuffer[VGA_TEXT_X*VGA_TEXT_Y];
static uint8_t ScanLineBuf[SPI_BUF_SIZE];
volatile uint8_t MicroTimer0, MicroTimer1;

void VGA_Init(void)
{
	// GPIO default: input
	// PA13, PA14 = SWD
	
	// Enable GPIO and DMA clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN|RCC_AHBENR_GPIOBEN|RCC_AHBENR_GPIOFEN|RCC_AHBENR_DMAEN;
	// Enable SPI, UART1 clock
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN|RCC_APB2ENR_USART1EN|					// Enable SPI, UART, SYSCFG
	                RCC_APB2ENR_SYSCFGCOMPEN;
	// Enable TIM3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
  // Select pin types
	GPIOA->MODER = GPIOA_MODER|PIN_ALT(PA7)|PIN_ALT(PA6)|PIN_OUTPUT(PA5); // MOSI, VSync, HSync
	GPIOA->AFR[0] = PIN_AFRL(PA7,0)|PIN_AFRL(PA6,1);									// MOSI,TIM3 CH1

	GPIOA->PUPDR = GPIOA_PUPDR;
	GPIOA->OTYPER = GPIOA_OTYPER;
	GPIOA->BSRR = GPIOA_BSRR;	
	GPIOA->AFR[1] = GPIOA_AFR1;
	
	// SPI: (SCK, MOSI) slew rate = 00 (2MHz), 01 (10MHz), 11 (50MHz)
  // Don't seems to have an effect on the video quality.  Use default for EMI control
	
 GPIOA->OSPEEDR = PIN_OSPEED(PA7,GPIO_OSPEEDR_OSPEEDR0_1);

#ifdef VGA_BACKGROUND
  GPIOB->MODER  = PIN_ALT(PB1);																			// TIM3 CH4 (Display enable)
	GPIOB->AFR[0] = PIN_AFRL(PB1,1);																	// TIM3 CH4
#else	
	GPIOB->MODER  = PIN_OUTPUT(PB1);
#endif	
	
  GPIOF->MODER  = PIN_OUTPUT(PF1)|PIN_INPUT(PF0);

	GPIOB->OSPEEDR = PIN_OSPEED(PB1,GPIO_OSPEEDR_OSPEEDR0_1);
/*
         0                                  VGA_PIX_X
 				       _______________________________
  HSync   ____/                               \			  TIM3 C1: VGA_HSYNC
																															 
	SPI DMA   |																					TIM3 C2: tweak for IRQ latency for TIM1 C3	
          ______ _______________________________
	Display ______X_______________________________ 			TIM3 C4: VGA_HSYNC+VGA_HSYNC_BP+VGA_BORDER_LEFT

*/
	VGA.Line = 0;
	
	// TIM3 CH1: HSync
  TIM3->CCR1 =  VGA_HSYNC_CNT;																					// set rising edge
  TIM3->CCMR1 = TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1PE;			// OC1 PWM1, preload																					
								
	// TIM3 CH2 -> IRQ -> SPI DMA 3
  TIM3->CCR2 = VGA_DMA_START;
	
#ifdef VGA_BACKGROUND
	// TIM3 CH4 -> Display Enable (tweaking only)
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
	SPI1->CR2 = SPI_CR2_DATASIZE|SPI_CR2_TXDMAEN|SPI_CR2_EXTRA;						// TI Mode, set Data Size, SPI TX DMA enable 
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
{ uint8_t i,*textbuf, *font, *scanline;
	
	if(TIM3->SR & TIM_SR_CC2IF)
	{
		DMA1_Channel3->CCR = DMA_CCR_PL_1|DMA_CCR_PL_0|DMA_CCR_MINC|				// Very high priority, memory increment
												 DMA_CCR_DIR|SPI_DMA_CCR_SIZE|DMA_CCR_EN;				// trigger DMA transfer

		if(VGA.Render)																											// render loop
		{ 		   
		  font = (uint8_t *) &FONT_TABLE[VGA.Font_CurRow];			
      textbuf = VGA.TextBuffer_Ptr+VGA_PRE_RENDER;
	    scanline = ScanLineBuf+1+VGA_PRE_RENDER;
			
	    for(i=0;i<VGA_POST_RENDER/2;i++)
		  {
	      *scanline++ = font[(*textbuf++)*FONT_ROW];
			  *scanline++ = font[(*textbuf++)*FONT_ROW];
		  }

			if(++VGA.Font_CurRow == FONT_Y)
			{ 
				VGA.Font_CurRow = 0;
			  VGA.TextBuffer_Ptr+= VGA_TEXT_X;
			}
			
	    font = (uint8_t *) &FONT_TABLE[VGA.Font_CurRow];			
      textbuf = VGA.TextBuffer_Ptr;
	    scanline = ScanLineBuf+1;			

	    for(i=0;i<VGA_PRE_RENDER/2;i++)
		  {
	      *scanline++ = font[(*textbuf++)*FONT_ROW];
			  *scanline++ = font[(*textbuf++)*FONT_ROW];
		  }			
		}

#ifdef VGA_BACKGROUND
		if(VGA.Display)
		{  TIM3->CCR4 = VGA_DISPLAY_OFF;
		   TIM3->CCMR2 = TIM_CCMR2_OC4M_1;																	// OC4 Clear on match
		}
#endif

		TIM3->SR &= ~TIM_SR_CC2IF;
	}
  else if(TIM3->SR & TIM_SR_UIF)
	{
		switch(VGA.Line++)
    {
			case VGA_VSYNC_START:
				if (VGA.DPMS_Mode < DPMSModeSuspend)
					VSYNC_ASSERT();																	// Set VSync
				else
					VSYNC_PORT->BSRR = PIN_CLR(VSYNC_PIN);					
				
			  if ((VGA.DPMS_Mode==DPMSModeOn)||(VGA.DPMS_Mode==DPMSModeSuspend))
          TIM3->CCMR1 |= TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1PE;		// OC1 PWM1, preload																					
				else
					TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1PE); // Forced off
				break;
			
			case VGA_VSYNC_STOP:
				if (VGA.DPMS_Mode<DPMSModeSuspend)
					VSYNC_DEASSERT();																// Reset VSync
				
			  VGA.Render = 0;
				VGA.Display = 0;
  			VGA.TextBuffer_Ptr = TextBuffer;
				break;

			case VGA_DISPLAY_START-1:		
				VGA.Render = 1;
				font = (uint8_t *) &FONT_TABLE[VGA.Font_CurRow];			
				textbuf = VGA.TextBuffer_Ptr;
				scanline = ScanLineBuf+1;			

				for(i=0;i<VGA_PRE_RENDER/2;i++)
				{
					*scanline++ = font[(*textbuf++)*FONT_ROW];
					*scanline++ = font[(*textbuf++)*FONT_ROW];
				}
				break;			

			case VGA_DISPLAY_START:
				VGA.Display = 1;
				break;						
			
			case VGA_DISPLAY_STOP-1:
			  VGA.Render = 0;
			  break;
			
			case VGA_DISPLAY_STOP:
				VGA.Display = 0;	
			  break;
			
			case VGA_LINES:																			// Reach bottom of display
				VGA.Line = 0;
			  VGA.Font_CurRow = 0;

			  if (VGA.VerticalBlank)														// Callback code
			    (* VGA.VerticalBlank)();
				break;
			}
		
      if(VGA.Display)
			{
				DMA1_Channel3->CCR &= ~DMA_CCR_EN;
				DMA1_Channel3->CNDTR = SPI_DMA_WORDS;							// # of transfers					
				DMA1_Channel3->CMAR = (uint32_t)ScanLineBuf;
								
#ifdef VGA_BACKGROUND
				TIM3->CCR4 = VGA_DISPLAY_ON;
				TIM3->CCMR2 = TIM_CCMR2_OC4M_0;										// OC4 active on match
#endif	
				// Set PendAV
				SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
			}
		
		if (MicroTimer0) 
		  MicroTimer0--;
		
		if (MicroTimer1) 
		  MicroTimer1--;
		
		TIM3->SR &= ~TIM_SR_UIF;															// clear interrupt flag
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
