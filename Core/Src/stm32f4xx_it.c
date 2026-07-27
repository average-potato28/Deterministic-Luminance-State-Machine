/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim11;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */



__attribute__((naked)) void HardFault_Handler(void) {
    __asm volatile (
        "tst lr, #4            \n" // Check EXC_RETURN bit 2 (0 = MSP, 1 = PSP used before fault)
        "ite eq                \n"
        "mrseq r0, msp         \n" // If bit 2 is 0, MSP was the active stack pointer
        "mrsne r0, psp         \n" // If bit 2 is 1, PSP was the active stack pointer
        "mov r1, lr            \n" // Pass EXC_RETURN value in R1
        "b hard_fault_handler_c\n" // Branch to the C-level decoder
    );
}

/**
 * @brief C-level crash decoder.
 * Extracts registers at the time of the fault and queries System Control Block registers.
 * 'volatile' prevents the compiler from optimizing out local variables during debug.
 */
#include <stdio.h>
#include <string.h>
#include "usart.h"
void hard_fault_handler_c(uint32_t *stack_pointer);
void hard_fault_handler_c(uint32_t *stack_pointer) {
unsigned int pc = stack_pointer[6];
unsigned int lr = stack_pointer[5];
unsigned int xpsr = stack_pointer[7];
unsigned int r0 = stack_pointer[0];
unsigned int r1 = stack_pointer[1];
unsigned int r2 = stack_pointer[2];
unsigned int r3 = stack_pointer[3];
unsigned int r12 = stack_pointer[4];
unsigned int lr_val = stack_pointer[8];

unsigned int cfsr = SCB->CFSR;
unsigned int hfsr = SCB->HFSR;
unsigned int bfar = SCB->BFAR;
unsigned int mmfar = SCB->MMFAR;

// FIX 1: Increased buffer size from 128 to 256 to prevent truncation
char buffer[256];

// FIX 2: Changed all %LX to %lX
int len = snprintf(buffer, sizeof(buffer),
         "\r\n=== CRASH DETECTED ===\r\n"
         "PC   : 0x%08lX\r\nLR   : 0x%08lX\r\nxPSR : 0x%08lX\r\n"
         "R0   : 0x%08lX\r\nR1   : 0x%08lX\r\nR2   : 0x%08lX\r\nR3   : 0x%08lX\r\n"
         "R12  : 0x%08lX\r\nSP   : 0x%08lX\r\nEXC_R: 0x%08lX\r\n",
         pc, lr, xpsr, r0, r1, r2, r3, r12, (uint32_t)stack_pointer, lr_val);

// Transmit first block via UART (assuming huart2 or whichever handle you use)
// HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, HAL_MAX_DELAY);

len = snprintf(buffer, sizeof(buffer),
         "CFSR : 0x%08lX\r\nHFSR : 0x%08lX\r\nBFAR : 0x%08lX\r\nMMFAR: 0x%08lX\r\n",
         cfsr, hfsr, bfar, mmfar);

// Transmit second block
// HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, HAL_MAX_DELAY);

while(1) {
    // Hang on crash
}
}
/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */


/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */

/**
  * @brief This function handles System tick timer.
  */

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM1 trigger and commutation interrupts and TIM11 global interrupt.
  */
void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 0 */

  /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 0 */
  HAL_TIM_IRQHandler(&htim11);
  /* USER CODE BEGIN TIM1_TRG_COM_TIM11_IRQn 1 */

  /* USER CODE END TIM1_TRG_COM_TIM11_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
