#include "board.h"
#include <stm32f37x_tim.h>
#include <stm32f37x_misc.h>
#include <stm32f37x_usart.h>
#include <stm32f37x_sdadc.h>
#include <si5351.h>

volatile unsigned int record_length;

volatile unsigned char send_buffer[SAMPLE_RATE];
volatile unsigned char *send_buffer_write_p;
unsigned char *send_buffer_read_p;

void TIM3_IRQHandler(void)
{
	unsigned short value;
	
  if (TIM3->SR & TIM_IT_Update)
  {
    while (!(SDADC3->ISR & SDADC_FLAG_REOC));
		value = SDADC3->RDATAR;
    /* Enable software start conversion of the selected regular channel */
		SDADC3->CR2 |= (uint32_t)SDADC_CR2_RSWSTART;
		if (record_length)
		{
			record_length--;
			serial_sendw(value);
		}
	  //TIM_ClearITPendingBit
	  TIM3->SR = (uint16_t)~TIM_IT_Update;
	}
}

void serial_send(unsigned char c)
{
	/* Disable interrupts */
	__disable_irq();
	
	*send_buffer_write_p = c;
	if (send_buffer_write_p == &send_buffer[SAMPLE_RATE-1])
		send_buffer_write_p = send_buffer;
	else
		send_buffer_write_p++;
	
	/* Enable interrupts back */
	__enable_irq();
}

void serial_sendw(unsigned short s)
{
	/* Disable interrupts */
	__disable_irq();
	
	*send_buffer_write_p = s & 0xFF;
	if (send_buffer_write_p == &send_buffer[SAMPLE_RATE-1])
		send_buffer_write_p = send_buffer;
	else
		send_buffer_write_p++;

	*send_buffer_write_p = s >> 8;
	if (send_buffer_write_p == &send_buffer[SAMPLE_RATE-1])
		send_buffer_write_p = send_buffer;
	else
		send_buffer_write_p++;
	
	/* Enable interrupts back */
	__enable_irq();
}

/*void USART3_IRQHandler(void)
{
  if (USART3->ISR & USART_FLAG_RXNE)
  {
    process_command(USART3->RDR);
	}
}*/

int main(void)
{
  NVIC_InitTypeDef    NVIC_InitStructure;

	record_length = 0;
	command_processor_init();

	send_buffer_write_p = send_buffer;
	send_buffer_read_p = (unsigned char*)send_buffer;

	si5351_init(0);

  /* Enable software start conversion of the selected regular channel */
  SDADC3->CR2 |= (uint32_t)SDADC_CR2_RSWSTART;
	
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

//  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_Init(&NVIC_InitStructure);
	
  while (1)
  {
		if (send_buffer_write_p != send_buffer_read_p &&
			  USART3->ISR & USART_FLAG_TXE)
		{
      USART3->TDR = *send_buffer_read_p;
			if (send_buffer_read_p == &send_buffer[SAMPLE_RATE-1])
				send_buffer_read_p = (unsigned char*)send_buffer;
			else
				send_buffer_read_p++;
	  }
    if (USART3->ISR & USART_FLAG_RXNE)
      process_command(USART3->RDR);
#ifndef DEBUG
    __wfi(); // entering sleep mode
#endif
  }
}
