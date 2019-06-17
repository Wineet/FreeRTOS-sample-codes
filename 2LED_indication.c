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
/*-----------------------------------------------------------*/
//GLOBAL VAR TEST
unsigned int red;
unsigned int gr;
unsigned int bl;
unsigned int yl;

/**----------------------------------------------**/


int main( void )
{
	/* Init the semi-hosting. */
	printf( "\n" );

	LPC_GPIO2->DIR = 0x00000200;
	LPC_GPIO2->SET = (1<<9);
	/* Create one of the two tasks. */
	xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask2, "Task 2", 240,NULL, 2, NULL );

	//Task 3
	//xTaskCreate( vTask1, "Task 3", 240, 3, 2, NULL );

	//Task 4
	//	xTaskCreate( vTask1, "Task 4", 240, 4, 2, NULL );

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/
//Periodic Task
void vTask1( void *pvParameters )
{
portTickType xTime1,xTime2;
const char *pcTaskName1 = "Task 1 is running\n";
volatile unsigned long ul;
xTime1 = xTaskGetTickCount();
xTime2 = xTime1;
	for(;;)
	{
		xTime1 = xTaskGetTickCount();
		xTime2 = xTime1;

		gr++;
		while((xTime2-xTime1 ) != 6000 )
		{
			bl++;
			vTaskDelayUntil(&xTime1, 500);
			bl++;
			vTaskDelayUntil(&xTime1, 500);
		}
		gr++;
		vTaskDelayUntil(&xTime1, 10000);
	}
		/* As per most tasks, this task is implemented in an infinite loop. */


}
/*-----------------------------------------------------------*/

void vTask2( void *pvParameters )
{
portTickType xTime1,xTime2;
const char *pcTaskName1 = "Task 2 is running\n";
volatile unsigned long ul;
xTime1 = xTaskGetTickCount();

	for(;;)
	{
		xTime1 = xTaskGetTickCount();
		xTime2 = xTime1;
		red++;
		while((xTime1 - xTime2) != 6000 )
		{
			yl++;
			vTaskDelayUntil(&xTime1, 500);
			yl++;
			vTaskDelayUntil(&xTime1, 500);
		}
		red++;
		vTaskDelayUntil(&xTime1, 10000);
	}
		/* As per most tasks, this task is implemented in an infinite loop. */


}
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


