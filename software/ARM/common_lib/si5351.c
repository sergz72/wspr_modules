/*
 * si5351.c - Si5351 library for avr-gcc
 *
 * Copyright (C) 2014 Jason Milldrum <milldrum@gmail.com>
 *
 * Some tuning algorithms derived from clk-si5351.c in the Linux kernel.
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Rabeeh Khoury <rabeeh@solid-run.com>
 *
 * rational_best_approximation() derived from lib/rational.c in
 * the Linux kernel.
 * Copyright (C) 2009 emlix GmbH, Oskar Schirmer <oskar@scara.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "board.h"
#include "si5351.h"

/* Define definitions */

#define SI5351_PLL_VCO_MIN					600000000
#define SI5351_PLL_VCO_MAX					900000000
#define SI5351_MULTISYNTH_MIN_FREQ			1000000
#define SI5351_MULTISYNTH_DIVBY4_FREQ		150000000
#define SI5351_MULTISYNTH_MAX_FREQ			160000000
#define SI5351_MULTISYNTH67_MAX_FREQ		SI5351_MULTISYNTH_DIVBY4_FREQ
#define SI5351_CLKOUT_MIN_FREQ				8000
#define SI5351_CLKOUT_MAX_FREQ				SI5351_MULTISYNTH_MAX_FREQ
#define SI5351_CLKOUT67_MAX_FREQ			SI5351_MULTISYNTH67_MAX_FREQ

#define SI5351_PLL_A_MIN					15
#define SI5351_PLL_A_MAX					90
#define SI5351_PLL_B_MAX					(SI5351_PLL_C_MAX-1)
#define SI5351_PLL_C_MAX					1048575
#define SI5351_MULTISYNTH_A_MIN				6
#define SI5351_MULTISYNTH_A_MAX				1800
#define SI5351_MULTISYNTH67_A_MAX			254
#define SI5351_MULTISYNTH_B_MAX				(SI5351_MULTISYNTH_C_MAX-1)
#define SI5351_MULTISYNTH_C_MAX				1048575
#define SI5351_MULTISYNTH_P1_MAX			((1<<18)-1)
#define SI5351_MULTISYNTH_P2_MAX			((1<<20)-1)
#define SI5351_MULTISYNTH_P3_MAX			((1<<20)-1)

#define SI5351_DEVICE_STATUS				0
#define SI5351_INTERRUPT_STATUS				1
#define SI5351_INTERRUPT_MASK				2
#define  SI5351_STATUS_SYS_INIT				(1<<7)
#define  SI5351_STATUS_LOL_B				(1<<6)
#define  SI5351_STATUS_LOL_A				(1<<5)
#define  SI5351_STATUS_LOS					(1<<4)
#define SI5351_OUTPUT_ENABLE_CTRL			3
#define SI5351_OEB_PIN_ENABLE_CTRL			9
#define SI5351_PLL_INPUT_SOURCE				15
#define  SI5351_CLKIN_DIV_MASK				(3<<6)
#define  SI5351_CLKIN_DIV_1					(0<<6)
#define  SI5351_CLKIN_DIV_2					(1<<6)
#define  SI5351_CLKIN_DIV_4					(2<<6)
#define  SI5351_CLKIN_DIV_8					(3<<6)
#define  SI5351_PLLB_SOURCE					(1<<3)
#define  SI5351_PLLA_SOURCE					(1<<2)

