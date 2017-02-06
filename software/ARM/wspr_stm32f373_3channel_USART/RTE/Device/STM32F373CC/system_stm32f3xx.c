#include "board.h"
#include <stm32f37x_gpio.h>
#include <stm32f37x_tim.h>
#include <stm32f37x_usart.h>
#include <stm32f37x_sdadc.h>
#include <stm32f37x_pwr.h>
#include <stm32f37x_rcc.h>
#include <stm32f37x_misc.h>
#include <i2c_soft.h>

void TIM3Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef    NVIC_InitStructure;

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

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

#define SDADC_INIT_TIMEOUT   30 /* ~ about two SDADC clock cycles after INIT is set */
#define SDADC_CAL_TIMEOUT    4*30720 /*  ~5.12 ms at 6 MHz  in a single calibration sequence */

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

void USART3Init(void)
{
  USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable USART clock */
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
  
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_7);
  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_7);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  USART_OverSampling8Cmd(USART3, ENABLE);
	
  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follow:
  - BaudRate = 230400 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 921600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);
  
  /* Enable USART */
  USART_Cmd(USART3, ENABLE);

  /* Enable the USARTx Receive interrupt: this interrupt is generated when the
  USARTx receive data register is not empty */
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
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

void ClockInit(void)
{
  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY));

  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_HSE;
 
  while ((RCC->CFGR & RCC_CFGR_SWS) != 4); 
}

/*#define PLLMUL 2

void ClockInit(void)
{
  RCC->CR |= RCC_CR_HSEON;
  while (!(RCC->CR & RCC_CR_HSERDY));

  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL);
  RCC->CFGR |= RCC_CFGR_PLLSRC | ((PLLMUL - 2)  << 18);

  RCC->CR |= RCC_CR_PLLON;
  while(!(RCC->CR & RCC_CR_PLLRDY));
	
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
 
  while ((RCC->CFGR & RCC_CFGR_SWS) != 8); 
}*/

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

	TIM3Init();
	SDADC3Init();
	SDADC2Init();
	SDADC1Init();
	USART3Init();
	I2CInit();
}
