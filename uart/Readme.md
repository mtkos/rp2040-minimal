# the uart program

This program uses the (maximal for this MCU, see [rp2040] section 2.18.1) 133MHz clock frequency. The UART has strict timing requirements, so the default (ROSC) oscillator cannot be used. Instead,
we use the 12MHz crystal oscillator ([rp2040] section 2.16), from which, using the PLL ([rp2040], section 2.18), we derive the 133MHz system (and also peripheral) clock. Switching glitchlessly
from the ~6.5MHz clock running at boot time to this 133MHz is a little bit involved. To understand how it should be done, see [rp2040], section 2.15. To understand that section you need to know the
difference between 'clocks' (like the system clock, peripheral clock, USB clock) and 'clock sources' (ring oscillator, crystal oscillator, PLL).

Once the clock is running the UART needs to be configured. This is documented in [rp2040], section 4.2. The most interesting part to note is that the baudrate can be configured very accurately.
It is derived from the peripheral clock (usually equal to the system clock, in our case 133MHz) using two registers, UARTIBRD and UARTFBRD. They form the integer and fractional parts of the ratio
between system clock frequency and (baudrate multiplied by 16). See [rp2040], section 4.2.3.2.1. The explanation given there is a little bit involved. The calculation done in our program might well
be easier to understand.
