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
#define SI5351_CHANNELS 3

#define I2C_SOFT

#define i2c_dly Delayus(10)
void SCL_HIGH(int c);
void SCL_LOW(int c);
void SDA_HIGH(int c);
void SDA_LOW(int c);
int SDA_IN(int c);

void Delayus(int time);

void Delayms(int time);
void serial_send(unsigned char c);
void serial_sendw(unsigned short s);

void sdadc_start(void);
void timer_enable(void);
void timer_disable(void);

void command_processor_init(void);
void process_command(unsigned char c);

register unsigned int record_length __asm("r9");
register unsigned char *send_buffer_write_p __asm("r11");
register unsigned char *send_buffer_read_p __asm("r10");

#endif
