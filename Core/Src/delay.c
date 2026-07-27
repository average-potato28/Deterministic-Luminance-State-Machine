#include "delay.h"
#include <stdint.h>
#include "stm32f4xx.h"
#include "cmsis_compiler.h"
void SystemClock_Config(void);
extern  int volatile bright[2];
extern uint32_t utick;
 int delay ( uint32_t itr, uint32_t last ){
	if (utick-last >itr)
		return 1;
	else
		return 0;
}




