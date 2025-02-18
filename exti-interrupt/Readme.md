# the exti-interrupt program

This works as in my stm32f103-minimal repository. Only the interrupt numbers are different. They can be found in section 2.3.2 of [RP2040]. IO\_IRQ\_BANK0, which is the one we need, has interrupt
number 13. This corresponds to position 13 + 16 = 29 in the vector table, so startup.s uses this number.
