#include "clock.h"
#include "interrupt.h"
#include "gpio_i2c.h"



int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
	init_i2c();
	
	
	GPIOD->ODR |= GPIO_ODR_ODR_12;
	SDA_ON
	SCL_ON
	unsigned char a[]="I2C@LHTAN";
	unsigned char add;
	add = 0x6F << 1;
	add |= 0;

	while (1)
	{
		send_i2c(a,add);
		delay_ms(1000);
	}
}

