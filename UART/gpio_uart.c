#include "gpio_uart.h"
#include "clock.h"


void send_uart_GPIO(char * string){
	/*baud 50
		8 bit
		1 bit stop
		LSB first
		TX = D7
	*/

	char *data = string;
	int idx;
	char byte;
	while(*data)
	{
		
		byte=*data;
		data++;		
		GPIOD->ODR |= GPIO_ODR_ODR_7;
		delay_us(20000);
		
		GPIOD->ODR &= ~GPIO_ODR_ODR_7;
		delay_us(20000);
		for(idx = 0;idx<8;idx++)
		{
			if( byte & (1<<idx) ) 
			{
				GPIOD->ODR |= GPIO_ODR_ODR_7;
				delay_us(20000);
			}
			else{
				GPIOD->ODR &= ~GPIO_ODR_ODR_7;
				delay_us(20000);
			}
		}
		GPIOD->ODR |= GPIO_ODR_ODR_7;
		delay_us(20000);
		
	}

}
char read_uart_GPIO(){
		/*baud 50
		8 bit
		1 bit stop
		LSB first
		RX = A0
	*/
	int idx;
	char data;
	char flag;
	flag = 0;
	while(flag==0)
	{
		data = 0x0;
	//start bit
	while( GPIOA->IDR & 1<<0)
	{
		GPIOD->ODR |= GPIO_ODR_ODR_13;
	}
	GPIOD->ODR &=~ GPIO_ODR_ODR_13;
	delay_us((int)1666/2);
	//8 data bit
	
	for(idx = 0;idx<8;idx++)
	{
		delay_us(1666);
		if (GPIOA->IDR & 1<<0)
		{
			data |= 1<<idx;
		}
	}
	delay_us(1666);
	if (GPIOA->IDR & 1<<0)
	{
		flag = 1;
	}
}
	return data;
}
