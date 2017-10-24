#include <stdint.h>
#include "vgafont.h"


// include the actual bitmap depending on font size. keep in mind that smaller fonts result in
// more lines of text, and need more RAM for screen buffer
//
const uint8_t FONT_TABLE[4096] = 
{
#if FONT_Y==16
#include "vga16.fnt.c"
#endif
#if FONT_Y==12
#include "vga12.fnt.c"
#endif
};

