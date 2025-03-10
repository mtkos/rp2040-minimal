#define IO_BANK0_BASE 0x40014000
#define   IO_BANK0_GPIO0_CTRL_OFFSET 0x4 + 0*0x8
#define   IO_BANK0_GPIO1_CTRL_OFFSET 0x4 + 1*0x8
#define   IO_BANK0_GPIO2_CTRL_OFFSET 0x4 + 2*0x8
#define   IO_BANK0_GPIO8_CTRL_OFFSET 0x4 + 8*0x8
#define   IO_BANK0_GPIO9_CTRL_OFFSET 0x4 + 9*0x8
#define   IO_BANK0_GPIO15_CTRL_OFFSET 0x4 + 15*0x8
#define   IO_BANK0_GPIO16_CTRL_OFFSET 0x4 + 16*0x8
#define   IO_BANK0_GPIO17_CTRL_OFFSET 0x4 + 17*0x8
#define     GPIO_FUNC_UART 2
#define     GPIO_FUNC_PWM 4
#define     GPIO_FUNC_SIO 5
#define     GPIO_FUNC_PIO0 6
#define   IO_BANK0_INTR0_OFFSET 0xf0
#define     IO_BANK0_INTR0_GPIO1_EDGE_HIGH_BITS 1<<7
#define   IO_BANK0_PROC0_INTE0_OFFSET 0x100
#define     IO_BANK0_PROC0_INTE0_GPIO1_EDGE_HIGH_BITS 1<<7
