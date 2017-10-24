# The MIT License (MIT)
# 
#  Copyright (c) 2017 Madis Kaal <mast@nomad.ee>
# 
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#
#
# this makefile just  flashes the compiler produced hex file, optionally you can extract the
# hex out of .elf as shown below
#
# on OSX the flashing is not reliable. when the first attempt comes back with error message
# then pull the microcontroller reset pin to ground to do hard reset, and try again
# you also need to do hardware reset again after the flashing is complete
#
flash:
	#wine ../../../../Keil_v5/ARM/ARMCLANG/bin/fromelf --only=ExtFlashSection --i32 --output=Objects\\VGA.hex Objects\\VGA.axf
	st-flash --format ihex write Objects/VGA.hex
