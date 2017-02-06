#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "board.h"
#include <stm32f37x_pwr.h>
#include <stm32f37x_exti.h>

#define         ID1          (0x1FFFF7AC)
#define         ID2          (0x1FFFF7B0)
#define         ID3          (0x1FFFF7B4)

void Set_System(void);
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);
uint32_t CDC_Send_DATA (uint8_t *ptrBuffer, uint8_t Send_length);
uint32_t CDC_Send_DATAW (unsigned short *ptrBuffer, int Send_length);
uint32_t CDC_Receive_DATA(void);

#endif  /*__HW_CONFIG_H*/
