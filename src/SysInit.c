/**********************************************************************************
 * File : SysInit.c
 * Doel : Met SysInit wordt het systeem geinitialiseerd en ingesteld, het gaat
 *	  daarbij om:
 *	  - GPIO (Analoog / Digitaal)
 *	  - UART (Serieel, I2C, SPI etc.)
 *	  - Interrupt instellingen / prioriteit
 * Written by : Tom Bulsink
 * (C) Brunelco Electronic Innovators
 *********************************************************************************/

#include "SysInit.h"
#include "stm32f10x.h"

static void SysInitRCC	( void );
static void SysInitNVIC	( void );

void SysInit( void )
{
  SysInitRCC();
  SysInitNVIC();
}

void SysInitRCC( void )
{
  // System clock is set by the SystemInit-function, called by the startup-file before main is called.
  // So, when correctly configured in system_stm32f10x.c, the system runs at HSE 8 MHz, using PLL to create 72 MHz SystemClock

  // ADCCLK = PCLK2/<divider>
  // PCLK2 runs @72 MHz, ADCCLK can be max. 14 MHz
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);


  /* Enable AHB periphs */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

  /* Enable APB1 periphs */
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );

  /* Enable APB2 periphs */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); // for remapping purposes
}

void SysInitNVIC( void )
{
  NVIC_InitTypeDef NVICCfg;

#ifdef  VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable( NVIC_VectTab_RAM, 0x0 );
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x0 );
#endif

  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

  /* Enable the USART2 Interrupt */
  NVICCfg.NVIC_IRQChannel = USART2_IRQn;
  NVICCfg.NVIC_IRQChannelPreemptionPriority = 0;
  NVICCfg.NVIC_IRQChannelSubPriority = 0;
  NVICCfg.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init( &NVICCfg );
}

#ifndef NDEBUG
int	SysInitTest( void );
#endif	// NDEBUG
