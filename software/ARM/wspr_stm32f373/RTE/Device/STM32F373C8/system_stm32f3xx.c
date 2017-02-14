#include "board.h"
#include <stm32f37x_gpio.h>
#include <stm32f37x_tim.h>
#include <stm32f37x_sdadc.h>
#include <stm32f37x_pwr.h>
#include <stm32f37x_rcc.h>
#include <stm32f37x_misc.h>
#include <stm32f37x_exti.h>
#include <i2c_soft.h>

void TIM3Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  //enable the clock for Timer 3
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = TIM3PERIOD;
  TIM_TimeBaseStructure.TIM_Prescaler = 0; // No divide
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ARRPreloadConfig(TIM3, ENABLE);

  /* TIM IT enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

#define SDADC_INIT_TIMEOUT   100 /* ~ about two SDADC clock cycles after INIT is set */
#define SDADC_CAL_TIMEOUT    (SYSCLK_VALUE / 100000 * 512) /*  ~5.12 ms at 6 MHz  in a single calibration sequence */

void SDADC3Init(void)
{
  SDADC_InitTypeDef SDADC_InitStructure;
  SDADC_AINStructTypeDef SDADC_AINStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  int SDADCTimeout;
	
  /* SDADC APB2 interface clock enable */
  RCC->APB2ENR |= RCC_APB2ENR_SDADC3EN;
  
  /* Enable SDADC analog interface */
  PWR_SDADCAnalogCmd(PWR_SDADCAnalog_3, ENABLE);

  RCC_SDADCCLKConfig(SDADC_CLK_DIVIDER);

  /* SDADC channel 6P (PD8) */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Select external reference */
  SDADC_VREFSelect(SDADC_VREF_Ext);

  /* Insert delay equal to ~5 ms */
  Delayms(5);
  
  /* Enable SDADC */
  SDADC_Cmd(SDADC3, ENABLE);

  /* Enter initialization mode */
  SDADC_InitModeCmd(SDADC3, ENABLE);
  SDADCTimeout = SDADC_INIT_TIMEOUT;
  /* wait for INITRDY flag to be set */
  while((SDADC_GetFlagStatus(SDADC3, SDADC_FLAG_INITRDY) == RESET) && (--SDADCTimeout != 0));

  if(SDADCTimeout == 0)
  {
		while (1);
  }

  /* Analog Input configuration conf0: use single ended zero reference */
  SDADC_AINStructure.SDADC_InputMode = SDADC_InputMode_SEOffset;
  SDADC_AINStructure.SDADC_Gain = SDADC_Gain_1;
  SDADC_AINStructure.SDADC_CommonMode = SDADC_CommonMode_VSSA;
  SDADC_AINStructure.SDADC_Offset = 0;
  SDADC_AINInit(SDADC3, SDADC_Conf_0, &SDADC_AINStructure);

  /* select SDADC channel 6 to use conf0 */
  SDADC_ChannelConfig(SDADC3, SDADC_Channel_6, SDADC_Conf_0);

  /* Channel 6 configuration */
  SDADC_InitStructure.SDADC_Channel = SDADC_Channel_6;
  SDADC_InitStructure.SDADC_ContinuousConvMode = DISABLE;
  SDADC_InitStructure.SDADC_FastConversionMode = DISABLE;
  SDADC_Init(SDADC3, &SDADC_InitStructure);

  /* Exit initialization mode */
  SDADC_InitModeCmd(SDADC3, DISABLE);

  /* configure calibration to be performed on conf0 */
  SDADC_CalibrationSequenceConfig(SDADC3, SDADC_CalibrationSequence_1);
  /* start POT_SDADC Calibration */
  SDADC_StartCalibration(SDADC3);
  /* Set calibration timeout: 5.12 ms at 6 MHz in a single calibration sequence */
  SDADCTimeout = SDADC_CAL_TIMEOUT;
  /* wait for POT_SDADC Calibration process to end */
  while((SDADC_GetFlagStatus(SDADC3, SDADC_FLAG_EOCAL) == RESET) && (--SDADCTimeout != 0));
  
  if(SDADCTimeout == 0)
  {
		while (1);
  }
}

