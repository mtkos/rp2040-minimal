#include <stdint.h>

#include "../include/common.h"
#include "../include/resets.h"
#include "../include/sio.h"
#include "../include/io_bank0.h"

#define PIN25 25

void prog(){

    REG(RESETS_BASE + RESETS_RESET_OFFSET + REG_ALIAS_CLR_BITS) = RESETS_RESET_IO_BANK0_BITS;
    while((~(REG(RESETS_BASE + RESETS_RESET_DONE_OFFSET)) & RESETS_RESET_DONE_IO_BANK0_BITS));

    REG(IO_BANK0_BASE + IO_BANK0_GPIO25_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(SIO_BASE + SIO_GPIO_OE_SET_OFFSET) = 1<<PIN25;

    for(;;){
        REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN25;
        for(uint32_t i = 100000; i; i--);
    }
}
