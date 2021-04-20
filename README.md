## uTerm


uTerm (micro-Term) is a VT100-like terminal for the Z80-MBC2 (https://hackaday.io/project/159973). It has a VGA out and PS/2 keyboard connector, a power supply for the Z80-MBC2 and a "transparent" serial-USB port.

This fork of https://github.com/SuperFabius/uTerm was originally made for supporting German Keyboard-Layout.
Then, I recognized, that some kind of keyboards with PS/2 doesn't react at the given firmware. They are just sending out 0xAA all the time and no key codes. By comparing the signals to a system, where they are working fine, I found that they need a reset (0xff), to work propperly.
This fork solve therefore three things:

1. the state machine for the keyboard has been changed to support this kind of keyboards, which are waiting for reset.
2. the right alt key is now used as a separate modifier to support the ALTGR-Codes on many non US-Keyboard-Layouts.
3. the keys are changed corresponding to German Layout

To compile this code, I used Keil µVision5 under Windows X!

Here comes the original Text:

These are the sources modified for the uTerm forked from the Madis Kaal 
repository (forked from the original repository of K. C. Lee: 
https://github.com/FPGA-Computer/STM32F030F4-VGA. Original project 
page: https://hw-by-design.blogspot.com/2018/07/low-cost-vga-terminal-module-project.html)


uTerm "project" page: https://hackaday.io/project/165325

NOTE: I've updated here only the changed source files, so you must recompile all to get the new executable.

Supported uTerm boards:

- A071218-R250119
- A071218-R290319

Supported uTerm-S boards:

- A200419

------------------------------------------------------------------------------

**UPDATE (11/2019):** Solved a bug (by gkaufman) using the right CTRL key in some situations (i.e. CTRL-L)

------------------------------------------------------------------------------

In the following the original text. 

------------------------------------------------------------------------------
------------------------------------------------------------------------------


VT100 emulation, font editor, 16-line font, and support for inverse fonts
added by Madis Kaal <mast@nomad.ee> http://www.nomad.ee


The individual license(s) are in each directories.

Directories:
------------------------------------------------------------------------------
font conv/ 
- source code + Windows console executable for a font conversion program.
It imports GLCD font Creator file and converter it to a C font table
of the comverted scan line bitmaps that is to be used with the VGA library.

- The converter is compiled using Pelles C
http://www.pellesc.de/index.php?page=start&lang=en

- "GLCD Font Creator" MikroElektronika
http://www.mikroe.com/glcd-font-creator/


Code in this directory is licensed under "Simplified BSD License"

-------------------------------------------------------------------------------
STM32F030F4/Hardware/LT Spice Simulation
files in this directory is licensed under "Simplified BSD License"

-------------------------------------------------------------------------------
STM32F030F4/Hardware/Sketchup 3D Model
Creative Commons 4.0 Attribution-NonCommercial-NoDerivs International
http://creativecommons.org/licenses/by-nc-nd/4.0/

This is to prevent someone photoshopping this as their own project for crowd-funding 
scams. You are free to generate your own model using Eagleup from your new layout.

-------------------------------------------------------------------------------
STM32F030F4/Hardware/
Schematic/Layout is distributed with Creative Commons 4.0 Attribution-NonCommercial
http://creativecommons.org/licenses/by-nc/4.0/

If you want to sell this and want a different licensing term, please contact me.

-------------------------------------------------------------------------------
STM32F030F4/Firmware/

Source code distributed under GPLV3, with exception of fontedit.py that is
distributed under BSD license.