void SDADC2Init(void)
{
  SDADC_InitTypeDef SDADC_InitStructure;
  SDADC_AINStructTypeDef SDADC_AINStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  int SDADCTimeout;
	
  /* SDADC APB2 interface clock enable */
  RCC->APB2ENR |= RCC_APB2ENR_SDADC2EN;
  
  /* Enable SDADC analog interface */
  PWR_SDADCAnalogCmd(PWR_SDADCAnalog_2, ENABLE);

  /* SDADC channel 6P (PB2) */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Enable SDADC */
  SDADC_Cmd(SDADC2, ENABLE);

  /* Enter initialization mode */
  SDADC_InitModeCmd(SDADC2, ENABLE);
  SDADCTimeout = SDADC_INIT_TIMEOUT;
  /* wait for INITRDY flag to be set */
  while((SDADC_GetFlagStatus(SDADC2, SDADC_FLAG_INITRDY) == RESET) && (--SDADCTimeout != 0));

  if(SDADCTimeout == 0)
  {
		while (1);
  }

  /* Analog Input configuration conf0: use single ended zero reference */
  SDADC_AINStructure.SDADC_InputMode = SDADC_InputMode_SEOffset;
  SDADC_AINStructure.SDADC_Gain = SDADC_Gain_1;
  SDADC_AINStructure.SDADC_CommonMode = SDADC_CommonMode_VSSA;
  SDADC_AINStructure.SDADC_Offset = 0;
  SDADC_AINInit(SDADC2, SDADC_Conf_0, &SDADC_AINStructure);

  /* select SDADC channel 6 to use conf0 */
  SDADC_ChannelConfig(SDADC2, SDADC_Channel_6, SDADC_Conf_0);

  /* Channel 6 configuration */
  SDADC_InitStructure.SDADC_Channel = SDADC_Channel_6;
  SDADC_InitStructure.SDADC_ContinuousConvMode = DISABLE;
  SDADC_InitStructure.SDADC_FastConversionMode = DISABLE;
  SDADC_Init(SDADC2, &SDADC_InitStructure);

  /* Exit initialization mode */
  SDADC_InitModeCmd(SDADC2, DISABLE);

  /* configure calibration to be performed on conf0 */
  SDADC_CalibrationSequenceConfig(SDADC2, SDADC_CalibrationSequence_1);
  /* start POT_SDADC Calibration */
  SDADC_StartCalibration(SDADC2);
  /* Set calibration timeout: 5.12 ms at 6 MHz in a single calibration sequence */
  SDADCTimeout = SDADC_CAL_TIMEOUT;
  /* wait for POT_SDADC Calibration process to end */
  while((SDADC_GetFlagStatus(SDADC2, SDADC_FLAG_EOCAL) == RESET) && (--SDADCTimeout != 0));
  
  if(SDADCTimeout == 0)
  {
		while (1);
  }
}

