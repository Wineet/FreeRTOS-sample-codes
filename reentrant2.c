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
void vTask1( int para );
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
					1,		/* We are not using the task parameter. */
					2,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */

	/* Create the other task in exactly the same way. */
	xTaskCreate( vTask1, "Task 2", 240,2, 2, NULL );

	//Task 3
	xTaskCreate( vTask1, "Task 3", 240, 3, 2, NULL );

	//Task 4
		xTaskCreate( vTask1, "Task 4", 240, 4, 2, NULL );

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
void vTask1( int para )
{
portTickType xLastWakeTime;
const char *pcTaskName1 = "Task 1 is running\n";
const char *pcTaskName2 = "Task 2 is running\n";
const char *pcTaskName3 = "Task 3 is running\n";
const char *pcTaskName4 = "Task 4 is running\n";

volatile unsigned long ul;
xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
int arg = para;
	if(arg == 1)
	{
		for( ;; )
		{

			/* Print out the name of this task. */
			vPrintString( pcTaskName1 );

			/*****---Blue LED ----*****/
			bl++;
			vTaskDelayUntil(&xLastWakeTime, 1000);
			bl++;
			vTaskDelayUntil(&xLastWakeTime, 1000);

			/****----------------*****/
		}
	}

	if(arg == 2)
		{
			for( ;; )
			{

				/* Print out the name of this task. */
				vPrintString( pcTaskName2 );

				/*****red LED ****/
				red++;
				vTaskDelayUntil(&xLastWakeTime, 1000);
				red++;
				vTaskDelayUntil(&xLastWakeTime,1000);
				/*****------*****/
			}
		}

	if(arg == 3)
		{
			for( ;; )
			{

				/* Print out the name of this task. */
				vPrintString( pcTaskName3 );

				/****----Green LED ----****/
				gr++;
				vTaskDelayUntil(&xLastWakeTime, 1000);
				gr++;
				vTaskDelayUntil(&xLastWakeTime, 1000);
				/***---------------------***/
			}
		}
	if(arg == 4)
		{
			for( ;; )
			{

				/* Print out the name of this task. */
				vPrintString( pcTaskName4 );

				/*****---yellow LED ----*****/
				yl++;
				vTaskDelayUntil(&xLastWakeTime, 1000);
				yl++;
				vTaskDelayUntil(&xLastWakeTime, 1000);

				/****----------------*****/
			}
		}
}
/*-----------------------------------------------------------*/


//Single LED
void vTask2( void *pvParameters )
{
portTickType xLastWakeTime;
const char *pcTaskName = "Task 2 is running\n";
const char *pcTaskcmpl = "Task 2 complete*******\n";
volatile unsigned long ul;
xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );

		/*****red LED ****/
		red++;
		vTaskDelayUntil(&xLastWakeTime, 2000);
		red++;
		vTaskDelayUntil(&xLastWakeTime, 2000);
		/*****------*****/

		/*LPC_GPIO2->CLR = (1<<9);
		vTaskDelay(2000);
		LPC_GPIO2->SET = (1<<9);
		vTaskDelay(500);
		vPrintString( pcTaskcmpl );
		/* Delay for a period. */
		/*for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */

		//}

		//taskYIELD();
	}
}
/*-----------------------------------------------------------*/

void vTask3( void *pvParameters )
{
	portTickType xLastWakeTime;
const char *pcTaskName = "Task 3 is running\n";
volatile unsigned long ul;
xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );

		/****----Green LED ----****/
		gr++;
		vTaskDelayUntil(&xLastWakeTime, 3000);
		gr++;
		vTaskDelayUntil(&xLastWakeTime, 3000);
		/***---------------------***/

		/* Delay for a period. */
		/*for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */


	//	}
		//taskYIELD();
	}
}
/*-----------------------------------------------------------*/
void vTask4( void *pvParameters )
{
portTickType xLastWakeTime;
const char *pcTaskName = "Task 4 is running\n";
volatile unsigned long ul;
xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{

		/* Print out the name of this task. */
		vPrintString( pcTaskName );

		/*****---Blue LED ----*****/
		yl++;
		vTaskDelayUntil(&xLastWakeTime, 4000);
		yl++;
		vTaskDelayUntil(&xLastWakeTime, 4000);

		/****----------------*****/
/*
		LPC_GPIO2->CLR = (1<<9);
		vTaskDelayUntil(&xLastWakeTime, 2000);
		LPC_GPIO2->SET = (1<<9);
		vTaskDelayUntil(&xLastWakeTime, 2000);*/

		/* Delay for a period. */
		/*for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */


		//}*/
		//taskYIELD();
	}
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


