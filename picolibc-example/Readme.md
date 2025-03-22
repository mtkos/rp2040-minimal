# the picolib-example program

Using picolibc requires a little tweaking. To get the second stage bootloader at the first 256 of flash, we convert the raw bytes
of the binary to an assembler 'program', boot.s, padding it with zeroes to a size of 256 bytes, with .section attribute .text.init.enter. The picolibc linker script places this section
at the beginning of flash.
