#include "clock.h"
#include "rtc.h"


int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();	
RTC_Init(0x23,0x59,0x40,//hh/mm/ss
				0x26,0x12,0x23);//dd/mm/yy
	
int count = 0;

	while (1)
	{	
		RTC_get_date();
		RTC_get_time();
	delay_ms(1000);
	GPIOD->ODR |= (GPIO_ODR_OD12|GPIO_ODR_OD13|GPIO_ODR_OD14|GPIO_ODR_OD15);
	delay_ms(1000);
		GPIOD->ODR &=~ (GPIO_ODR_OD12|GPIO_ODR_OD13|GPIO_ODR_OD14|GPIO_ODR_OD15);

		
	}
	
}

