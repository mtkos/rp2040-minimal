#include <stdint.h>

#include "../include/common.h"
#include "../include/resets.h"
#include "../include/io_bank0.h"
#include "../include/pwm.h"

#define A_DUTY 0x2000 //0.125 duty
#define B_DUTY 0x8000 //0.5 duty
#define CPU_FREQ 6500000
#define DIVIDER CPU_FREQ/0x10000 //to get ~1Hz pulses
#define CH0 0

void prog(){

    REG(RESETS_BASE + RESETS_RESET_OFFSET + REG_ALIAS_CLR_BITS) = RESETS_RESET_IO_BANK0_BITS | RESETS_RESET_PWM_BITS;
    while((~(REG(RESETS_BASE + RESETS_RESET_DONE_OFFSET)) & (RESETS_RESET_DONE_IO_BANK0_BITS | RESETS_RESET_DONE_PWM_BITS)));

    REG(IO_BANK0_BASE + IO_BANK0_GPIO0_CTRL_OFFSET) = GPIO_FUNC_PWM;
    REG(IO_BANK0_BASE + IO_BANK0_GPIO1_CTRL_OFFSET) = GPIO_FUNC_PWM;

    REG(PWM_BASE + PWM_CH0_DIV_OFFSET) = DIVIDER<<PWM_CH0_DIV_INT_LSB;
    REG(PWM_BASE + PWM_CH0_CC_OFFSET) = (B_DUTY<<PWM_CH0_CC_B_LSB) + A_DUTY;
    REG(PWM_BASE + PWM_EN_OFFSET) = 1<<CH0;

    __asm__ volatile("wfi");
}