#define SI5351_CLK0_CTRL					16
#define SI5351_CLK1_CTRL					17
#define SI5351_CLK2_CTRL					18
#define SI5351_CLK3_CTRL					19
#define SI5351_CLK4_CTRL					20
#define SI5351_CLK5_CTRL					21
#define SI5351_CLK6_CTRL					22
#define SI5351_CLK7_CTRL					23
#define  SI5351_CLK_POWERDOWN				(1<<7)
#define  SI5351_CLK_INTEGER_MODE			(1<<6)
#define  SI5351_CLK_PLL_SELECT				(1<<5)
#define  SI5351_CLK_INVERT					(1<<4)
#define  SI5351_CLK_INPUT_MASK				(3<<2)
#define  SI5351_CLK_INPUT_XTAL				(0<<2)
#define  SI5351_CLK_INPUT_CLKIN				(1<<2)
#define  SI5351_CLK_INPUT_MULTISYNTH_0_4	(2<<2)
#define  SI5351_CLK_INPUT_MULTISYNTH_N		(3<<2)
#define  SI5351_CLK_DRIVE_STRENGTH_MASK		(3<<0)
#define  SI5351_CLK_DRIVE_STRENGTH_2MA		(0<<0)
#define  SI5351_CLK_DRIVE_STRENGTH_4MA		(1<<0)
#define  SI5351_CLK_DRIVE_STRENGTH_6MA		(2<<0)
#define  SI5351_CLK_DRIVE_STRENGTH_8MA		(3<<0)

#define SI5351_CLK3_0_DISABLE_STATE			24
#define SI5351_CLK7_4_DISABLE_STATE			25
#define  SI5351_CLK_DISABLE_STATE_MASK		3
#define  SI5351_CLK_DISABLE_STATE_LOW		0
#define  SI5351_CLK_DISABLE_STATE_HIGH		1
#define  SI5351_CLK_DISABLE_STATE_FLOAT		2
#define  SI5351_CLK_DISABLE_STATE_NEVER		3

#define SI5351_PARAMETERS_LENGTH			8
#define SI5351_PLLA_PARAMETERS				26
#define SI5351_PLLB_PARAMETERS				34
#define SI5351_CLK0_PARAMETERS				42
#define SI5351_CLK1_PARAMETERS				50
#define SI5351_CLK2_PARAMETERS				58
#define SI5351_CLK3_PARAMETERS				66
#define SI5351_CLK4_PARAMETERS				74
#define SI5351_CLK5_PARAMETERS				82
#define SI5351_CLK6_PARAMETERS				90
#define SI5351_CLK7_PARAMETERS				91
#define SI5351_CLK6_7_OUTPUT_DIVIDER		92
#define  SI5351_OUTPUT_CLK_DIV_MASK			(7 << 4)
#define  SI5351_OUTPUT_CLK6_DIV_MASK		(7 << 0)
#define  SI5351_OUTPUT_CLK_DIV_SHIFT		4
#define  SI5351_OUTPUT_CLK_DIV6_SHIFT		0
#define  SI5351_OUTPUT_CLK_DIV_1			0
#define  SI5351_OUTPUT_CLK_DIV_2			1
#define  SI5351_OUTPUT_CLK_DIV_4			2
#define  SI5351_OUTPUT_CLK_DIV_8			3
#define  SI5351_OUTPUT_CLK_DIV_16			4
#define  SI5351_OUTPUT_CLK_DIV_32			5
#define  SI5351_OUTPUT_CLK_DIV_64			6
#define  SI5351_OUTPUT_CLK_DIV_128			7
#define  SI5351_OUTPUT_CLK_DIVBY4			(3<<2)

#define SI5351_SSC_PARAM0					149
#define SI5351_SSC_PARAM1					150
#define SI5351_SSC_PARAM2					151
#define SI5351_SSC_PARAM3					152
#define SI5351_SSC_PARAM4					153
#define SI5351_SSC_PARAM5					154
#define SI5351_SSC_PARAM6					155
#define SI5351_SSC_PARAM7					156
#define SI5351_SSC_PARAM8					157
#define SI5351_SSC_PARAM9					158
#define SI5351_SSC_PARAM10					159
#define SI5351_SSC_PARAM11					160
#define SI5351_SSC_PARAM12					161

#define SI5351_VXCO_PARAMETERS_LOW			162
#define SI5351_VXCO_PARAMETERS_MID			163
#define SI5351_VXCO_PARAMETERS_HIGH			164

