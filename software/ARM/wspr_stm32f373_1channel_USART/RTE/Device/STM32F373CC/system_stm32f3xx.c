#include "board.h"
#include <stm32f37x_gpio.h>
#include <stm32f37x_tim.h>
#include <stm32f37x_usart.h>
#include <stm32f37x_sdadc.h>
#include <stm32f37x_pwr.h>
#include <stm32f37x_rcc.h>
#ifdef I2C_SOFT
#include <i2c_soft.h>
#else
#include <stm32f37x_i2c.h>
#endif

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

	TIM_SetCounter(TIM3, TIM3PERIOD);
	
  TIM_Cmd(TIM3, ENABLE);

  /* TIM IT enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
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

  /* POT_SDADC channel 6P (PD8) */
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

  /* Channel3 configuration */
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

  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follow:
  - BaudRate = 230400 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 460800;
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

#ifdef I2C_SOFT
void I2C1Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	i2c_soft_init();
	
  // Configure I2C pins: SCL, SDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
#else
/* I2C TIMING Register define when I2C clock source is SYSCLK */
/* I2C TIMING is calculated in case of the I2C Clock source is the SYSCLK = 12 MHz */
/* set TIMING to reach 100 KHz speed (Rise time = 640ns, Fall time = 20ns) */

#define I2C1_TIMING              0x2062121F

void I2C1Init(void)
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure; 
   
  // Enable I2C clock
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

  // Configure the I2C clock source. The clock is derived from the SYSCLK
  RCC_I2CCLKConfig(RCC_I2C1CLK_SYSCLK);
  
  // Connect PXx to I2C_SCL
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_4);

  // Connect PXx to I2C_SDA
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_4); 

  // Configure I2C pins: SCL, SDA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // I2C configuration
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_Timing = I2C1_TIMING;
  
  // Apply I2C configuration after enabling it
  I2C_Init(I2C1, &I2C_InitStructure);
  
  // I2C Peripheral Enable
  I2C_Cmd(I2C1, ENABLE);
}
#endif

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
  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */

  ClockInit();
	
  /* Enable the PWR module clock */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	
  //enable the GPIO clock for port GPIOB
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

  //enable the GPIO clock for port GPIOD
  RCC->AHBENR |= RCC_AHBENR_GPIODEN;

	TIM3Init();
	SDADC3Init();
	USART3Init();
	I2C1Init();
}
