#include "board.h"
#include "si5351.h"
#include <i2c_soft.h>
#include <stm32f37x_tim.h>
#include <stm32f37x_exti.h>
#include "usb_istr.h"

void sdadc_start(void)
{
	SDADC1->CR2 |= (uint32_t)SDADC_CR2_RSWSTART;
	SDADC2->CR2 |= (uint32_t)SDADC_CR2_RSWSTART;
	SDADC3->CR2 |= (uint32_t)SDADC_CR2_RSWSTART;
}

void timer_enable(void)
{
  //TIM_ClearITPendingBit
  TIM3->SR = (uint16_t)~TIM_IT_Update;
	TIM_SetCounter(TIM3, TIM3PERIOD);
  TIM_Cmd(TIM3, ENABLE);
}

void timer_disable(void)
{
  TIM_Cmd(TIM3, DISABLE);
}

void Delayms(int time)
{
  time *= SYSCLK_VALUE / 1000;

  while(time--);
}

void Delayus(int time)
{
  time *= SYSCLK_VALUE / 1000000;

  while(time--);
}

int si5351_write_bulk(int channel, uint8_t addr, uint8_t bytes, uint8_t *data)
{
	return i2c_soft_command(channel, SI5351_BUS_BASE_ADDR, &addr, 1, data, bytes, NULL, 0);
}

int si5351_write(int channel, uint8_t addr, uint8_t data)
{
	return i2c_soft_command(channel, SI5351_BUS_BASE_ADDR, &addr, 1, &data, 1, NULL, 0);
}

int si5351_read(int channel, uint8_t addr, uint8_t *data)
{
	return i2c_soft_command(channel, SI5351_BUS_BASE_ADDR, &addr, 1, NULL, 0, data, 1);
}

void SCL_HIGH(int c)
{
	switch (c)
	{
		case 0:
      // set PB6
			GPIOB->BSRRL = 0x0040;
			break;
		case 1:
      // set PB4
			GPIOB->BSRRL = 0x0010;
			break;
		case 2:
      // set PA15
			GPIOA->BSRRL = 0x8000;
			break;
	}
}

void SCL_LOW(int c)
{
	switch (c)
	{
		case 0:
      // clr PB6
			GPIOB->BSRRH = 0x0040;
			break;
		case 1:
      // clr PB4
			GPIOB->BSRRH = 0x0010;
			break;
		case 2:
      // clr PA15
			GPIOA->BSRRH = 0x8000;
			break;
	}
}

void SDA_HIGH(int c)
{
	switch (c)
	{
		case 0:
      // set PB7
			GPIOB->BSRRL = 0x0080;
			break;
		case 1:
      // set PB5
			GPIOB->BSRRL = 0x0020;
			break;
		case 2:
      // set PB3
			GPIOB->BSRRL = 0x0008;
			break;
	}
}

void SDA_LOW(int c)
{
	switch (c)
	{
		case 0:
      // set PB7
			GPIOB->BSRRH = 0x0080;
			break;
		case 1:
      // set PB5
			GPIOB->BSRRH = 0x0020;
			break;
		case 2:
      // set PB3
			GPIOB->BSRRH = 0x0008;
			break;
	}
}

int SDA_IN(int c)
{
	switch (c)
	{
		case 0:
      // read PB7
			return GPIOB->IDR & 0x80;
		case 1:
      // read PB5
			return GPIOB->IDR & 0x20;
		case 2:
      // read PB3
			return GPIOB->IDR & 0x08;
	}
	
	return 0;
}

void USBWakeUp_IRQHandler(void)
{
  EXTI_ClearITPendingBit(EXTI_Line18);
}

void USB_LP_IRQHandler(void)
{
  USB_Istr();
}
