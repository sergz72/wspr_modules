#include "board.h"
#include <stm32f37x_tim.h>
#include <stm32f37x_usart.h>
#include <stm32f37x_sdadc.h>
#include <si5351.h>

volatile unsigned char send_buffer[SAMPLE_RATE];

void TIM3_IRQHandler(void)
{
	unsigned short value1, value2, value3;
	
  if (TIM3->SR & TIM_IT_Update)
  {
		if (record_length)
		{
			while (!(SDADC1->ISR & SDADC_FLAG_REOC));
			value1 = SDADC1->RDATAR;
			while (!(SDADC2->ISR & SDADC_FLAG_REOC));
			value2 = SDADC2->RDATAR;
			while (!(SDADC3->ISR & SDADC_FLAG_REOC));
			value3 = SDADC3->RDATAR;
			/* Enable software start conversion of the selected regular channel */
			sdadc_start();
			serial_sendw(value1);
			serial_sendw(value2);
			serial_sendw(value3);
			record_length--;
		}
    else
      timer_disable();			
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
		send_buffer_write_p = (unsigned char*)send_buffer;
	else
		send_buffer_write_p++;

	/* Enable interrupts back */
	__enable_irq();
}

void serial_sendw(unsigned short s)
{
	*send_buffer_write_p = s & 0xFF;
	if (send_buffer_write_p == &send_buffer[SAMPLE_RATE-1])
		send_buffer_write_p = (unsigned char*)send_buffer;
	else
		send_buffer_write_p++;

	*send_buffer_write_p = s >> 8;
	if (send_buffer_write_p == &send_buffer[SAMPLE_RATE-1])
		send_buffer_write_p = (unsigned char*)send_buffer;
	else
		send_buffer_write_p++;
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
	
	record_length = 0;
	command_processor_init();

	send_buffer_write_p = send_buffer_read_p = (unsigned char*)send_buffer;

	si5351_init();

//	serial_send('t');
//	serial_send('e');
//	serial_send('s');
//	serial_send('t');
	
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
