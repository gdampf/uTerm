/*
 * vgafont.c
 *
 *  Author: Madis Kaal <mast@nomad.ee>
 *  Copyright (c) 2017 by Madis Kaal
 
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

