/*
 * serial.c
 *
 * Created: March-16-2016, 3:52:04 PM
 *  Author: K. C. Lee
 * Copyright (c) 2015 by K. C. Lee
 
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
#include "vga-min.h"
#include "fifo.h"

FIFO_Data_t RxBuf[RX_FIFO_Size],TxBuf[TX_FIFO_Size];

FIFO FIFO_Rx = { RxBuf, sizeof(RxBuf)-1 };
FIFO FIFO_Tx = { TxBuf, sizeof(TxBuf)-1 };

void USART_Init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;									// Enable UART1 clock
  USART1->BRR = CPU_CLOCK/UART_BAUD;										// Set default baud rate
#ifdef AUTOBAUD
	USART1->CR2 = USART_CR2_ABRMODE_0|USART_CR2_ABREN;		// enable autobaud, 1 stop bit
#endif
  USART1->CR1 = USART_CR1_RXNEIE|												// Receive not empty
								USART_CR1_RE|USART_CR1_TE|USART_CR1_UE; // 8-bit, 1 start bit, no parity, 16X oversampling

	FIFO_Clear(&FIFO_Rx);
	FIFO_Clear(&FIFO_Tx);
	
  // NVIC IRQ
  NVIC_SetPriority(USART1_IRQn,USART_IRQ_PRIORITY);			// Lowest priority																	// Highest priority
  NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)
{
	if(USART1->ISR & USART_ISR_RXNE)											// Rx data
	{
		FIFO_Write(&FIFO_Rx,USART1->RDR);
	}
	
	if(USART1->ISR & USART_ISR_TXE)												// Tx empty
	{
		uint8_t TxD;
		
		if(FIFO_Read(&FIFO_Tx,&TxD))
			USART1->TDR = TxD;																// TDR is 16-bit!
		else
			USART1->CR1 &= ~USART_CR1_TXEIE;									// Disable Tx Empty interrupt
	}
}

void Putchar( uint8_t data )
{
	while(!FIFO_Write(&FIFO_Tx,data))
	  /* busy wait */;
	
  USART1->CR1 |= USART_CR1_TXEIE;												// Enable Tx Empty interrupt
}
