# the exti-interrupt program

This works as in my stm32f103-minimal repository. Only the interrupt numbers are different. They can be found in section 2.3.2 of [RP2040]. IO\_IRQ\_BANK0, which is the one we need, has interrupt
number 13. This corresponds to position 13 + 16 = 29 in the vector table, so startup.s uses this number. The electrical characteristics of a GPIO pin are determined by the PADS\_BANK0 registers
([rp2040], section 2.19.6.3). In my board, closing the switch connected to GPIO24 pulls it low. For that reason we have to activate the pullup for this pin. To debounce it we also activate
the Schmitt trigger.
