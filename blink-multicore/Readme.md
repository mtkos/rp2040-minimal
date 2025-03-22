# the blink-multicore program

The rp2040 chip has two cortex-m0+ cores. By default, code runs on core 0. The bootrom makes it easy to also run code on core 1. It installs a small 'bootloader' on the second core and then puts
it to sleep. To run a function on the second core one simply has to wake it up and send some information (vector table address, initial stack pointer, and address of the function you want to run)
using the inter-processor fifos ([rp2040] section 2.3.1.4). The whole process is described in section 2.8.2 of [rp2040]. For processor 0 we use SRAM5 as stack (\_estack = 0x20042000 in the linker
script, remember that the stack grows *downwards*). For processor 1 we use SRAM4 (\_estack1 = 0x20041000). The example program blinks two LEDs (one for each core) with different frequencies. 
A processor can determine its identity (0 or 1) by reading the CPUID register ([rp2040] section 2.3.1.7). Hence we can run the same function (blink) on both cores and have the processor determine
the pin and blink frequency to use.
