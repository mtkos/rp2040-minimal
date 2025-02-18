#include <stdint.h>

#include "../include/common.h"
#include "../include/resets.h"
#include "../include/sio.h"
#include "../include/io_bank0.h"
#include "../include/m0plus.h"

#define IO_IRQ_BANK0_IRQn 13

#define PIN0 0
#define PIN1 1

void IO_IRQ_BANK0_Handler() __attribute__((interrupt));

void IO_IRQ_BANK0_Handler(){

    REG(IO_BANK0_BASE + IO_BANK0_INTR0_OFFSET) = IO_BANK0_INTR0_GPIO1_EDGE_HIGH_BITS;
}

void prog(){

    REG(RESETS_BASE + RESETS_RESET_OFFSET + REG_ALIAS_CLR_BITS) = RESETS_RESET_IO_BANK0_BITS;
    while((~(REG(RESETS_BASE + RESETS_RESET_DONE_OFFSET)) & RESETS_RESET_DONE_IO_BANK0_BITS));

    REG(IO_BANK0_BASE + IO_BANK0_GPIO0_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(IO_BANK0_BASE + IO_BANK0_GPIO1_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(SIO_BASE + SIO_GPIO_OE_SET_OFFSET) = 1<<PIN0;

    REG(IO_BANK0_BASE + IO_BANK0_PROC0_INTE0_OFFSET) = IO_BANK0_PROC0_INTE0_GPIO1_EDGE_HIGH_BITS;

    REG(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET) = 1<<IO_IRQ_BANK0_IRQn;

    for(;;){
        __asm__ volatile("wfi");
        REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN0;
    }
}
