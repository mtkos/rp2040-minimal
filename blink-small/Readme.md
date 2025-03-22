# the blink-small program

This program works more or less in the same way as its stm32f103 counterpart. Initialization is done by the reset subsystem (section 2.14 of the datasheet). GPIO is documented in section
2.19 of the datasheet. One interesting thing to note is that in many cases individual bits of configuration registers can be set or cleared 'atomically', i.e., without a read-modify-write sequence.
This is documented in section 2.1.2 of the datasheet and illustrated in the first line of our program: the IO_BANK0 (GPIO) subsystem can be reset by writing the corresponding bit of the
'clear'-alias of the reset register. Similarly, in the program's main loop, the pin can be toggled by writing one bit to the 'xor' alias of the GPIO output register. Finally, it should be
noted that pins have to be configured explicitly for GPIO output. See section 2.19.2 of the datasheet. The resulting binary is about 70 bytes. As a result, it does not need a secondary bootloader
([rp2040], section 2.8). During conversion to uf2, by the bin2uf2 utility, the checksum required by the rp2040 primary (ROM) bootloader is added. As a result, the executable will be accepted by
the primary bootloader, loaded into SRAM and start executing from there. Startup code, for creating a vector table is also not necessary.
