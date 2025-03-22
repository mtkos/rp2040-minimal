# the ws2812d program

This program works differently from the corresponding programs in my ch32v003-minimal and stm32f103-minimal repositories. The reason is that rp2040 has a programmable io (PIO) peripheral,
which is ideally suited for tasks such as implementing the ws2812d protocol. The description of this peripheral takes an entire chapter (chapter 3) of [rp2040] which I will not try to summarize
here. The program has the usual parts: startup.s containing the (very tiny) vector table, the second stage bootloader, the main program (main.c) and a fourth component, the PIO program. This last
program is very simple-minded. It consists of out, set and jmp instructions only. The datasheet also has a ws2812 example, with a shorter, more sophisticated program. Our PIO program is translated
into an array of machine readable PIO instructions by the pioasm program, which you have to take from the SDK. Because it is copyrighted I have not included it in this repository. 
Its output contains some SDK specific code which we trim off to get an include file ws2812d.pio.h, which contains the instructions, together with the addresses 'wrap' and 'wrap_target',
which are essentially labels of the pio program.

The main program is not complicated. It uses the 12MHz XOSC clock (the ROSC is not accurate enough). Thus, a zero bit corresponds to 3 cycles high and 12 cycles low, and a one bit to 12 cycles
high and 3 cycles low. The main program initializes the PIO peripheral and the XOSC clock, and sets pin 23 as PIO output. Then the instructions are loaded into the instruction registers of the PIO
peripheral. After this, program wrapping and pin mapping are configured (see [rp2040] 3.5.2 and 3.2.5). Finally, autopull ([rp2040] 3.5.4) is configured so that after 24 bits have been read
a new word is pulled in from the FIFO without intervention of the CPU. Sending data for one LED is then simply a question of writing one word (32 bits, of which only 24 are used) to the FIFO. See
the send_color function. My board has one built-in ws2812, so I send only one word of color data.

For a good understanding of the PIO peripheral it is worth noting that the direction in which data flows is always the direction as seen from the main processor, not the state machine. Thus
the instruction 'out x, 1' means that one bit is shifted *into* the X register. The TX FIFO contains data which is *input* to the state machine, etc.

Concluding, it is not difficult to use the PIO without using the SDK.
