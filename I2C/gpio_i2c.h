#ifndef GPIO_I2C_H
#define GPIO_I2C_H
#include "stm32f4xx.h"
#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup

#define SDA_ON GPIOD->ODR |= GPIO_ODR_ODR_0;
#define SDA_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_0;
#define SCL_ON GPIOD->ODR |= GPIO_ODR_ODR_1;
#define SCL_OFF GPIOD->ODR &=~ GPIO_ODR_ODR_1;

#define SDA_CONFIG_INPUT GPIOD->MODER &=~ GPIO_MODER_MODE0;
#define SDA_CONFIG_OUTPUT GPIOD->MODER |= GPIO_MODER_MODER0_0;

#define SDA_ON_B9 GPIOB->ODR |= GPIO_ODR_ODR_9;
#define SDA_OFF_B9 GPIOB->ODR &=~ GPIO_ODR_ODR_9;
#define SCL_ON_B6 GPIOB->ODR |= GPIO_ODR_ODR_6;
#define SCL_OFF_B6 GPIOB->ODR &=~ GPIO_ODR_ODR_6;

#define SDA_B9_CONFIG_INPUT GPIOB->MODER &=~ GPIO_MODER_MODE9;
#define SDA_B9_CONFIG_OUTPUT GPIOB->MODER |= GPIO_MODER_MODER9_0;


void send_i2c_string(unsigned char * data,unsigned char add);
void init_i2c();
void send_i2c_byte(unsigned char * data,unsigned char size,unsigned char add);

void lcd_init (void);   // initialize lcd

void lcd_send_cmd (char cmd);  // send command to the lcd

void lcd_send_data (char data);  // send data to the lcd

void lcd_send_string (char *str);  // send string to the lcd

void lcd_clear_display (void);	//clear display lcd

void lcd_goto_XY (int row, int col); //set proper location on screen


void init_i2c_LSM303DLHC();

void send_i2c_byte_LSM303DLHC(unsigned char * data,unsigned char size,unsigned char add);

#endif
