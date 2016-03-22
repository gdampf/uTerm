#ifndef _MATRIX_H_
#define _MATRIX_H_

/*
 * matrix.c
 *
 * Created: March-16-2016, 4:03:10 PM
 *  Author: K. C. Lee
 * Copyright (c) 2016 by K. C. Lee
 */ 

#include <stdint.h>

#define BACKGROUND						0x60000000UL
#define FOREGROUND						0x00000000UL

#define HOUR_FORMAT						24
#define TICK_RELOAD						60

// Clock frequency = 31250/525 = 1250/21
#define TICK_INC							21
#define TICK_THRESHOLD				1250

// update rate
#define TIME_RATE	  					10
#define BACKGROUND_RATE				2
#define RAIN_RATE							2

typedef struct
{
	uint8_t X_pos;
	uint8_t Y_pos;
	uint8_t length;
} Raindrop;

#define RAIN_DROPS						6
#define RAIN_DROP_LENGTH			40
#define RAIN_DROP_LENGTH_MIN	8
#define RAIN_DROP_Y						10
#define RAIN_DROP_X						60
#define RAIN_DROP_X_INC				15

#define BLOCK_CURSOR					(FONT_END-FONT_START)

#define CLOCK_X								8
#define CLOCK_Y								7

extern volatile uint8_t hour, minute, second;
#endif
