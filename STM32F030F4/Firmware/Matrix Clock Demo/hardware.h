#ifndef _HARDWARE_H_
#define _HARDWARE_H_

/*
 * hardware.h
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

#include "gpio.h"
#include <stm32f0xx.h>

#define GPIOA_MODER (PIN_ALT(PA14)|PIN_ALT(PA13)|				/* SWCLK, SWDIO */	\
										 PIN_ALT(PA10)|PIN_ALT(PA9)|				/* RxD, TxD			*/	\
										 PIN_OUTPUT(PA4)|										/* ??? ???			*/	\
										 PIN_OUTPUT(PA3)|PIN_OUTPUT(PA2)|		/* ??? ???			*/	\
		                 PIN_OUTPUT(PA1)|PIN_OUTPUT(PA0))		/* PS/2 PS/2		*/	\
										 
#define GPIOA_OTYPER (PIN_OPENDRAIN(PA1)|PIN_OPENDRAIN(PA0))	// PS/2
#define GPIOA_BSRR	 (PIN_SET(PA1)|PIN_SET(PA0))
#define GPIOA_AFR1	 (PIN_AFRH(PA14,0)|PIN_AFRH(PA13,0)|/* SWCLK, SWDIO	*/	\
											PIN_AFRH(PA10,1)|PIN_AFRH(PA9,1))	/* RxD, TxD 		*/

#define SPI_CR1_EXTRA SPI_CR1_LSBFIRST 
#define SPI_CR2_EXTRA 0

#endif
