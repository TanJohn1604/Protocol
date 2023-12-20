#include "gpio_spi.h"
#include "clock.h"



void send_2_byte(unsigned char add,unsigned char da)
{
unsigned char byte_temp;
EN_ON
unsigned char data[2];
	data[0] = add;
	data[1] = da;
// data MOSI
for(int i=0;i<2;i++)
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


///////////NOT COMPLETED///////////////////
//reset
send_2_byte(CommandReg,PCD_SoftReset);
delay_ms(1000);

// Reset baud rates
send_2_byte(TxModeReg,0x00);
send_2_byte(RxModeReg,0x00);
// Reset ModWidthReg
send_2_byte(ModWidthReg,0x26);



// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
send_2_byte(TModeReg,0x80);
// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25µs.
send_2_byte(TPrescalerReg,0xA9);


// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
send_2_byte(TReloadRegH,0x03);



send_2_byte(TReloadRegL, 0xE8);

send_2_byte(TxASKReg, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
send_2_byte(ModeReg, 0x3D);

//antena on but clear orthe bit
send_2_byte(TxControlReg,  0x03);
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




