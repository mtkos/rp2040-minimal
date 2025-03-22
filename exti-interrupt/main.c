#include <stdint.h>

#include "../include/common.h"
#include "../include/resets.h"
#include "../include/sio.h"
#include "../include/io_bank0.h"
#include "../include/pads_bank0.h"
#include "../include/m0plus.h"

#define IO_IRQ_BANK0_IRQn 13

#define PIN25 25

void IO_IRQ_BANK0_Handler() __attribute__((interrupt));

void IO_IRQ_BANK0_Handler(){

    REG(IO_BANK0_BASE + IO_BANK0_INTR3_OFFSET) = IO_BANK0_INTR3_GPIO24_EDGE_HIGH_BITS;
}

void prog(){

    REG(RESETS_BASE + RESETS_RESET_OFFSET + REG_ALIAS_CLR_BITS) = RESETS_RESET_IO_BANK0_BITS;
    while((~(REG(RESETS_BASE + RESETS_RESET_DONE_OFFSET)) & RESETS_RESET_DONE_IO_BANK0_BITS));

    REG(IO_BANK0_BASE + IO_BANK0_GPIO24_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(IO_BANK0_BASE + IO_BANK0_GPIO25_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(SIO_BASE + SIO_GPIO_OE_SET_OFFSET) = 1<<PIN25;

    REG(IO_BANK0_BASE + IO_BANK0_PROC0_INTE3_OFFSET) = IO_BANK0_PROC0_INTE3_GPIO24_EDGE_HIGH_BITS;

    REG(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET) = 1<<IO_IRQ_BANK0_IRQn;

    REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN25;

    REG(PADS_BANK0_BASE + PADS_BANK0_GPIO24_OFFSET) = PADS_BANK0_GPIO0_IE_BITS | PADS_BANK0_GPIO0_PUE_BITS | PADS_BANK0_GPIO0_SCHMITT_BITS;

    for(;;){
        __asm__ volatile("wfi");
        REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN25;
    }
}
