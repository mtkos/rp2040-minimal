#include <stdint.h>

#include "../include/common.h"
#include "../include/resets.h"
#include "../include/sio.h"
#include "../include/io_bank0.h"

#define PIN0 0
#define PIN1 1

uint32_t count = 1000;

extern uint32_t _sidata, _sdata, _edata, _ebss, _sbss;

uint32_t period(){

    count += 1000;
    return count;
}

void flash_to_ram(){

    uint32_t *p_idata = &_sidata;

    for(uint32_t *p_data = &_sdata; p_data < &_edata; *p_data++ = *p_idata++);
    for(uint32_t *p_bss = &_sbss; p_bss < &_ebss; *p_bss++ = 0);

}

void prog(){

    flash_to_ram();

    REG(RESETS_BASE + RESETS_RESET_OFFSET + REG_ALIAS_CLR_BITS) = RESETS_RESET_IO_BANK0_BITS;
    while((~(REG(RESETS_BASE + RESETS_RESET_DONE_OFFSET)) & RESETS_RESET_DONE_IO_BANK0_BITS));

    REG(IO_BANK0_BASE + IO_BANK0_GPIO0_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(IO_BANK0_BASE + IO_BANK0_GPIO1_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(SIO_BASE + SIO_GPIO_OE_SET_OFFSET) = 1<<PIN0 | 1<<PIN1;

    REG(SIO_BASE + SIO_GPIO_OUT_OFFSET) = 1<<PIN0;
    for(;;){
        REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN0 | 1<<PIN1;
        for(uint32_t i = period(); i; i--);
    }
}
