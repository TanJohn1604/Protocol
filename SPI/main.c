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
send_2_byte(TxControlReg|0x80,0);
delay_ms(1000);
	}
	
}

