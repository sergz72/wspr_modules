#include "board.h"
#include "si5351.h"
#ifdef I2C_SOFT
#include <i2c_soft.h>
#else
#include <stm32f37x_i2c.h>
#endif

void Delayms(int time)
{
  time *= HSE_VALUE / 1000;

  while(time--);
}

#ifdef I2C_SOFT
void Delayus(int time)
{
  time *= HSE_VALUE / 1000000;

  while(time--);
}

uint8_t si5351_write_bulk(uint8_t addr, uint8_t bytes, uint8_t *data)
{
	return i2c_soft_command(SI5351_BUS_BASE_ADDR, &addr, 1, data, bytes, NULL, 0);
}

uint8_t si5351_write(uint8_t addr, uint8_t data)
{
	return i2c_soft_command(SI5351_BUS_BASE_ADDR, &addr, 1, &data, 1, NULL, 0);
}

uint8_t si5351_read(uint8_t addr, uint8_t *data)
{
	return i2c_soft_command(SI5351_BUS_BASE_ADDR, &addr, 1, NULL, 0, data, 1);
}
#else
#define I2C_LONG_TIMEOUT         ((uint32_t)(10 * I2C_FLAG_TIMEOUT))

uint8_t si5351_write_bulk(uint8_t addr, uint8_t bytes, uint8_t *data)
{
	int timeout;
	
  // Test on BUSY Flag 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET)
  {
    if((timeout--) == 0)
			return 1;
  }
	
  // Configure slave address, nbytes, reload and generate start 
  I2C_TransferHandling(I2C1, SI5351_BUS_BASE_ADDR, 1 + bytes, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);

  // Wait until TXIS flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }

  // Send register address 
  I2C_SendData(I2C1, addr);

	while (bytes--)
	{
		// Wait until TXIS flag is set 
		timeout = I2C_LONG_TIMEOUT;
		while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
		{
			if((timeout--) == 0)
				return 1;
		}

		// Send data 
		I2C_SendData(I2C1, *data++);
  }
	
  // Wait until STOPF flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }
  
  // Clear STOPF flag 
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
	
  return 0;
}

uint8_t si5351_write(uint8_t addr, uint8_t data)
{
	int timeout;

  // Test on BUSY Flag 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET)
  {
    if((timeout--) == 0)
			return 1;
  }
	
  // Configure slave address, nbytes, reload and generate start 
  I2C_TransferHandling(I2C1, SI5351_BUS_BASE_ADDR, 2, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);

  // Wait until TXIS flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }

  // Send register address 
  I2C_SendData(I2C1, addr);

  // Wait until TXIS flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }

  // Send data 
  I2C_SendData(I2C1, data);
	
  // Wait until STOPF flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }
  
  // Clear STOPF flag 
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
	
  return 0;
}

uint8_t si5351_read(uint8_t addr, uint8_t *data)
{
	int timeout;
	
  // Test on BUSY Flag 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET)
  {
    if((timeout--) == 0)
			return 1;
  }
	
  // Configure slave address, nbytes, reload and generate start 
  I2C_TransferHandling(I2C1, SI5351_BUS_BASE_ADDR, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);

  // Wait until TXIS flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }

  // Send register address 
  I2C_SendData(I2C1, addr);

  // Wait until TC flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }  

	// Configure slave address, end mode and start condition 
	I2C_TransferHandling(I2C1, SI5351_BUS_BASE_ADDR, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);

	// Wait until RXNE flag is set 
	timeout = I2C_LONG_TIMEOUT;
	while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET)
	{
		if((timeout--) == 0)
			return 1;
	}
	
	// Read data from RXDR 
	*data = I2C_ReceiveData(I2C1);

  // Wait until STOPF flag is set 
  timeout = I2C_LONG_TIMEOUT;
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET)
  {
    if((timeout--) == 0)
			return 1;
  }
  
  // Clear STOPF flag 
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
	
  return 0;
}
#endif
