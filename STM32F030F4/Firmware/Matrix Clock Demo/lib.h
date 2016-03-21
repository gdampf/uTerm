/*
 * lib.h
 *
 * Created: 08/09/2012 10:19:34 PM
 *  Author: K. C. Lee
 * License: Creative Commons Attribution-ShareAlike 4.0 International Public License
 * Copyright (c) 2015 by K. C. Lee
 */ 

#ifndef LIB_H_
#define LIB_H_

uint8_t Puts(char *s);
void NewLine(void);
void Space(void);
void FillSpc(char n);
void Puthex2(uint8_t n);
void Puthex4(uint16_t n);
uint8_t Hex(char ch);
uint8_t Puts(char *s);

char ToUpper(char ch);
char IsWhiteSpc(char ch);

#endif /* LIB_H_ */

