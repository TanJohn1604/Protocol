#ifndef GPIO_UART_H
#define GPIO_UART_H
#include "stm32f4xx.h"

char read_uart_GPIO();
void send_uart_GPIO(char * string);
#endif