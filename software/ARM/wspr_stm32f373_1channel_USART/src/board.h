#ifndef BOARD_H
#define BOARD_H

#include <stm32f3xx.h>

#define assert_param(expr)

#define DEBUG
#define NULL 0

#define HSI_VALUE  ((uint32_t)8000000)
#define HSE_VALUE  12000000
#define LSE_VALUE  ((uint32_t)32768)    /*!< Value of the External Low Speed oscillator in Hz */
#define HSE_STARTUP_TIMEOUT  ((uint16_t)0x0500)   /*!< Time out for HSE start up */

#define SYSCLK_VALUE  12000000

#define SAMPLE_RATE 12000

#define TIM3PERIOD (SYSCLK_VALUE / SAMPLE_RATE)

  /* Set the SDADC divider: The SDADC should run @6MHz */
  /* If Sysclk is 12MHz, SDADC divider should be 2 */
#define SDADC_CLK_DIVIDER RCC_SDADCCLK_SYSCLK_Div2

#define SI5351_BUS_BASE_ADDR			0xC0
#define SI5351_XTAL_FREQ					27000000
#define SI5351_PLL_FIXED					900000000

//#define I2C_SOFT

#ifdef I2C_SOFT
#define i2c_dly Delayus(10)
// set PB6
#define SCL_HIGH GPIOB->BSRRL = 0x0040
// clr PB6
#define SCL_LOW GPIOB->BSRRH = 0x0040
// set PB7
#define SDA_HIGH GPIOB->BSRRL = 0x0080
// clr PB7
#define SDA_LOW GPIOB->BSRRH = 0x0080
// read PB7
#define SDA_IN (GPIOB->IDR & 0x80)

void Delayus(int time);
#endif

void Delayms(int time);
void serial_send(unsigned char c);
void serial_sendw(unsigned short s);

void command_processor_init(void);
void process_command(unsigned char c);

extern volatile unsigned int record_length;

#endif
