#ifndef RTC_H
#include "stm32f4xx.h"                  // Device header


void RTC_Init(unsigned char h,unsigned char m,unsigned char s,
							unsigned char day,unsigned char month,unsigned char year);

void RTC_get_time (void);
void RTC_get_date(void);
#endif