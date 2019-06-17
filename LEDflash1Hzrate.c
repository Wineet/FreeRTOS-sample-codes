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
//#include "LPC17xx.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "port.c"
/* Demo includes. */
#include "basic_io.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )
//#define configASSERT(x)	if(x==0){ taskDISABLE_INTERRUPTS(); for(;;); }
/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void ToggleLED1(void);
void ToggleLED2(void);
void ToggleLED3(void);
void ToggleLED4(void);
void ToggleBuzz(void);
void ToggleLED(void);
void TimerLOAD(void);
void TimerStart(void);
void TimerinitSETUP(void);
unsigned long int TimerGETSERVICES(void);
/*-----------------------------------------------------------*/



/*XXXXXXXXXXXXXXXXXXXXX VARIABLES TO TRACE XXXXXXXXXXXXXXX*/
volatile int32_t u=0;
volatile int32_t v=0;
volatile int32_t x=0;
volatile int32_t y=0;
unsigned long BlueLED1State=0;
unsigned long GreenLED2State=0;
unsigned long OrangeLED3State=0;
unsigned long RedLED4State=0;
//unsigned long TimeStamp1=0;
//unsigned long TimeStamp2=0;
//volatile unsigned long TimeStamp3=0;
//volatile unsigned long TimeStamp4=0;
//unsigned long RES1=0;
//unsigned long RES2=0;
//unsigned long TS2;
//unsigned long TS3;

//volatile int32_t flag=0;
//volatile int32_t flag1=0;
/*--------------------------------------------------------*/
int main( void )
{
	/* Init the semi-hosting. */
	//printf( "\n" );
	TimerinitSETUP();
//struct PARA *P1=&R1,*P2=&R2,*P3=&R3,*P4=&R4;


	//LPC_PINCON->PINSEL4	|= ( 3 << 18 );
	//LPC_GPIO2->DIR |= ( 1 << 9 );
	//LPC_GPIO2->DIR |= ( 1 << 11 );
// LPC_GPIO_T *LPC_GPItO_PORT;
	//ToggleBuzz();
	//Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT,2,9);

	/* Create one of the two tasks. */
	int ret1,ret2;

	ret1= xTaskCreate(	vTask1,		/* Pointer to the function that implements the task. */
					"Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */
	configASSERT(ret1==pdPASS);
	ret2= xTaskCreate(	vTask2,		/* Pointer to the function that implements the task. */
					"Task 2",	/* Text name for the task.  This is to facilitate debugging only. */
					240,		/* Stack depth in words. */
					NULL,		/* We are not using the task parameter. */
					1,			/* This task will run at priority 1. */
					NULL );		/* We are not using the task handle. */
	configASSERT(ret2==pdPASS);
		/* Create the other task in exactly the same way. */
	//xTaskCreate( vTask2, "Task 2", 240, NULL, 1, NULL );
//	xTaskCreate( vTask3, "Task 3", 240, NULL, 2, NULL );
	//	ToggleLED(); //offLED
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
const char *pcTaskName = "Task 1 is running\n";
TickType_t xLastExecutionTime;
xLastExecutionTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{	TimerLOAD();

		ToggleLED1();	//on
		ToggleLED2();	//on
		//vTaskDelay()
	//	TimeStamp1=TimerGETSERVICES();
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	//	TimeStamp2=TimerGETSERVICES();
		ToggleLED1();	//off
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
		ToggleLED1();	//on
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
		ToggleLED1();	//off
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
		ToggleLED1();	//on
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
		ToggleLED1();	//off
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
		ToggleLED2();	//on
		vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 4000 ) );
		//RES1=TS2-TimeStamp1;
	//	RES2=TimeStamp2-TS3 +(TS3-TS2) ;//+ RES1;
		u++;

		//taskYIELD();
	}
}
void vTask2( void *pvParameters )
{
const char *pcTaskName = "Task 2 is running\n";

TickType_t xLastExecutionTime;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
	//TimerLOAD();
	//TimeStamp4=TimerGETSERVICES();
	ToggleLED3();	//on
	ToggleLED4();	//on
	//vTaskDelay()
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	ToggleLED3();	//off
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	ToggleLED3();	//on
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	ToggleLED3();	//off
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	ToggleLED3();	//on
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	ToggleLED3();	//off
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 1000 ) );
	ToggleLED4();	//on
	vTaskDelayUntil( &xLastExecutionTime, pdMS_TO_TICKS( 4000 ) );
	//TimeStamp4=TimerGETSERVICES();
	//RES2=TimeStamp4-TimeStamp3;
	v++;
	}
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void ToggleLED(void){

/*-------------THESE CODE USES USB_LED at P2.9---------------------*/
	unsigned long ulLEDState;
	ulLEDState = LPC_GPIO2->PIN;
	LPC_GPIO2->PIN = (ulLEDState ^ ( 1<<9 ));
/*----------------------------------------------------------*/
}
void ToggleLED1(void){

/*-------------THESE CODE USES USB_LED at P2.9---------------------*/
//	unsigned long ulLED1State=0;
	if(BlueLED1State ==0)
		(BlueLED1State)=1;
	else
		(BlueLED1State)=0;

/*----------------------------------------------------------*/
}
void ToggleLED2(void){

/*-------------THESE CODE USES USB_LED at P2.9---------------------*/
	//unsigned long ulLED2State=0;
	if(GreenLED2State ==0)
			(GreenLED2State)=1;
		else
			(GreenLED2State)=0;

/*----------------------------------------------------------*/
}
void ToggleLED3(void){

/*-------------THESE CODE USES USB_LED at P2.9---------------------*/
	//unsigned long ulLED3State=0;
	if(OrangeLED3State ==0)
			(OrangeLED3State)=1;
		else
			(OrangeLED3State)=0;

/*----------------------------------------------------------*/
}
void ToggleLED4(void){

/*-------------THESE CODE USES USB_LED at P2.9---------------------*/

	if(RedLED4State ==0)
			(RedLED4State)=1;
		else
			(RedLED4State)=0;

/*----------------------------------------------------------*/
}
void ToggleBuzz(void){

/*-------------THESE CODE USES USB_LED at P2.9---------------------*/
	unsigned long ulLEDState;
	ulLEDState = LPC_GPIO2->PIN;
	LPC_GPIO2->PIN = (ulLEDState ^ ( 1<<11 ));
/*----------------------------------------------------------*/
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
void TimerinitSETUP(void)
{
//	LPC_SYSCTL->PCONP|= (1<<1); //enable PCLK of TIMER0 default
	LPC_SYSCTL->PCLKSEL[0] |=(1<<2); //PCLK=100/4 MHz = 25 MHz by default
	LPC_TIMER0->PR = ( configCPU_CLOCK_HZ / 1000000UL ) - 1UL;	//1us resolution
	//LPC_TIMER0->PR = 100;
//	LPC_TIMER0->MCR |=(1<<2);			//RESET on MATCH
//	LPC_TIMER0->TCR =0;				//disable timer
//	LPC_TIMER0->MR[0] = 0xFFFFF;	//Max values
	LPC_TIMER0->TCR =1;
}
void TimerLOAD(void){
LPC_TIMER0->TC=( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
}
unsigned long int TimerGETSERVICES(void)
{
	//Enable
	//while(LPC_TIMER0->TC!=LPC_TIMER0->MR[0]);		//Timer increment value
	return LPC_TIMER0->TC;
}
