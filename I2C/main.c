#include "clock.h"
#include "interrupt.h"
#include "gpio_i2c.h"



int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
	delay_ms(1000);
	init_i2c();
	init_i2c_LSM303DLHC();
  lcd_init ();   // initialize lcd

	unsigned char a[]="lhtan";
	while (1)
	{
	lcd_send_string("lhtan_i2cc");

	GPIOD->ODR &=~ GPIO_ODR_ODR_12;
	lcd_clear_display();
	delay_ms(1000);


	}
}

