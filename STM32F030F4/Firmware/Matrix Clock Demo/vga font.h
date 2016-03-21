#ifndef _FONT_Less_Perfect_DOS_VGA8x15_
#define _FONT_Less_Perfect_DOS_VGA8x15_

#include <stdint.h>

extern const uint8_t Less_Perfect_DOS_VGA8x15[];
typedef uint8_t FONT_Less_Perfect_DOS_VGA8x15_t;

// Original size
#define FONT_Less_Perfect_DOS_VGA8x15_X 8
#define FONT_Less_Perfect_DOS_VGA8x15_Y 15

// Padded size
#define FONT_ROW 16
#define FONT_COL 8
#define FONT_TABLE	Less_Perfect_DOS_VGA8x15
#define FONT_START	32
#define FONT_END		127
#endif

