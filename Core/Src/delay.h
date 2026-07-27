#ifndef __delay_h__
#define __delay_h__
#include <stdint.h>
#include <stddef.h>

void SystemClock_Config(void);
int delay (  uint32_t,uint32_t);

uint32_t* swap (uint32_t* x, uint32_t* y);void white (void);


void SysTick_Handler(void);






#endif
