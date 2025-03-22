# the secondary bootloader

The rp2040 has the special property of having no on-board flash. Instead, external flash is used to store instructions and data, by using the XIP (execute in place) interface. See [rp2040],
section 2.6.3. The secondary bootloader takes care of the necessary configuration. It is not part of the bootrom, so that different types of flash can be used, each with their own optimized
secondary bootloader. The program boot2.c is a simple secondary bootloader. It is not optimized (for instance, it does not use quad-SPI). The linker script (ld/Link.ld) places its section
(.boot2) in the first 256 bytes of flash. The program initializes the XIP interface. Then it sets the processor's VTOR register (indicating where the vector table starts) to point just
after the secondary bootlader. Finally, it initializes the stack pointer and branches to the reset handler. I did not succeed in modifying picolibc's linker script to place the secondary
bootloader in the first 256 bytes of flash. For that reason I used a little hack. The 'make pad' command creates a 256 byte file boot.s which essentially is the binary of boot.c, padded with
zeroes. The boot.s binary has section .text.init.enter, so that the picolibc linker script places it at the start of flash.

The secondary bootloader is *not* involved in initialization code like setting op the vector table. This is done by the startup.s code. So, a typical program uses 3 source files: main.c, startup.s
and a secondary bootloader (boot.c or boot.s). The latter one is not necessary if your binary is smaller than 252 bytes, see for example the 'blink-small' program.