#define SI5351_CLK0_PHASE_OFFSET			165
#define SI5351_CLK1_PHASE_OFFSET			166
#define SI5351_CLK2_PHASE_OFFSET			167
#define SI5351_CLK3_PHASE_OFFSET			168
#define SI5351_CLK4_PHASE_OFFSET			169
#define SI5351_CLK5_PHASE_OFFSET			170

#define SI5351_PLL_RESET					177
#define  SI5351_PLL_RESET_B				(1<<7)
#define  SI5351_PLL_RESET_A				(1<<5)

#define  SI5351_CRYSTAL_LOAD_MASK		(3<<6)

#define SI5351_FANOUT_ENABLE			187
#define  SI5351_CLKIN_ENABLE			(1<<7)
#define  SI5351_XTAL_ENABLE				(1<<6)
#define  SI5351_MULTISYNTH_ENABLE		(1<<4)

/* Struct definitions */

struct Si5351RegSet
{
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;
};

struct Si5351Status
{
	uint8_t SYS_INIT;
	uint8_t LOL_B;
	uint8_t LOL_A;
	uint8_t LOS;
	uint8_t REVID;
};

struct Si5351IntStatus
{
	uint8_t SYS_INIT_STKY;
	uint8_t LOL_B_STKY;
	uint8_t LOL_A_STKY;
	uint8_t LOS_STKY;
};

/* Suggested private function prototypes */

void rational_best_approximation(
        unsigned int, unsigned int,
        unsigned int, unsigned int,
        unsigned int *, unsigned int *);
uint32_t pll_calc(uint32_t, struct Si5351RegSet *, int32_t);
uint32_t multisynth_calc(uint32_t, struct Si5351RegSet *);
uint32_t multisynth_recalc(uint32_t, uint32_t, struct Si5351RegSet *);
int si5351_update_sys_status(int channel, struct Si5351Status *);
int si5351_update_int_status(int channel, struct Si5351IntStatus *);
int si5351_set_ms_source(int channel, enum si5351_clock, enum si5351_pll);
				
int32_t ref_correction[SI5351_CHANNELS];
uint32_t plla_freq[SI5351_CHANNELS];
uint32_t pllb_freq[SI5351_CHANNELS];

struct Si5351Status dev_status;
struct Si5351IntStatus dev_int_status;

/******************************/
/* Suggested public functions */
/******************************/

/*
 * si5351_init(void)
 *
 * Call this to initialize I2C communications and get the
 * Si5351 ready for use.
 */
void si5351_init(void)
{
	int i;
	
	for (i = 0; i < SI5351_CHANNELS; i++)
	{
		/* Store the correction factor */
		ref_correction[i] = 0;
		plla_freq[i] = pllb_freq[i] = 0;
	}
}

/*
 * si5351_set_freq(uint32_t freq, uint32_t pll_freq, enum si5351_clock output)
 *
 * Sets the clock frequency of the specified CLK output
 *
 * freq - Output frequency in Hz
 * pll_freq - Frequency of the PLL driving the Multisynth
 *   Use a 0 to have the function choose a PLL frequency
 * clk - Clock output
 *   (use the si5351_clock enum)
 */
