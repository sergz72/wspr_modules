#include "board.h"
#include <stm32f37x_tim.h>
#include <stm32f37x_sdadc.h>
#include <usb_lib.h>

volatile unsigned short send_buffers[SEND_BUFFER_COUNT][SEND_BUFFER_LENGTH];

void TIM3_IRQHandler(void)
{
  if (TIM3->SR & TIM_IT_Update)
  {
		if (record_length)
		{
			while (!(SDADC1->ISR & SDADC_FLAG_REOC));
			*app_buffer_p++ = SDADC1->RDATAR;
			while (!(SDADC2->ISR & SDADC_FLAG_REOC));
			*app_buffer_p++ = SDADC2->RDATAR;
			while (!(SDADC3->ISR & SDADC_FLAG_REOC));
			*app_buffer_p++ = SDADC3->RDATAR;
			/* Enable software start conversion of the selected regular channel */
			sdadc_start();
			if (app_buffer_p == app_buffer + SEND_BUFFER_LENGTH)
			{
				if (app_buffer_p == (unsigned short*)send_buffers[SEND_BUFFER_COUNT])
					app_buffer = app_buffer_p = (unsigned short*)send_buffers[0];
				else
				  app_buffer = app_buffer_p;
			}
			record_length--;
		}
    else
      timer_disable();			
	  //TIM_ClearITPendingBit
	  TIM3->SR = (uint16_t)~TIM_IT_Update;
	}
}
