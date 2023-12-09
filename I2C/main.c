#include "clock.h"
#include "interrupt.h"

#define SDA_ON GPIOD->ODR |= GPIO_ODR_ODR_0;
#define SDA_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_0;

#define SCL_ON GPIOD->ODR |= GPIO_ODR_ODR_1;
#define SCL_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_1;
void send_i2c(unsigned char * data,unsigned char add);

int main (void)
{

	SysClockConfig ();
	GPIO_Config ();
	TIM2_Config();
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
