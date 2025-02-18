# the blink-small program

This program works more or less in the same way as its stm32f103 counterpart. Initialization is done by the reset subsystem (section 2.14 of the datasheet). GPIO is documented in section
2.19 of the datasheet. One interesting thing to note is that in many cases individual bits of configuration registers can be set or cleared 'atomically', i.e., without a read-modify-write sequence.
This is documented is section 2.1.2 of the datasheet and illustrated in the first line of our program: the IO_BANK0 (GPIO) subsystem can be reset by writing the corresponding bit of the
'clear'-alias of the reset register. Similarly, in the program's main loop, the pin can be toggled by writing one bit to the 'xor' alias of the GPIO output register. Finally, it should be
noted that pins have to be configured explicitly for GPIO output. See section 2.19.2 of the datasheet. Looking at the Makefile, you will see how the secondary bootloader has to be added to the
program's sources. Where it lands in flash memory is determined by the linker script: the first 0x100 = 256 bytes of flash memory.
