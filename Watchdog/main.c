#include "clock.h"




int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();

	unsigned char data[]="lhtan_spi";

	
	
	IWDG->KR = 0x5555;
	while(IWDG->SR & IWDG_SR_PVU);
	IWDG->PR = 0b111;
	while(IWDG->SR & IWDG_SR_RVU);
	IWDG->RLR = 125 * 7; //<4095
	IWDG->KR = 0xaaaa;
	IWDG->KR = 0xcccc;
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

