#ifndef CLOCK_H
#define CLOCK_H
#include "stm32f4xx.h"

void SysClockConfig (void);
void GPIO_Config (void);
void TIM2_Config (void);

void delay_us(unsigned int us );

void delay_ms(unsigned int ms);
#endif
