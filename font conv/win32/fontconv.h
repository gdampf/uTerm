#ifndef _FONTCONV_H_
#define  _FONTCONV_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
//#include <WinNT.h>

#define FONT_XMAX	32
#define FONT_YMAX	16

#define LINE_SIZE	255

#define C_COMMENT	"//"
#define C_COMMENT_LEN	2

#define FONTNAME	"FontName"
#define FONTSIZE	"FontSize"
#define PARM_START	11
#define WARNING		"WARNING"
#define FONTDECL	"const"
#define DECL_END	"};"
#define TOKEN		" ,\n"
#define TOKEN_COMMENT	"\n"

// uncomment to output data in binary
//#define OUTPUT_BIN


#endif
