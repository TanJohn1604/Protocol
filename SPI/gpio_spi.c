#include "gpio_spi.h"
#include "clock.h"




void init_spi()
{

//5. set spi port
//
//D0 - MOSI
//D1 - MISO
//D2 - CLOCK
//D3 - EN 
//5.1 Set the Pin as OUTPUT	
GPIOD->MODER |= GPIO_MODER_MODER0_0;	
GPIOD->MODER |= GPIO_MODER_MODER2_0;	
GPIOD->MODER |= GPIO_MODER_MODER3_0;	
	
GPIOD->MODER &=~ GPIO_MODER_MODER1;	
	
//5.2 push pull
GPIOD->OTYPER &=~ GPIO_OTYPER_OT0;
GPIOD->OTYPER &=~ GPIO_OTYPER_OT2;
GPIOD->OTYPER &=~ GPIO_OTYPER_OT3;


//5.3 pull up resitor for MISO input port
GPIOD->PUPDR |= GPIO_PUPDR_PUPD1_0;
GPIOD->PUPDR &=~ GPIO_PUPDR_PUPD1_1;

MOSI_OFF
CLOCK_OFF
}


void send_spi_byte(unsigned char * data,unsigned char size)
{
unsigned char byte_temp;
EN_ON

// data MOSI
for(int i=0;i<size;i++)
{
byte_temp =data[i];

for (int i=7;i>=0;i--)
{

if(byte_temp & 1<<i)
{
	MOSI_ON
}
else
{
	MOSI_OFF
}

delay_ms(10);
CLOCK_ON
delay_ms(10);
CLOCK_OFF
}


}
//data MOSI


EN_OFF
}




