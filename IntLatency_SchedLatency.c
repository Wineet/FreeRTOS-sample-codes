/*
    FreeRTOS V8.0.1 - Copyright (C) 2014 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "basic_io.h"


void vTask1( void *pvParameters );
void vTask2( void *pvParameters );

#define LEDon		LPC_GPIO2->CLR=(1<<9);
#define LEDoff      LPC_GPIO2->SET=(1<<9);
#define LED1on		LPC_GPIO1->CLR=(1<<29);
#define LED1off		LPC_GPIO1->SET=(1<<29);

/*-----------------------------------------------------------*/
volatile static int LED1=0,LED2=0,LED3=0,LED4=0;
volatile int x;

void vSetupTimerForRunTimeStats( void );
volatile unsigned long ultimestamp4 = 0;

int main( void )
{

	LPC_GPIO2->DIR=(1<<9);
	LEDoff;
	LPC_GPIO1->DIR=(1<<29);
	LED1off;
	//Chip_GPIO_SetPinOutHigh(LPC_GPIO2, 2, 9);
	vSetupTimerForRunTimeStats();
	/* Create one of the two tasks. */
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					4,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */

	//xTaskCreate(vTask2,"Task 2",240,NULL,1,NULL);
	/* Start the scheduler so our tasks start executing. */
	//ultimestamp4=LPC_TIMER0->TC;
	//vTaskDelay((portTickType)1000);
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
	//SysTick->VAL;
	return 0;
}
/*-----------------------------------------------------------*/
volatile unsigned long ultimestamp1 = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
volatile unsigned long ultimestamp2 = 0;
volatile unsigned long ultimestamp3 = 0;
//volatile unsigned long ultimestamp4 = 0;
volatile unsigned long ultimestamp6 = 0;
//volatile unsigned long ultimestamp6 = 0;
volatile unsigned long schedlatency=0;
volatile unsigned long intrlatency=0;

//extern volatile unsigned long sched;
extern volatile unsigned long intr;
void vTask1( void *pvParameters )
{
//ultimestamp6=LPC_TIMER0->TC;
//volatile unsigned long ul;
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
				ultimestamp1=LPC_TIMER0->TC;
				LED1++;
				LEDon
				vTaskDelay((TickType_t)1000);
				ultimestamp2=LPC_TIMER0->TC;
				//LED2++;
				LED1--;
				LEDoff;

				vTaskDelay((TickType_t)1000);
				ultimestamp3 =LPC_TIMER0->TC;
				intrlatency=99999-intr;
				//x=ultimestamp8-ultimestamp3;
				//schedlatency=sched-ultimestamp3;

				//schedlatency=sched-ultimestamp3-intrlatency;

	}
}
/*
void vTask2( void *pvParameters )
{
//volatile unsigned long ul;
	//while(1);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	for( ;; )
	{
				x++;
				//ultimestamp4=LPC_TIMER0->TC;
				LED1++;
				LED1on
				vTaskDelay((TickType_t)2000);
				//ultimestamp5=LPC_TIMER0->TC;
				//LED2++;
				LED1--;
				LED1off;
				vTaskDelay((TickType_t)2000);
				//ultimestamp6 =LPC_TIMER0->TC;

	}
}*/
void vSetupTimerForRunTimeStats( void )
{
const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00, TCR_COUNT_ENABLE = 0x01;

	LPC_SYSCON->PCONP|=0x02UL;
	LPC_SYSCON->PCLKSEL[0] = ( LPC_SYSCON->PCLKSEL[0] & (~(0x3<<2)) ) | ( 0x01 << 2 );

	/* Reset Timer 0 */
	LPC_TIMER0->TCR = TCR_COUNT_RESET;

	/* The timer needs to just count up continuously. */
	LPC_TIMER0->CTCR = CTCR_CTM_TIMER;

	LPC_TIMER0->PR =  ( configCPU_CLOCK_HZ / 1000000UL ) - 1UL;

	/* Start the counter. */
	LPC_TIMER0->TCR = TCR_COUNT_ENABLE;
}
/*--------------------------------------------------------*/
/*void vTask2( void *pvParameters )
{
volatile unsigned long ul;

	// As per most tasks, this task is implemented in an infinite loop.
	for( ;; )
	{
		LPC_GPIO2->CLR=(1<<11);
		//Chip_GPIO_SetPinOutLow(LPC_GPIO2,2,9);
		vTaskDelay((TickType_t)2000);
		LPC_GPIO2->SET=(1<<11);
		//Chip_GPIO_SetPinOutHigh(LPC_GPIO2, 2, 9);
		vTaskDelay((TickType_t)1000);
	}

}*/

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}
/*
void spi_init(void)
{
	LPC_IOCON->PINSEL[0]|=(1<<15);
	LPC_IOCON->PINSEL[1]|=(1<<17)|(1<<18);
	LPC_IOCON->PINSEL[4]&= ~((1<<18)|(1<<19));
	LPC_GPIO->DIR|= (1<<16);
	LPC_GPIO->CLR|=(1<<16);
}*/
