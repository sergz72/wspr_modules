#include "board.h"
#include <si5351.h>
#include <usb_lib.h>
#include "usb_pwr.h"
#include <stm32f37x_misc.h>
#include <stm32f37x_tim.h>

extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
__IO uint32_t packet_sent=1;
__IO uint32_t packet_receive=1;

extern volatile unsigned short send_buffers[SEND_BUFFER_COUNT][SEND_BUFFER_LENGTH];
unsigned short *usb_buffer;

void USB_send(unsigned char *buffer, int l)
{
	while (!packet_sent);
  CDC_Send_DATA ((unsigned char*)buffer, l);
}

void serial_send(unsigned char c)
{
	USB_send(&c, 1);
}

void USB_sendbuf(unsigned short *buffer)
{
	while (!packet_sent);
  CDC_Send_DATAW(buffer, SEND_BUFFER_LENGTH);
}

int main(void)
{
  int command_size, l;
	unsigned char *p;
  NVIC_InitTypeDef    NVIC_InitStructure;
	
	record_length = 0;
	usb_buffer = app_buffer = app_buffer_p = (unsigned short*)send_buffers[0];

  //TIM_ClearITPendingBit
  TIM3->SR = 0;
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	command_processor_init();

	si5351_init();

  USB_Init();
	
//	serial_send('t');
//	serial_send('e');
//	serial_send('s');
//	serial_send('t');
	
  while (1)
  {
    if (bDeviceState == CONFIGURED)
    {
			while (usb_buffer != app_buffer)
			{
				USB_sendbuf(usb_buffer);
				usb_buffer += SEND_BUFFER_LENGTH;
				if (usb_buffer == (unsigned short*)send_buffers[SEND_BUFFER_COUNT])
					usb_buffer = (unsigned short*)send_buffers[0];
			}
      CDC_Receive_DATA();
      /*Check to see if we have data yet */
      if (Receive_length  != 0)
      {
				l = command_size = Receive_length;
				p = (unsigned char*)Receive_Buffer;
				while (command_size--)
          process_command(*p++);
        Receive_length -= l;
      }
    }
#ifndef DEBUG
    __wfi(); // entering sleep mode
#endif
  }
}
