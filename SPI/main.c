#include "clock.h"
#include "gpio_spi.h"



int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
init_spi();
	unsigned char data[]="lhtan_spi";
	while (1)
	{
	send_spi_byte(data,sizeof(data));
	delay_ms(1000);


	}
}

