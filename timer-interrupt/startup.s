.set PWM_IRQ_WRAP_IRQn, 20
.section .init

.word _estack
.word prog
.skip 4*(PWM_IRQ_WRAP_IRQn - 2)
.word PWM_IRQ_WRAP_Handler
