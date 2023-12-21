#include "clock.h"
#include "watchdog.h"

int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();	
init_IWDG(10);
start_IWDG();

int count = 0;

	while (1)
	{	
		if(count<5)
		{
		delay_ms(500);
		count +=1;
		GPIOD->ODR |= (GPIO_ODR_OD12|GPIO_ODR_OD13|GPIO_ODR_OD14|GPIO_ODR_OD15);
		delay_ms(500);
		GPIOD->ODR &=~ (GPIO_ODR_OD12|GPIO_ODR_OD13|GPIO_ODR_OD14|GPIO_ODR_OD15);
		}

		
	}
	
}

