/*
 * cmd.c
 *
 * Created: 08/09/2012 10:29:05 PM
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
 
#include "shell.h"
#include "lib.h"
#include "matrix.h"

uint32_t GetIntParm(void);

void SETTIME(void)
{
	 hour=GetIntParm();
	 minute=GetIntParm();
	 second=GetIntParm();
}

const CMD_TBL Command_Table[]= 
{ 
  {"HELP","Show a list of commands.",	Help},
	{"SETTIME","HH MM SS", SETTIME},
	
  {0}		/* Marks end of list */
 };
