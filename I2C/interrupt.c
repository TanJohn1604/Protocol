#include "interrupt.h"

void EXTI0_IRQHandler(void){

GPIOD->ODR &=~ GPIO_ODR_ODR_12;
//xoa bit ngat
EXTI->PR |=1;
}

void init_interrupt_PA0(void){
	//cau hinh ngat cho chan pa0
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
		__disable_irq();
		NVIC_EnableIRQ(EXTI0_IRQn);
		__enable_irq();
}
