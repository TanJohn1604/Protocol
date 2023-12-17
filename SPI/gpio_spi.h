#ifndef GPIO_SPI_H
#define GPIO_SPI_H
#include "stm32f4xx.h"


#define MOSI_ON GPIOD->ODR |= GPIO_ODR_ODR_0;
#define MOSI_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_0;

#define MISO_STATUS GPIOD->IDR & (1<<1) 

#define CLOCK_ON GPIOD->ODR |= GPIO_ODR_ODR_2;
#define CLOCK_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_2;

#define EN_ON GPIOD->ODR &=~ GPIO_ODR_ODR_3;
#define EN_OFF GPIOD->ODR |= GPIO_ODR_ODR_3;



void init_spi();
void send_spi_byte(unsigned char * data,unsigned char size);


#endif
