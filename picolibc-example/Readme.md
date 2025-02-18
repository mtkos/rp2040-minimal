# the picolib-example program

Using picolibc requires a little tweaking. Its linker script only has two memory sections: flash and ram. To get the second stage bootloader at the beginning of flash we use a patched version,
changing its .section attribute from .boot2 to .text.init.enter. The picolibc linker script places this section at the beginning of flash, i.e. at the first 256 bytes. We then can have the start of
flash simply at address 0x10000000 ([rp2040] section 2.2.1 and 2.6.3) and everything works as expected. Note that the second stage bootloader sets the VTOR (vector table offset register) to
0x10000100, i.e the address immediately following the second stage bootloader. This is exactly where the code from startup.s (setting the vector table, section .init) lands.
