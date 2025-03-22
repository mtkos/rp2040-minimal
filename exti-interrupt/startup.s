.set IO_IRQ_BANK0_IRQn, 29
.section .init

.word _estack
.word prog
.skip 4*(IO_IRQ_BANK0_IRQn - 2)
.word IO_IRQ_BANK0_Handler
