#ifndef _FONT_Terminal_Hex8x12_
#define _FONT_Terminal_Hex8x12_

typedef uint8_t FONT_t;
extern const uint8_t FONT_TABLE[4096];

// Displayed font size
// the number of screen lines, and so the amount of screen buffer memory required is 480/FONT_Y*80
// and for original 12 line font it results in 3200 bytes needed for just screen buffer. This does not leave
// enough RAM for ansi terminal emulation and other needs. 16 row font gives 30 lines of text, and it
// looks much better anyway.
//
#define FONT_X 8
#define FONT_Y 16

// Padded size
#define FONT_ROW 16
#define FONT_COL 8

#define FONT_START 0
#define FONT_END 255

#endif
