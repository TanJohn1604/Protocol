#include "clock.h"
#include "interrupt.h"
#include "gpio_uart.h"


int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
	
	init_interrupt_PA0();
	char a[] = "a\n";
	char b;
GPIOD->ODR |= GPIO_ODR_ODR_12;

delay_ms(1000);
	

	while (1)
	{		

	b= read_uart_GPIO();
	a[0] = b;
	send_uart_GPIO(a);

	}
}


