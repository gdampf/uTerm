/*
 * Shell.h
 *
 * Created: 08/09/2012 10:10:18 PM
 *  Author: User Unknown
 */ 

#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <stdint.h>

#define Char_BS		0x08
#define Char_CR		0x0d
#define Char_LF		0x0a

#define PROMPT		"$ "

#define LINEBUFSIZE	75
#define Desc_Col	10

typedef struct
{ const char *Token;
  const char *Description;
  void (* func)(void);
 } CMD_TBL;

void Shell_Init(void);
void Shell_Exec(void);
uint8_t ExecCmd(void);
void Shell_Term_Task(void);
uint32_t GetHexParm(void);

void Help(void);
extern const CMD_TBL Command_Table[];
extern char *LinePtr;
#endif /* SHELL_H_ */

