#include "gpio_i2c.h"
#include "clock.h"





void init_i2c()
{

//5. set i2c port
//1 bit = 3ms => speed = 333bit/s
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


void send_i2c_string(unsigned char * data,unsigned char add)
{
unsigned char byte_temp;
	
SDA_OFF
delay_ms(1);
SCL_OFF
delay_ms(1);

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
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
}
//address + r/w

//clock for ack
SDA_ON
//read ACK, wait for ACK
SDA_CONFIG_INPUT
while(GPIOD->IDR & (1<<0));
SDA_CONFIG_OUTPUT
//read ACK, wait for ACK
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
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
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
}

//clock for ack
SDA_ON
//read ACK, wait for ACK
SDA_CONFIG_INPUT
while(GPIOD->IDR & (1<<0));
SDA_CONFIG_OUTPUT
//read ACK, wait for ACK
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
//clock for ack
}

//data



//stop bit
SDA_OFF
delay_ms(1);
SCL_ON
delay_ms(1);
SDA_ON
delay_ms(4);
		
}


void send_i2c_byte(unsigned char * data,unsigned char size,unsigned char add)
{
unsigned char byte_temp;
	
SDA_OFF
delay_ms(1);
SCL_OFF
delay_ms(1);

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
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
}
//address + r/w

//clock for ack
SDA_ON
//read ACK, wait for ACK
SDA_CONFIG_INPUT
while(GPIOD->IDR & (1<<0));
SDA_CONFIG_OUTPUT
//read ACK, wait for ACK
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
//clock for ack

// data
for(int i=0;i<size;i++)
{
byte_temp =data[i];

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
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
}

//clock for ack
SDA_ON
//read ACK, wait for ACK
SDA_CONFIG_INPUT
while(GPIOD->IDR & (1<<0));
SDA_CONFIG_OUTPUT
//read ACK, wait for ACK
delay_ms(1);
SCL_ON
delay_ms (1);
SCL_OFF
delay_ms(1);
//clock for ack
}
//data

//stop bit
SDA_OFF
delay_ms(1);
SCL_ON
delay_ms(1);
SDA_ON
delay_ms(4);
		
}








void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0

send_i2c_byte_LSM303DLHC(data_t,sizeof(data_t),SLAVE_ADDRESS_LCD);

}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0

send_i2c_byte_LSM303DLHC(data_t,sizeof(data_t),SLAVE_ADDRESS_LCD);
}

void lcd_init (void)
{
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	delay_ms(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	delay_ms(50);
	lcd_send_cmd (0x01); /* clear display */
	delay_ms(50);
	lcd_send_cmd (0x06); /* set entry mode */
	delay_ms(50);
	lcd_send_cmd (0x0c); /* set display to on */
	delay_ms(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	delay_ms(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 1)
	{
		pos_Addr = 0x80 + row - 1 + col;
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	lcd_send_cmd(pos_Addr);
}



void init_i2c_LSM303DLHC()
{

//5. set i2c port
//1 bit = 3ms => speed = 333bit/s
//B9 - SDA
//B6 - CLK
//5.1 Set the Pin as OUTPUT
//enable port B

	
GPIOB->MODER |= GPIO_MODER_MODER6_0;	
GPIOB->MODER |= GPIO_MODER_MODER9_0;	
//5.2 open drain
GPIOB->OTYPER |= GPIO_OTYPER_OT6;
GPIOB->OTYPER |= GPIO_OTYPER_OT9;
//5.3 pull up resitor
GPIOB->PUPDR |=GPIO_PUPDR_PUPD6_0;
GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD6_1;	
GPIOB->PUPDR |=GPIO_PUPDR_PUPD9_0;
GPIOB->PUPDR &=~ GPIO_PUPDR_PUPD9_1;
}


void send_i2c_byte_LSM303DLHC(unsigned char * data,unsigned char size,unsigned char add)
{
unsigned int timeout=0;
unsigned char byte_temp;
	delay_ms(1);
SDA_OFF_B9
delay_ms(1);
SCL_OFF_B6
delay_ms(1);

//address + r/w
for (int i=7;i>=0;i--)
{
if(add & 1<<i)
{
	SDA_ON_B9
}
else
{
	SDA_OFF_B9
}
delay_ms(1);
SCL_ON_B6
delay_ms (1);
SCL_OFF_B6
delay_ms(1);
}
//address + r/w

//clock for ack
SDA_ON_B9
//read ACK, wait for ACK
//SDA_B9_CONFIG_INPUT
//while(GPIOB->IDR & (1<<9));
//SDA_B9_CONFIG_OUTPUT

SDA_B9_CONFIG_INPUT
while(GPIOB->IDR & (1<<9))
{
	timeout++;
	if (timeout>1000000)
	{
		SDA_B9_CONFIG_OUTPUT
		SDA_ON_B9
		SCL_ON_B6
		return;
	}
}
SDA_B9_CONFIG_OUTPUT

//read ACK, wait for ACK
delay_ms(1);
SCL_ON_B6
delay_ms (1);
SCL_OFF_B6
delay_ms(1);
//clock for ack

// data
for(int i=0;i<size;i++)
{
byte_temp =data[i];

for (int i=7;i>=0;i--)
{
if(byte_temp & 1<<i)
{
	SDA_ON_B9
}
else
{
	SDA_OFF_B9
}
delay_ms(1);
SCL_ON_B6
delay_ms (1);
SCL_OFF_B6
delay_ms(1);
}

//clock for ack
SDA_ON_B9
//read ACK, wait for ACK
SDA_B9_CONFIG_INPUT
while(GPIOB->IDR & (1<<9))
{
	timeout++;
	if (timeout>1000000)
	{
		SDA_B9_CONFIG_OUTPUT
		SDA_ON_B9
		SCL_ON_B6
		return;
	}
}
SDA_B9_CONFIG_OUTPUT
//read ACK, wait for ACK
delay_ms(1);
SCL_ON_B6
delay_ms (1);
SCL_OFF_B6
delay_ms(1);
//clock for ack
}
//data

//stop bit
SDA_OFF_B9
delay_ms(1);
SCL_ON_B6
delay_ms(1);
SDA_ON_B9
delay_ms(10);
	
}




