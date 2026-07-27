#ifndef __delay_h__
#define __delay_h__
#include <stdint.h>
#include <stddef.h>
void main1 (void);
void SystemClock_Config(void);
int delay (  uint32_t,uint32_t);
#define GPIO_C *((volatile uint32_t*) 0x40020818u)//bsrrgpioc
#define LED_PC13_ALIAS *((volatile uint32_t*) 0x424102B4u)
uint32_t* swap (uint32_t* x, uint32_t* y);void white (void);
void blue (void);
void green (void);
void yellow (void);
void red (void);
void context_switch(void);

void SysTick_Handler(void);
void rtos_yield(void);
#define mx_thread 6
#define stack_size 80

typedef struct {
    uint32_t *sp;                    // First member (Offset 0)
    uint32_t timer;                  // Second member (Offset 4)
    uint32_t mem_alloc[stack_size];  // Last member (Offset 8)
} OS_boy;

// Thread array storage
/* In delay.h - Declarations only */
extern OS_boy Array[mx_thread];
extern OS_boy *arr[mx_thread];
extern OS_boy *curr;
extern OS_boy *prev;
extern volatile uint32_t SYS_i;
extern volatile uint32_t ready_reg[1];

void PendSV_Handler(void); void idle_thread(void); /* Checks, sets, or resets thread ready states using binary commands */
int ready_flag(int index, int state);

/* Automatically initializes a task's stack at the next available index */
void pseudo_stack(int *ptr);

/* Decerements active thread delay timers */
void SYS_ticks(void);

/* Runs round-robin selection and triggers the PendSV context switch */
void SYS_prep(void);

/* Non-blocking delay function to sleep a thread for a set number of ticks */
void rtos_delay(uint32_t ticks);



#endif
