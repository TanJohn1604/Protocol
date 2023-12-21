#ifndef WATCH_DOG_H
#define WATCH_DOG_H
#include "stm32f4xx.h"


void init_IWDG(unsigned char second);
void start_IWDG();
	void stop_IWDG();
#endif
