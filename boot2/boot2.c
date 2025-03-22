#include <stdint.h>
#include <stdbool.h>

#include "../include/common.h"
#include "../include/ssi.h"
#include "../include/m0plus.h"
#include "../include/xip.h"

#define CMD_READ_DATA 0x3
#define ADDRESS_BITS 24
#define DATA_FRAME_SIZE 32

__attribute__((section (".boot2"))) void boot2(){

    REG(XIP_SSI_BASE + SSI_SSIENR_OFFSET) = 0;

    REG(XIP_SSI_BASE + SSI_CTRLR0_OFFSET) = (SSI_CTRLR0_TMOD_VALUE_EEPROM_READ << SSI_CTRLR0_TMOD_LSB) | ((DATA_FRAME_SIZE - 1) << SSI_CTRLR0_DFS_32_LSB);
    REG(XIP_SSI_BASE + SSI_BAUDR_OFFSET) = 4;
    REG(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET) = ((ADDRESS_BITS/4) << SSI_SPI_CTRLR0_ADDR_L_LSB) | (SSI_SPI_CTRLR0_INST_L_VALUE_8B << SSI_SPI_CTRLR0_INST_L_LSB) | \
                                                (CMD_READ_DATA << SSI_SPI_CTRLR0_XIP_CMD_LSB);

    REG(XIP_SSI_BASE + SSI_SSIENR_OFFSET) = 1;

    REG(PPB_BASE + M0PLUS_VTOR_OFFSET) = XIP_BASE + 0x100;

    __asm__ volatile(
                     ".set XIP_BASE, 0x10000000\n" \
                     "ldr r0, =(XIP_BASE + 0x100)\n" \
//load data from first two entries of vector table:
                     "ldmia r0, {r0, r1}\n" \
//set stack pointer
                     "msr msp, r0\n" \
//branch to reset handler / main program
                     "bx r1\n"
    );
}