int si5351_set_freq(int channel, uint32_t freq, int pll_freq, enum si5351_clock clk, unsigned int r_div)
{
	struct Si5351RegSet ms_reg, pll_reg;
	enum si5351_pll target_pll;
	uint8_t params[30];
	uint32_t i, calc_pll;
	uint8_t temp;
	unsigned char rdiv = 0;
	
	r_div >>= 1;
	while (r_div)
	{
		rdiv += 16;
  	r_div >>= 1;
	}
	
	/* Calculate the synth parameters */
	/* If pll_freq is 0, let the algorithm pick a PLL frequency */
	if (pll_freq == 0)
	{
		calc_pll = 1;
		pll_freq = multisynth_calc(freq, &ms_reg);
	}
	/* TODO: bounds checking */
	else if (pll_freq < 0)
	{
		pll_freq = -pll_freq;
		calc_pll = 1;
		multisynth_recalc(freq, pll_freq, &ms_reg);
	}
	else
	{
		calc_pll = 0;
		multisynth_recalc(freq, pll_freq, &ms_reg);
	}

	/* Determine which PLL to use */
	/* CLK0 gets PLLA, CLK1 gets PLLB */
	/* CLK2 gets PLLB if necessary */
	/* Only good for Si5351A3 variant at the moment */
	if(clk == SI5351_CLK0)
	{
		target_pll = SI5351_PLLA;
		plla_freq[channel] = pll_freq;
	}
	else if(clk == SI5351_CLK1)
	{
		target_pll = SI5351_PLLB;
		pllb_freq[channel] = pll_freq;
	}
	else
	{
		/* need to account for CLK2 set before CLK1 */
		if(pllb_freq[channel] == 0)
		{
			target_pll = SI5351_PLLB;
			pllb_freq[channel] = pll_freq;
		}
		else
		{
			target_pll = SI5351_PLLB;
			pll_freq = pllb_freq[channel];
			multisynth_recalc(freq, pll_freq, &ms_reg);
		}
	}

	/* PLL parameters first */
	if (calc_pll)
	{
  	pll_calc(pll_freq, &pll_reg, ref_correction[channel]);

  	i = 0;

		/* Registers 26-27 */
		temp = ((pll_reg.p3 >> 8) & 0xFF);
		params[i++] = temp;

		temp = (uint8_t)(pll_reg.p3  & 0xFF);
		params[i++] = temp;

		/* Register 28 */
		temp = (uint8_t)((pll_reg.p1 >> 16) & 0x03);
		params[i++] = temp;

		/* Registers 29-30 */
		temp = (uint8_t)((pll_reg.p1 >> 8) & 0xFF);
		params[i++] = temp;

		temp = (uint8_t)(pll_reg.p1  & 0xFF);
		params[i++] = temp;

		/* Register 31 */
		temp = (uint8_t)((pll_reg.p3 >> 12) & 0xF0);
		temp += (uint8_t)((pll_reg.p2 >> 16) & 0x0F);
		params[i++] = temp;

		/* Registers 32-33 */
		temp = (uint8_t)((pll_reg.p2 >> 8) & 0xFF);
		params[i++] = temp;

		temp = (uint8_t)(pll_reg.p2  & 0xFF);
		params[i++] = temp;

		/* Write the parameters */
		if(target_pll == SI5351_PLLA)
		{
			if (si5351_write_bulk(channel, SI5351_PLLA_PARAMETERS, i + 1, params))
				return 1;
		}
		else if(target_pll == SI5351_PLLB)
		{
			if (si5351_write_bulk(channel, SI5351_PLLB_PARAMETERS, i + 1, params))
				return 1;
		}
	}

	i = 0;

	/* Registers 42-43 */
	temp = (uint8_t)((ms_reg.p3 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(ms_reg.p3  & 0xFF);
	params[i++] = temp;

	/* Register 44 */
	temp = (uint8_t)(((ms_reg.p1 >> 16) & 0x03) | rdiv);
	params[i++] = temp;

	/* Registers 45-46 */
	temp = (uint8_t)((ms_reg.p1 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(ms_reg.p1  & 0xFF);
	params[i++] = temp;

	/* Register 47 */
	temp = (uint8_t)((ms_reg.p3 >> 12) & 0xF0);
	temp += (uint8_t)((ms_reg.p2 >> 16) & 0x0F);
	params[i++] = temp;

	/* Registers 48-49 */
	temp = (uint8_t)((ms_reg.p2 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(ms_reg.p2  & 0xFF);
	params[i++] = temp;

	/* Write the parameters */
	switch(clk)
	{
		case SI5351_CLK0:
			if (si5351_write_bulk(channel, SI5351_CLK0_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK1:
			if (si5351_write_bulk(channel, SI5351_CLK1_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK2:
			if (si5351_write_bulk(channel, SI5351_CLK2_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK3:
			if (si5351_write_bulk(channel, SI5351_CLK3_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK4:
			if (si5351_write_bulk(channel, SI5351_CLK4_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK5:
			if (si5351_write_bulk(channel, SI5351_CLK5_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK6:
			if (si5351_write_bulk(channel, SI5351_CLK6_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
		case SI5351_CLK7:
			if (si5351_write_bulk(channel, SI5351_CLK7_PARAMETERS, i + 1, params))
				return 1;
			return si5351_set_ms_source(channel, clk, target_pll);
	}
	
	return 1;
}

/*
 * si5351_set_pll(uint32_t pll_freq, enum si5351_pll target_pll)
 *
 * Set the specified PLL to a specific oscillation frequency
 *
 * pll_freq - Desired PLL frequency
 * target_pll - Which PLL to set
 *     (use the si5351_pll enum)
 */
int si5351_set_pll(int channel, uint32_t pll_freq, enum si5351_pll target_pll)
{
	struct Si5351RegSet pll_reg;
	uint8_t params[30];
	uint32_t i;
	uint8_t temp;
	
	pll_calc(pll_freq, &pll_reg, ref_correction[channel]);

	/* Derive the register values to write */

  i = 0;

	/* Registers 26-27 */
	temp = ((pll_reg.p3 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(pll_reg.p3  & 0xFF);
	params[i++] = temp;

	/* Register 28 */
	temp = (uint8_t)((pll_reg.p1 >> 16) & 0x03);
	params[i++] = temp;

	/* Registers 29-30 */
	temp = (uint8_t)((pll_reg.p1 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(pll_reg.p1  & 0xFF);
	params[i++] = temp;

	/* Register 31 */
	temp = (uint8_t)((pll_reg.p3 >> 12) & 0xF0);
	temp += (uint8_t)((pll_reg.p2 >> 16) & 0x0F);
	params[i++] = temp;

	/* Registers 32-33 */
	temp = (uint8_t)((pll_reg.p2 >> 8) & 0xFF);
	params[i++] = temp;

	temp = (uint8_t)(pll_reg.p2  & 0xFF);
	params[i++] = temp;

	/* Write the parameters */
	if(target_pll == SI5351_PLLA)
	{
		return si5351_write_bulk(channel, SI5351_PLLA_PARAMETERS, i + 1, params);
	}
	else if(target_pll == SI5351_PLLB)
	{
		return si5351_write_bulk(channel, SI5351_PLLB_PARAMETERS, i + 1, params);
	}
	
	return 1;
}

/*
 * si5351_clock_enable(enum si5351_clock clk, uint8_t enable)
 *
 * Enable or disable a chosen clock
 * clk - Clock output
 *   (use the si5351_clock enum)
 * enable - Set to 1 to enable, 0 to disable
 */
int si5351_clock_enable(int channel, enum si5351_clock clk, uint8_t enable)
{
	uint8_t reg_val;

	if(si5351_read(channel, SI5351_OUTPUT_ENABLE_CTRL, &reg_val) != 0)
	{
		return 1;
	}

	if(enable)
	{
		reg_val &= ~(1<<(uint8_t)clk);
	}
	else
	{
		reg_val |= (1<<(uint8_t)clk);
	}

	return si5351_write(channel, SI5351_OUTPUT_ENABLE_CTRL, reg_val);
}

/*
 * si5351_drive_strength(enum si5351_clock clk, enum si5351_drive drive)
 *
 * Sets the drive strength of the specified clock output
 *
 * clk - Clock output
 *   (use the si5351_clock enum)
 * drive - Desired drive level
 *   (use the si5351_drive enum)
 */
int si5351_drive_strength(int channel, enum si5351_clock clk, enum si5351_drive drive)
{
	uint8_t reg_val;
	const uint8_t mask = 0x03;

	if(si5351_read(channel, SI5351_CLK0_CTRL + (uint8_t)clk, &reg_val) != 0)
	{
		return 1;
	}

	switch(drive)
	{
		case SI5351_DRIVE_2MA:
			reg_val &= ~(mask);
			reg_val |= 0x00;
			break;
		case SI5351_DRIVE_4MA:
			reg_val &= ~(mask);
			reg_val |= 0x01;
			break;
		case SI5351_DRIVE_6MA:
			reg_val &= ~(mask);
			reg_val |= 0x02;
			break;
		case SI5351_DRIVE_8MA:
			reg_val &= ~(mask);
			reg_val |= 0x03;
			break;
		default:
			break;
	}

	return si5351_write(channel, SI5351_CLK0_CTRL + (uint8_t)clk, reg_val);
}

/*
 * si5351_update_status(void)
 *
 * Call this to update the status structs, then access them
 * via the dev_status and dev_int_status global variables.
 *
 * See the header file for the struct definitions. These
 * correspond to the flag names for registers 0 and 1 in
 * the Si5351 datasheet.
 */
int si5351_update_status(int channel)
{
	if (si5351_update_sys_status(channel, &dev_status))
		return 1;
	return si5351_update_int_status(channel, &dev_int_status);
}

/*
 * si5351_set_correction(int32_t corr)
 *
 * Use this to set the oscillator correction factor to
 * EEPROM. This value is a signed 32-bit integer of the
 * parts-per-10 million value that the actual oscillation
 * frequency deviates from the specified frequency.
 *
 * The frequency calibration is done as a one-time procedure.
 * Any desired test frequency within the normal range of the
 * Si5351 should be set, then the actual output frequency
 * should be measured as accurately as possible. The
 * difference between the measured and specified frequencies
 * should be calculated in Hertz, then multiplied by 10 in
 * order to get the parts-per-10 million value.
 *
 * Since the Si5351 itself has an intrinsic 0 PPM error, this
 * correction factor is good across the entire tuning range of
 * the Si5351. Once this calibration is done accurately, it
 * should not have to be done again for the same Si5351 and
 * crystal. The library will read the correction factor from
 * EEPROM during initialization for use by the tuning
 * algorithms.
 */
void si5351_set_correction(int channel, int32_t corr)
{
	ref_correction[channel] = corr;
}

/*******************************/
/* Suggested private functions */
/*******************************/

/*
 * Calculate best rational approximation for a given fraction
 * taking into account restricted register size, e.g. to find
 * appropriate values for a pll with 5 bit denominator and
 * 8 bit numerator register fields, trying to set up with a
 * frequency ratio of 3.1415, one would say:
 *
 * rational_best_approximation(31415, 10000,
 *              (1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may look at given_numerator as a fixed point number,
 * with the fractional part size described in given_denominator.
 *
 * for theoretical background, see:
 * http://en.wikipedia.org/wiki/Continued_fraction
 */

void rational_best_approximation(
        unsigned int given_numerator, unsigned int given_denominator,
        unsigned int max_numerator, unsigned int max_denominator,
        unsigned int *best_numerator, unsigned int *best_denominator)
{
	unsigned int n, d, n0, d0, n1, d1;
	n = given_numerator;
	d = given_denominator;
	n0 = d1 = 0;
	n1 = d0 = 1;
	for (;;) {
		unsigned long t, a;
		if ((n1 > max_numerator) || (d1 > max_denominator)) {
			n1 = n0;
			d1 = d0;
			break;
		}
		if (d == 0)
			break;
		t = d;
		a = n / d;
		d = n % d;
		n = t;
		t = n0 + a * n1;
		n0 = n1;
		n1 = t;
		t = d0 + a * d1;
		d0 = d1;
		d1 = t;
	}
	*best_numerator = n1;
	*best_denominator = d1;
}

uint32_t pll_calc(uint32_t freq, struct Si5351RegSet *reg, int32_t correction)
{
	uint32_t ref_freq = SI5351_XTAL_FREQ;
	uint32_t rfrac, denom, a, b, c, p1, p2, p3;
	uint64_t lltmp;

	/* Factor calibration value into nominal crystal frequency */
	/* Measured in parts-per-ten million */
	if (correction > 0)
  	ref_freq += (uint32_t)((unsigned long long)correction * ref_freq / 10000000);
	else if (correction < 0)
	  ref_freq -= (uint32_t)((unsigned long long)-correction * ref_freq / 10000000);

	/* PLL bounds checking */
	if (freq < SI5351_PLL_VCO_MIN)
		freq = SI5351_PLL_VCO_MIN;
	if (freq > SI5351_PLL_VCO_MAX)
		freq = SI5351_PLL_VCO_MAX;

	/* Determine integer part of feedback equation */
	a = freq / ref_freq;

	if (a < SI5351_PLL_A_MIN)
		freq = ref_freq * SI5351_PLL_A_MIN;
	if (a > SI5351_PLL_A_MAX)
		freq = ref_freq * SI5351_PLL_A_MAX;

	/* find best approximation for b/c = fVCO mod fIN */
	denom = 1000L * 1000L;
	lltmp = freq % ref_freq;
	lltmp *= denom;
	rfrac = (uint32_t)(lltmp / ref_freq);

	b = 0;
	c = 1;
	if (rfrac)
		rational_best_approximation(rfrac, denom,
				    SI5351_PLL_B_MAX, SI5351_PLL_C_MAX, &b, &c);

	/* calculate parameters */
	p3  = c;
	p2  = (128 * b) % c;
	p1  = 128 * a;
	p1 += (128 * b / c);
	p1 -= 512;

	/* recalculate rate by fIN * (a + b/c) */
	lltmp  = ref_freq;
	lltmp *= b;

	freq  = (uint32_t)(lltmp / c);
	freq += ref_freq * a;

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	return freq;
}

uint32_t multisynth_calc(uint32_t freq, struct Si5351RegSet *reg)
{
	uint32_t pll_freq;
	uint64_t lltmp;
	uint32_t a, b, c, p1, p2, p3;
	uint8_t divby4;

	/* Multisynth bounds checking */
	if (freq > SI5351_MULTISYNTH_MAX_FREQ)
		freq = SI5351_MULTISYNTH_MAX_FREQ;
	if (freq < SI5351_MULTISYNTH_MIN_FREQ)
		freq = SI5351_MULTISYNTH_MIN_FREQ;

	divby4 = 0;
	if (freq > SI5351_MULTISYNTH_DIVBY4_FREQ)
		divby4 = 1;

	/* Find largest integer divider for max */
	/* VCO frequency and given target frequency */
	if (divby4 == 0)
		a = SI5351_PLL_VCO_MAX / freq;
	else
		a = 4;

	b = 0;
	c = 1;
	pll_freq = a * freq;

	/* Recalculate output frequency by fOUT = fIN / (a + b/c) */
	lltmp  = pll_freq;
	lltmp *= c;
	freq  = (unsigned long)(lltmp / (a * c + b));

	/* Calculate parameters */
	if (divby4)
	{
		p3 = 1;
		p2 = 0;
		p1 = 0;
	}
	else
	{
		p3  = c;
		p2  = (128 * b) % c;
		p1  = 128 * a;
		p1 += (128 * b / c);
		p1 -= 512;
	}

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	return pll_freq;
}

uint32_t multisynth_recalc(uint32_t freq, uint32_t pll_freq, struct Si5351RegSet *reg)
{
	uint64_t lltmp;
	uint32_t rfrac, denom, a, b, c, p1, p2, p3;
	uint8_t divby4;

	/* Multisynth bounds checking */
	if (freq > SI5351_MULTISYNTH_MAX_FREQ)
		freq = SI5351_MULTISYNTH_MAX_FREQ;
	if (freq < SI5351_MULTISYNTH_MIN_FREQ)
		freq = SI5351_MULTISYNTH_MIN_FREQ;

	divby4 = 0;
	if (freq > SI5351_MULTISYNTH_DIVBY4_FREQ)
		divby4 = 1;

	/* Determine integer part of feedback equation */
	a = pll_freq / freq;

	/* TODO: not sure this is correct */
	if (a < SI5351_MULTISYNTH_A_MIN)
		freq = pll_freq / SI5351_MULTISYNTH_A_MIN;
	if (a > SI5351_MULTISYNTH_A_MAX)
		freq = pll_freq / SI5351_MULTISYNTH_A_MAX;

	/* find best approximation for b/c */
	denom = 1000L * 1000L;
	lltmp = pll_freq % freq;
	lltmp *= denom;
	rfrac = (uint32_t)(lltmp / freq);

	b = 0;
	c = 1;
	if (rfrac)
		rational_best_approximation(rfrac, denom,
				    SI5351_MULTISYNTH_B_MAX, SI5351_MULTISYNTH_C_MAX, &b, &c);

	/* Recalculate output frequency by fOUT = fIN / (a + b/c) */
	lltmp  = pll_freq;
	lltmp *= c;
	freq  = (unsigned long)(lltmp / (a * c + b));

	/* Calculate parameters */
	if (divby4)
	{
		p3 = 1;
		p2 = 0;
		p1 = 0;
	}
	else
	{
		p3  = c;
		p2  = (128 * b) % c;
		p1  = 128 * a;
		p1 += (128 * b / c);
		p1 -= 512;
	}

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	return freq;
}

int si5351_update_sys_status(int channel, struct Si5351Status *status)
{
	uint8_t reg_val = 0;

	if(si5351_read(channel, SI5351_DEVICE_STATUS, &reg_val) != 0)
	{
		return 1;
	}

	/* Parse the register */
	status->SYS_INIT = (reg_val >> 7) & 0x01;
	status->LOL_B = (reg_val >> 6) & 0x01;
	status->LOL_A = (reg_val >> 5) & 0x01;
	status->LOS = (reg_val >> 4) & 0x01;
	status->REVID = reg_val & 0x03;
	
	return 0;
}

int si5351_update_int_status(int channel, struct Si5351IntStatus *int_status)
{
	uint8_t reg_val = 0;

	if(si5351_read(channel, SI5351_DEVICE_STATUS, &reg_val) != 0)
	{
		return 1;
	}

	/* Parse the register */
	int_status->SYS_INIT_STKY = (reg_val >> 7) & 0x01;
	int_status->LOL_B_STKY = (reg_val >> 6) & 0x01;
	int_status->LOL_A_STKY = (reg_val >> 5) & 0x01;
	int_status->LOS_STKY = (reg_val >> 4) & 0x01;

	return 0;
}

int si5351_set_ms_source(int channel, enum si5351_clock clk, enum si5351_pll pll)
{
	uint8_t reg_val = 0x0c;
	uint8_t reg_val2;

	if(si5351_read(channel, SI5351_CLK0_CTRL + (uint8_t)clk, &reg_val2) != 0)
	{
		return 1;
	}

	if(pll == SI5351_PLLA)
	{
		reg_val &= ~(SI5351_CLK_PLL_SELECT);
	}
	else if(pll == SI5351_PLLB)
	{
		reg_val |= SI5351_CLK_PLL_SELECT;
	}
	return si5351_write(channel, SI5351_CLK0_CTRL + (uint8_t)clk, reg_val);
}
