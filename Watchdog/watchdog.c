#include "watchdog.h"


void init_watchdog(unsigned char second)
{
IWDG->KR = 0x5555;
while(IWDG->SR & IWDG_SR_PVU);
IWDG->PR = 0b111;
while(IWDG->SR & IWDG_SR_RVU);
IWDG->RLR = 125 * second; //<4095
IWDG->KR = 0xaaaa;

}

void start_watchdog()
{
	IWDG->KR = 0xcccc;
}
void stop_watchdog()
{
	IWDG->KR = 0xaaaa;
}
