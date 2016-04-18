#ifndef _FONT_Terminal_Hex8x12_
#define _FONT_Terminal_Hex8x12_

typedef uint8_t FONT_t;
extern const uint8_t FONT_TABLE[];

// Original size
#define FONT_X 8
#define FONT_Y 12

// Padded size
#define FONT_ROW 16
#define FONT_COL 8

#define FONT_START 32
#define FONT_END 127

//#define BM(B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15) \
//0xff-B0,0xff-B1,0xff-B2,0xff-B3,0xff-B4,0xff-B5,0xff-B6,0xff-B7,0xff-B8,0xff-B9,0xff-B10,0xff-B11,0xff-B12,0xff-B13,0xff-B14,0xff-B15

#define BM(B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15) \
B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,B10,B11,B12,B13,B14,B15
#endif

