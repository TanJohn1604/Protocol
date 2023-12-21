#ifndef WATCH_DOG_H
#define WATCH_DOG_H
#include "stm32f4xx.h"


void init_watchdog(unsigned char second);
void start_watchdog();
	void stop_watchdog();
#endif
