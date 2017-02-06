#include "board.h"
#include <si5351.h>

#define COMMAND_RECORD          1
#define COMMAND_RESET           2
#define COMMAND_SET_CORRECTION  3
#define COMMAND_SET_FREQUENCY   4
#define COMMAND_OUTPUT_CONTROL  5
#define COMMAND_DRIVE_CONTROL   6

typedef struct {
  unsigned char command_id, command_length;
	unsigned short counter;
	unsigned char *buffer_p;
	union {
		unsigned char command_buffer[255];
		struct {
			unsigned short length;
		} record;
		struct {
			unsigned int value;
		} correction;
		struct {
			unsigned int value;
			unsigned char channel;
			unsigned char r_div;
		} freq;
		struct {
			unsigned char value;
			unsigned char channel;
		} control;
	} c;
} Command;

Command command;

void run_command(void)
{
	enum si5351_drive drive;
	
	switch (command.command_id)
	{
		case COMMAND_RECORD:
      serial_send('k');
		  record_length = command.c.record.length * SAMPLE_RATE;
			break;
		case COMMAND_SET_CORRECTION:
      serial_send('k');
		  si5351_set_correction(command.c.correction.value);
			break;
		case COMMAND_SET_FREQUENCY:
			if (command.c.freq.value >= 500000 && command.c.freq.value <= 200000000 && command.c.freq.channel < 8)
			{
        serial_send('k');
		    si5351_set_freq(command.c.freq.value, 0, command.c.freq.channel, command.c.freq.r_div);
			}
			else
        serial_send('e');
			break;
		case COMMAND_OUTPUT_CONTROL:
			if (command.c.control.channel < 8)
			{
        serial_send('k');
		    si5351_clock_enable(command.c.control.channel, command.c.control.value);
			}
			else
        serial_send('e');
			break;
		case COMMAND_DRIVE_CONTROL:
			if (command.c.control.channel < 8)
			{
				switch (command.c.control.value)
				{
					case 2: drive = SI5351_DRIVE_2MA; break;
					case 4: drive = SI5351_DRIVE_2MA; break;
					case 6: drive = SI5351_DRIVE_2MA; break;
					case 8: drive = SI5351_DRIVE_2MA; break;
					default:
            serial_send('e');
					  return;
				}
        serial_send('k');
		    si5351_drive_strength(command.c.control.channel, drive);
			}
			else
        serial_send('e');
			break;
	}
}

void command_processor_init(void)
{
	command.command_id = command.command_length = 0;
}

void process_command(unsigned char c)
{
	if (!command.command_id)
	{
		command.command_id = c;
  	command.buffer_p = command.c.command_buffer;
		switch (c)
		{
			case COMMAND_RECORD:
			case COMMAND_OUTPUT_CONTROL:
			case COMMAND_DRIVE_CONTROL:
				command.command_length = command.counter = 2;
				break;
			case COMMAND_SET_CORRECTION:
				command.command_length = command.counter = 4;
				break;
			case COMMAND_SET_FREQUENCY:
				command.command_length = command.counter = 6;
				break;
			case COMMAND_RESET:
				record_length = 0;
				command.command_id = 0;
				serial_send('k');
				break;
			default:
				command.command_id = 0;
				serial_send('e');
				break;
		}
		return;
	}

	if (!command.command_length)
	{
		command.command_length = command.counter = c;
		return;
	}
	
	*command.buffer_p++ = c;
	if (!--command.counter)
	{
		run_command();
		command_processor_init();
	}
}
