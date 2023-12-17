#include "clock.h"
#include "interrupt.h"
#include "gpio_i2c.h"



int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
	init_i2c();
	init_i2c_LSM303DLHC();
  lcd_init ();   // initialize lcd
		delay_ms(1000);
	unsigned char a[]="lhtan";
	while (1)
	{
	lcd_send_string("A");
//		GPIOD->ODR |= GPIO_ODR_ODR_12;
//	delay_ms(1000);
		GPIOD->ODR &=~ GPIO_ODR_ODR_12;
	lcd_clear_display();
	delay_ms(1000);
//		SDA_B9_CONFIG_INPUT
//		delay_ms(250);
//		SDA_B9_CONFIG_OUTPUT
//			delay_ms(250);
//		send_i2c_byte_LSM303DLHC(a,6,SLAVE_ADDRESS_LCD);
//		SDA_ON_B9
//		SCL_ON_B6
//			delay_ms(40);
//				SDA_OFF_B9
//		SCL_OFF_B6
//			delay_ms(40);

	}
}

