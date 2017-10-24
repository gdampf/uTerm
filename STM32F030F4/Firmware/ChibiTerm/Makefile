#
# this makefile just extracts the binary from compiler output and flashes it
# wine,st-flash and keil tools need to be installed
#
# on OSX the flashing is not reliable. when the first attempt comes back with error message
# then pull the microcontroller reset pin to ground to do hard reset, and try again
# you also need to do hardware reset again after the flashing is complete
#
flash:
	wine /Keil_v5/ARM/ARMCLANG/bin/fromelf --only=ExtFlashSection --i32 --output=Objects\\VGA.hex Objects\\VGA.axf
	st-flash --format ihex write Objects/VGA.hex
