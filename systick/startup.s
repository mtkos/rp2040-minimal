.set SysTicK_IRQn, 15
.section .init

.word _estack
.word prog
.skip 4*(SysTicK_IRQn - 2)
.word SysTick_Handler
