
#ifndef _STM32F030_
#define _STM32F030_

#include "stdio.h"
#include <stdint.h>

#include "stm32f0xx.h"
#include "system_stm32f0xx.h"

enum GPIO_A_PINS
{ PA0_CE, 
	PA1_nCS, 
	PA2_TXD, 
	PA3_RXD, 
	PA4_nSS, 
	PA5_SCK, 
	PA6_MISO, 
	PA7_MOSI,
  PA9_SCL = 9, 
  PA10_SDA = 10,
  PA13_SWDIO = 13, 
  PA14_SWCLK = 14
};

enum GPIO_B_PINS
{
	PB1_IRQ =1
};

enum GPIO_F_PINS
{
	PF0_OSC_IN,
  PF1_OSC_OUT
};

#define PIN_MOD(BIT,FUNC) ((FUNC)<<(BIT*2))
#define PIN_ANALOG(BIT)		PIN_MOD(BIT,0x03)
#define PIN_INPUT(BIT)		PIN_MOD(BIT,0x00)
#define PIN_OUTPUT(BIT)		PIN_MOD(BIT,0x01)
#define PIN_ALT(BIT)			PIN_MOD(BIT,0x02)

#endif
