#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x.h"

#include "Types.h"

#include <cross_studio_io.h>

static void MainTask1( void *pvParameters );
static void MainTask2( void *pvParameters );

int main( void )
{
  xTaskCreate( MainTask1, ( signed char * ) "Main1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL );
  xTaskCreate( MainTask2, ( signed char * ) "Main2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL );

  vTaskStartScheduler();

  for( ;; );
}
/*-----------------------------------------------------------*/

/* Described at the top of this file. */
void MainTask1( void *pvParameters )
{
  while( true )
  {
    vTaskDelay( 500 );
    debug_printf( "task 1\n" );
    vTaskDelay( 500 );
  }
}

/* Described at the top of this file. */
void MainTask2( void *pvParameters )
{
  while( true )
  {
    vTaskDelay( 500 );
    debug_printf( "task 2\n" );
    vTaskDelay( 500 );
  }
}

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
  /* This function will get called if a task overflows its stack.   If the
  parameters are corrupt then inspect pxCurrentTCB to find which was the
  offending task. */

  ( void ) pxTask;
  ( void ) pcTaskName;

  for( ;; );
}
/*-----------------------------------------------------------*/

void assert_failed( unsigned char *pucFile, unsigned long ulLine )
{
  ( void ) pucFile;
  ( void ) ulLine;

  for( ;; );
}
