# the timer program

This program uses the PWM timer peripheral ([rp2040], section 4.5) to blink two LEDs, at pins 0 and 1, with different duty cycles. The program is essentially the same as its stm32f103 counterpart,
although the peripherals are organized a little bit differently. The program assumes a clock frequency of 6.5MHz, which is the frequency of the default (ROSC) oscillator. This clock source is
documented in section 2.17 of [rp2040]. That section says: 'During boot the ROSC runs at a nominal 6.5MHz and is guaranteed to be in the range 1.8MHz to 12MHz.' For this reason the LEDs may blink
faster or slower than  once per second, depending on your particular rp2040. ROSC should not be used when precise timing is needed, for instance when using the UART.
