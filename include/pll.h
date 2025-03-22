#define PLL_SYS_BASE 0x40028000
#define   PLL_CS_OFFSET 0x0
#define     PLL_CS_LOCK_BITS 1<<31
#define   PLL_PWR_OFFSET 0x4
#define     PD 1<<0
#define     VCOPD 1<<5
#define     PLL_PWR_POSTDIVPD_LSB 3
#define     PLL_PWR_POSTDIVPD_BITS 1<<3
#define     PLL_PWR_PD_BITS 1<<0
#define     PLL_PWR_VCOPD_BITS 1<<5
#define   PLL_FBDIV_INT_OFFSET 0x8
#define   PLL_PRIM_OFFSET 0xc
#define     PLL_PRIM_POSTDIV1_LSB 16
#define     PLL_PRIM_POSTDIV2_LSB 12

