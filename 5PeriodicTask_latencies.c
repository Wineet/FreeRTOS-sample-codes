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

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3( void *pvParameters );
void vTask4( void *pvParameters );
void vTask5( void *pvParameters );
void vSetupTimerForRunTimeStats( void );

volatile unsigned int x = 0;
volatile unsigned int y = 0;
volatile unsigned int z = 0;
volatile unsigned int a = 0;
volatile unsigned int b = 0;
/*-----------------------------------------------------------*/

volatile unsigned long timestamp_intt_latency = 0;
unsigned long ultimestamp1 = 99999;
unsigned long ultimestamp2 = 0;
unsigned long ultimestamp3 = 0;
unsigned long ultimestamp4 = 0;
unsigned long ultimestamp5 = 0;
unsigned long ultimestamp6 = 0;

int main( void )
{
	/* Init the semi-hosting. */
	vSetupTimerForRunTimeStats();
	/* Create one of the two tasks. */
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask2, "Task 2", 240, NULL, 1, NULL );
	xTaskCreate( vTask3, "Task 3", 240, NULL, 1, NULL );
	xTaskCreate( vTask4, "Task 4", 240, NULL, 1, NULL );
	xTaskCreate( vTask5, "Task 5", 240, NULL, 1, NULL );


	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/

void vTask1( void *pvParameters )
{
	vTaskDelay(1);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */

	for( ;; )
	{

		vTaskDelayUntil( &xLastWakeTime, (portTickType)1 );
		ultimestamp2 = SysTick->VAL;
		++a;
	}
}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
	vTaskDelay(2);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */

	for( ;; )
	{

		vTaskDelayUntil( &xLastWakeTime, (portTickType)2 );
		ultimestamp3 = SysTick->VAL;
		++b;
	}
}
/*-----------------------------------------------------------*/
void vTask3( void *pvParameters )
{
	vTaskDelay(3);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */

	for( ;; )
	{

		vTaskDelayUntil( &xLastWakeTime, (portTickType)3 );
		ultimestamp4 = SysTick->VAL;
		++x;
	}
}

void vTask4( void *pvParameters )
{
	vTaskDelay(4);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */

	for( ;; )
	{


		vTaskDelayUntil( &xLastWakeTime,(portTickType)4 );
		ultimestamp5 = SysTick->VAL;
		++y;
	}
}

void vTask5( void *pvParameters )
{

	vTaskDelay(5);
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */

	for( ;; )
	{

		vTaskDelayUntil( &xLastWakeTime, (portTickType)5 );
		ultimestamp6 = SysTick->VAL;
		++z;
	}
}
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

void vSetupTimerForRunTimeStats( void )
{
const unsigned long TCR_COUNT_RESET = 0x02;
const unsigned long	CTCR_CTM_TIMER = 0x00;
const unsigned long	TCR_COUNT_ENABLE = 0x01;

	/* Power up and drive the timer 0. */
//
//
//lecture - refer to chapter 4 of lpc17xx user-manual
//          refer to Table 14 of section 4.2 of lpc17xx user-manual
//          refer to section 4.8.5 and 4.8.6 / Table 43
//          refer to section 4.8.9/Table 46 of lpc17xx user-manual
//          refer to section 21.1 of Timer 0/1/2/3
//          PCONP bit 1 is set to enable Timer 0
//          PCLKSEL0 register can be referred to in Table 40
//          PCLKSEL0 is used to set the PLCK_peripheral to CCLK (same as CPU clock frequency)
//          we must spot the values of CCLK ??
//          TCR(Timer Control register) can be used to reset Timer counter and
//          pre-scale counter - refer to Table 428
//          CTCR register can be used to select between Timer mode and counter mode -
//          in our case, we select Timer mode - in Timer mode, TC is incremented
//          as per prescale counter register and prescale register
//          PR is programmed and its value is used to match with prescale counter -
//          we need to explore and find why the value has been chosen - it may
//          connection with systick timer's tick period
//          TCR can also be used to enable prescale counter and Timer counter,
//          as per Timer mode operation
//
//          once enabled, TC (Timer Counter register) is an upcounting register
//          we can read it, when needed ??? it acts as a time-stamp ??
//          we can find the difference between 2 time-stamps and calculate
//          the time elapsed, latency ??
//
//
	LPC_SYSCTL->PCONP |= 0x02;
	LPC_SYSCTL->PCLKSEL[0] = ( LPC_SYSCTL->PCLKSEL[0]& (~(0x3<<2)) ) | ( 0x01 << 2 );

	/* Reset Timer 0 */
	LPC_TIMER0->TCR = TCR_COUNT_RESET;

	/* The timer needs to just count up continuously. */
	LPC_TIMER0->CTCR = CTCR_CTM_TIMER;

	/* The clock driving the timer is prescaled to a frequency that is good enough
	to get a decent resolution,	but not so fast that the counter value will
	overflow too quickly. */
	//lecture - what is the pre-scale value ?
	//lecture - what is the clock frequency value ?

	LPC_TIMER0->PR =  ( configCPU_CLOCK_HZ / 1000000UL ) - 1UL;

	/* Start the counter. */
	LPC_TIMER0->TCR = TCR_COUNT_ENABLE;
}