void SDADC1Init(void)
{
  SDADC_InitTypeDef SDADC_InitStructure;
  SDADC_AINStructTypeDef SDADC_AINStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  int SDADCTimeout;
	
  /* SDADC APB2 interface clock enable */
  RCC->APB2ENR |= RCC_APB2ENR_SDADC1EN;
  
  /* Enable SDADC analog interface */
  PWR_SDADCAnalogCmd(PWR_SDADCAnalog_1, ENABLE);

  /* SDADC channel 6P (PB0) */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Enable SDADC */
  SDADC_Cmd(SDADC1, ENABLE);

  /* Enter initialization mode */
  SDADC_InitModeCmd(SDADC1, ENABLE);
  SDADCTimeout = SDADC_INIT_TIMEOUT;
  /* wait for INITRDY flag to be set */
  while((SDADC_GetFlagStatus(SDADC1, SDADC_FLAG_INITRDY) == RESET) && (--SDADCTimeout != 0));

  if(SDADCTimeout == 0)
  {
		while (1);
  }

  /* Analog Input configuration conf0: use single ended zero reference */
  SDADC_AINStructure.SDADC_InputMode = SDADC_InputMode_SEOffset;
  SDADC_AINStructure.SDADC_Gain = SDADC_Gain_1;
  SDADC_AINStructure.SDADC_CommonMode = SDADC_CommonMode_VSSA;
  SDADC_AINStructure.SDADC_Offset = 0;
  SDADC_AINInit(SDADC1, SDADC_Conf_0, &SDADC_AINStructure);

  /* select SDADC channel 6 to use conf0 */
  SDADC_ChannelConfig(SDADC1, SDADC_Channel_6, SDADC_Conf_0);

  /* Channel 6 configuration */
  SDADC_InitStructure.SDADC_Channel = SDADC_Channel_6;
  SDADC_InitStructure.SDADC_ContinuousConvMode = DISABLE;
  SDADC_InitStructure.SDADC_FastConversionMode = DISABLE;
  SDADC_Init(SDADC1, &SDADC_InitStructure);

  /* Exit initialization mode */
  SDADC_InitModeCmd(SDADC1, DISABLE);

  /* configure calibration to be performed on conf0 */
  SDADC_CalibrationSequenceConfig(SDADC1, SDADC_CalibrationSequence_1);
  /* start POT_SDADC Calibration */
  SDADC_StartCalibration(SDADC1);
  /* Set calibration timeout: 5.12 ms at 6 MHz in a single calibration sequence */
  SDADCTimeout = SDADC_CAL_TIMEOUT;
  /* wait for POT_SDADC Calibration process to end */
  while((SDADC_GetFlagStatus(SDADC1, SDADC_FLAG_EOCAL) == RESET) && (--SDADCTimeout != 0));
  
  if(SDADCTimeout == 0)
  {
		while (1);
  }
}

void I2CInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	i2c_soft_init(0);
	i2c_soft_init(1);
	i2c_soft_init(2);

  // Configure I2C pins: SDA1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // Configure I2C pins: SCL1
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  // Configure I2C pins: SCL2, SDA2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // Configure I2C pins: SCL3, SDA3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

#define PLLMUL 4

void ClockInit(void)
{
  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY));

// APB1 Prescaler = 2
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;		

  FLASH->ACR |= FLASH_ACR_LATENCY_1;
	
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL);
  RCC->CFGR |= RCC_CFGR_PLLSRC | ((PLLMUL - 2)  << 18);

  RCC->CR |= RCC_CR_PLLON;
  while(!(RCC->CR & RCC_CR_PLLRDY));
	
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
 
  while ((RCC->CFGR & RCC_CFGR_SWS) != 8); 
}

void USBInit(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure; 
  NVIC_InitTypeDef NVIC_InitStructure;
	
  /* Select USBCLK source */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
  
  /* Enable the USB clock */
  RCC->APB1ENR |= RCC_APB1ENR_USBEN;

  /*Set PA11,12 as AF - USB_DM,DP*/ 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /*SET PA11,12 for USB: USB_DM,DP*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_14);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_14);

   /* Configure the EXTI line 18 connected internally to the USB IP */
  EXTI_ClearITPendingBit(EXTI_Line18);
  EXTI_InitStructure.EXTI_Line = EXTI_Line18;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 

  /* Enable the USB interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the USB Wake-up interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Setup the microcontroller system
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
	/* Set floating point coprosessor access mode. */
//  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */

  ClockInit();
	
  /* Enable the PWR module clock */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;

  //enable the GPIO clock for port GPIOA
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
  //enable the GPIO clock for port GPIOB
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

  //enable the GPIO clock for port GPIOD
  RCC->AHBENR |= RCC_AHBENR_GPIODEN;

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	TIM3Init();
	SDADC3Init();
	SDADC2Init();
	SDADC1Init();
	I2CInit();
	USBInit();
}
