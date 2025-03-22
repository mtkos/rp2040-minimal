#include <stdint.h>

#include "../include/common.h"
#include "../include/resets.h"
#include "../include/sio.h"
#include "../include/io_bank0.h"
#include "../include/m0plus.h"

#define PIN0 0
#define PIN1 1

extern uint32_t _estack1;

void blink(){

    if(REG(SIO_BASE + SIO_CPUID_OFFSET) == 0)
        for(;;){
            REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN0;
            for(uint32_t i = 100000; i; i--);
        }
    else
        for(;;){
            REG(SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET) = 1<<PIN1;
            for(uint32_t i = 320000; i; i--);
        }
}

void prog(){

    REG(RESETS_BASE + RESETS_RESET_OFFSET + REG_ALIAS_CLR_BITS) = RESETS_RESET_IO_BANK0_BITS;
    while((~(REG(RESETS_BASE + RESETS_RESET_DONE_OFFSET)) & RESETS_RESET_DONE_IO_BANK0_BITS));

    REG(IO_BANK0_BASE + IO_BANK0_GPIO0_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(IO_BANK0_BASE + IO_BANK0_GPIO1_CTRL_OFFSET) = GPIO_FUNC_SIO;
    REG(SIO_BASE + SIO_GPIO_OE_SET_OFFSET) = 1<<PIN0 | 1<<PIN1;

    uint32_t cmd_sequence[] = {0, 0, 1, 0, (uint32_t) &_estack1, (uint32_t) blink};
    cmd_sequence[3] = REG(PPB_BASE + M0PLUS_VTOR_OFFSET);

    uint32_t seq = 0;
    while(seq < sizeof(cmd_sequence)/sizeof(cmd_sequence[0])){
        uint32_t cmd = cmd_sequence[seq];
        if(!cmd){
            while(REG(SIO_BASE + SIO_FIFO_ST_OFFSET) & SIO_FIFO_ST_VLD_BITS)
                (void) REG(SIO_BASE + SIO_FIFO_RD_OFFSET);
            __asm__ volatile("sev");
        }

        while(!(REG(SIO_BASE + SIO_FIFO_ST_OFFSET) & SIO_FIFO_ST_RDY_BITS));
        REG(SIO_BASE + SIO_FIFO_WR_OFFSET) = cmd;
        __asm__ volatile("sev");

        while(!(REG(SIO_BASE + SIO_FIFO_ST_OFFSET) & SIO_FIFO_ST_VLD_BITS));
        uint32_t response = REG(SIO_BASE + SIO_FIFO_RD_OFFSET);

        seq = cmd == response ? seq + 1 : 0;
    }
    blink();
}
