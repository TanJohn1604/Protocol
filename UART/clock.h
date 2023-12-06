#ifndef CLOCK_H
#define CLOCK_H
#include "stm32f4xx.h"

void SysClockConfig (void);
void GPIO_Config (void);
void TIM2_Config (void);

void delay_us(int us );

void delay_ms(int ms);
#endif