#include "gpio_i2c.h"
#include "clock.h"

void init_i2c()
{
//5. set i2c port
//D0 - SDA
//D1 - CLK
//5.1 Set the Pin as OUTPUT
GPIOD->MODER |= GPIO_MODER_MODER0_0;	
GPIOD->MODER |= GPIO_MODER_MODER1_0;	
//5.2 open drain
GPIOD->OTYPER |= GPIO_OTYPER_OT0;
GPIOD->OTYPER |= GPIO_OTYPER_OT1;
//5.3 pull up resitor
GPIOD->PUPDR |=GPIO_PUPDR_PUPD0_0;
GPIOD->PUPDR &=~ GPIO_PUPDR_PUPD0_1;	
GPIOD->PUPDR |=GPIO_PUPDR_PUPD1_0;
GPIOD->PUPDR &=~ GPIO_PUPDR_PUPD1_1;
}


void send_i2c(unsigned char * data,unsigned char add)
{
unsigned char byte_temp;
	
SDA_OFF
delay_ms(10);
SCL_OFF
delay_ms(10);

//address + r/w
for (int i=7;i>=0;i--)
{
if(add & 1<<i)
{
	SDA_ON
}
else
{
	SDA_OFF
}
delay_ms(10);
SCL_ON
delay_ms(20);
SCL_OFF
delay_ms(10);
}
//address + r/w

//clock for ack
SDA_OFF //simulate ack
delay_ms(10);
SCL_ON
delay_ms(20);
SCL_OFF
delay_ms(10);
//clock for ack

// data
while(*data)
{
byte_temp =*data;
data ++;
for (int i=7;i>=0;i--)
{
if(byte_temp & 1<<i)
{
	SDA_ON
}
else
{
	SDA_OFF
}
delay_ms(10);
SCL_ON
delay_ms(20);
SCL_OFF
delay_ms(10);
}

//clock for ack
SDA_OFF //simulate ack
delay_ms(10);
SCL_ON
delay_ms(20);
SCL_OFF
delay_ms(10);
//clock for ack
}

//data



//stop bit
SDA_OFF
delay_ms(10);
SCL_ON
delay_ms(10);
SDA_ON
delay_ms(40);
		
}
