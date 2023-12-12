#include "clock.h"
#include "interrupt.h"
#include "gpio_i2c.h"



int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
	init_i2c();
	
  lcd_init ();   // initialize lcd
	while (1)
	{
	lcd_send_string("lhtan_12c");
	delay_ms(250);
	lcd_clear_display();
		
	}
}

