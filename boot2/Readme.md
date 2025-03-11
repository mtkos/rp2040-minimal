## the secondary bootloader

The rp2040 has the special property of having no on-board flash. Instead, external flash can be used to store instructions and data, by using the XIP (execute in place) interface. See [rp2040],
section 2.6.3. The secondary bootloader takes care of the necessary configuration. It is not part of the bootrom, so that different types of flash can be used, each with their own optimized
secondary bootloader. The raspberry pi pico board uses a 16Mbit w25q080 flash. The secondary bootloader is called bs2\_default\_padded\_checksummed.S. It is built from boot2\_w25q080.S by assembling,
padding the resulting file with zeroes and adding a checksum (required by the bootrom), resulting in a 256-byte file which needs to be placed at the start of flash. 
The CRC32 parameters to be used in the checksum calculation can be found in [rp2040], section 2.8.1.3.1.
To show that there is no magic involved, I have taken the necessary parts from the SDK (some assembly code in the present directory and mainly register definitions in directory ../sdk\_include)
and written a simple Makefile which builds the secondary bootloader from source (command: 'make pad'). To use the secondary bootloader with picolibc a patched version
(with .section .text.init.enter, instead of .boot2) can be built by issuing the command 'make patch'. All the other programs in this repository require one of these as source file, so they
should be built before trying to build one of the other programs.

The secondary bootloader is *not* involved in initialization code like setting op the vector table. This is done by the startup.s code. So, a typical program uses 3 source files: main.c, startup.s
and a secondary bootloader.

