#ifndef GPIO_I2C_H
#define GPIO_I2C_H
#include "stm32f4xx.h"

#define SDA_ON GPIOD->ODR |= GPIO_ODR_ODR_0;
#define SDA_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_0;
#define SCL_ON GPIOD->ODR |= GPIO_ODR_ODR_1;
#define SCL_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_1;

void send_i2c(unsigned char * data,unsigned char add);
void init_i2c();
#endif
