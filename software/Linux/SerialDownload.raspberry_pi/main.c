#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "wave_writer.h"

int set_interface_attribs (int fd, int speed, int parity)
{
  struct termios tty;

  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0)
  {
    fprintf(stderr, "error %d from tcgetattr.\n", errno);
    return -1;
  }

  if (cfsetospeed (&tty, speed))
  {
    fprintf(stderr, "error %d from cfsetospeed.\n", errno);
    return -1;
  }
  if (cfsetispeed (&tty, speed))
  {
    fprintf(stderr, "error %d from cfsetispeed.\n", errno);
    return -1;
  }

  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
  // disable IGNBRK for mismatched speed tests; otherwise receive break
  // as \000 chars
  tty.c_iflag &= ~IGNBRK;         // disable break processing
  tty.c_lflag = 0;                // no signaling chars, no echo,
                                  // no canonical processing
  tty.c_oflag = 0;                // no remapping, no delays
  tty.c_cc[VMIN]  = 0;            // read doesn't block
  tty.c_cc[VTIME] = 0;            // no read timeout

  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

  tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CRTSCTS;

  if (tcsetattr (fd, TCSANOW, &tty) != 0)
  {
    fprintf(stderr, "error %d from tcsetattr.\n", errno);
    return -1;
  }
  return 0;
}

void usage(void)
{
  puts("Usage: serial_download device_name length out_file_name1 out_file_name2 out_file_name3");
  puts("OR");
  puts("       serial_download device_name dds[123] dds_parameters");
}

int set_corr(int fd, int channel, int value)
{
  unsigned char message[6];
  int n;
  
  message[0] = 3;
  message[1] = value & 0xFF;
  message[2] = (value >> 8) & 0xFF;
  message[3] = (value >> 16) & 0xFF;
  message[4] = value >> 24;
  message[5] = channel;

  write (fd, message, 6);

  usleep(100000);
  n = read (fd, message, 1);
  
  return n != 1 || message[0] != 'k';
}

int set_freq(int fd, int channel, int output, int freq, short pll_freq, int r_div)
{
  unsigned char message[10];
  int n;
  
  message[0] = 4;
  message[1] = freq & 0xFF;
  message[2] = (freq >> 8) & 0xFF;
  message[3] = (freq >> 16) & 0xFF;
  message[4] = freq >> 24;
  message[5] = pll_freq & 0xFF;
  message[6] = (pll_freq >> 8) & 0xFF;
  message[7] = channel;
  message[8] = output;
  message[9] = r_div;

  write (fd, message, 10);

  usleep(100000);
  n = read (fd, message, 1);

//  printf("%d: %c\n", n, message[0]);
  
  return n != 1 || message[0] != 'k';
}

int set_output(int fd, int channel, int output, int value)
{
  unsigned char message[4];
  int n;
  
  message[0] = 5;
  message[1] = value;
  message[2] = channel;
  message[3] = output;

  write (fd, message, 4);

  usleep(100000);
  n = read (fd, message, 1);
  
  return n != 1 || message[0] != 'k';
}

int set_drive(int fd, int channel, int output, int value)
{
  unsigned char message[4];
  int n;
  
  message[0] = 6;
  message[1] = value;
  message[2] = channel;
  message[3] = output;

  write (fd, message, 4);

  usleep(100000);
  n = read (fd, message, 1);
  
  return n != 1 || message[0] != 'k';
}

int set_load(int fd, int channel, int value)
{
  unsigned char message[3];
  int n;
  
  message[0] = 7;
  message[1] = value;
  message[2] = channel;

  write (fd, message, 3);

  usleep(100000);
  n = read (fd, message, 1);
  
  return n != 1 || message[0] != 'k';
}

int set_dds_parameters(int channel, int argc, char** argv, int fd)
{
  int i, value1, value2, value3, value4;
  
  for (i = 3; i < argc; i++)
  {
    if (!strcmp("corr", argv[i]))
    {
      if (argc < i + 2)
      {
        fprintf(stderr, "Too few arguments for corr command.\n");
        return 1;
      }
      value1 = atoi(argv[++i]);
      if (set_corr(fd, channel, value1))
      {
        fprintf(stderr, "Corr command execution error.\n");
        return 1;
      }
    }
    else if (!strcmp("freq", argv[i]))
    {
      if (argc < i + +5)
      {
        fprintf(stderr, "Too few arguments for freq command.\n");
        return 1;
      }
      value1 = atoi(argv[++i]);
      value2 = atoi(argv[++i]);
      value3 = atoi(argv[++i]);
      value4 = atoi(argv[++i]);
      if (set_freq(fd, channel, value1, value2, (short)value3, value4))
      {
        fprintf(stderr, "Freq command execution error.\n");
        return 1;
      }
    }
    else if (!strcmp("out", argv[i]))
    {
      if (argc < i + 3)
      {
        fprintf(stderr, "Too few arguments for out command.\n");
        return 1;
      }
      value1 = atoi(argv[++i]);
      value2 = atoi(argv[++i]);
      if (set_output(fd, channel, value1, value2))
      {
        fprintf(stderr, "Out command execution error.\n");
        return 1;
      }
    }
    else if (!strcmp("drive", argv[i]))
    {
      if (argc < i + 3)
      {
        fprintf(stderr, "Too few arguments for drive command.\n");
        return 1;
      }
      value1 = atoi(argv[++i]);
      value2 = atoi(argv[++i]);
      if (set_drive(fd, channel, value1, value2))
      {
        fprintf(stderr, "Drive command execution error.\n");
        return 1;
      }
    }
    else if (!strcmp("load", argv[i]))
    {
      if (argc < i + 2)
      {
        fprintf(stderr, "Too few arguments for load command.\n");
        return 1;
      }
      value1 = atoi(argv[++i]);
      if (set_load(fd, channel, value1))
      {
        fprintf(stderr, "Load command execution error.\n");
        return 1;
      }
    }
    else
    {
      fprintf(stderr, "Unknown command: %s\n", argv[i]);
      return 1;
    }
  }
  
  return 0;
}

#define SAMPLE_RATE 6000

int main(int argc, char** argv)
{
  unsigned char message[3];
  int length, n, count, scount, fd;
  unsigned char *buffer, *p;
  unsigned short *sbuffer, *sbuffer1, *sbuffer2, *sbuffer3, savg1, savg2, savg3,
                 *sbuffer11, *sbuffer12, *sbuffer13, prev1, prev2, prev3, v;
  unsigned long average1, average2, average3;
  
  if (argc < 4)
  {
    usage();
    return 1;
  }
  
  fd = open(argv[1], O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0)
  {
    fprintf(stderr, "error %d opening %s: %s\n", errno, argv[1], strerror(errno));
    return 1;
  }

  if (set_interface_attribs (fd, B921600, 0) < 0)  // set speed to 921600 bps, 8n1 (no parity)
  {
    fprintf(stderr, "set baud rate error %d: %s\n", errno, strerror(errno));
    close(fd);
    return 1;
  }

  if (!strcmp("dds1", argv[2]))
  {
    n = set_dds_parameters(0, argc, argv, fd);
    close(fd);
    return n;
  }  

  if (!strcmp("dds2", argv[2]))
  {
    n = set_dds_parameters(1, argc, argv, fd);
    close(fd);
    return n;
  }  

  if (!strcmp("dds3", argv[2]))
  {
    n = set_dds_parameters(2, argc, argv, fd);
    close(fd);
    return n;
  }  
  
  if (argc != 6)
  {
    usage();
    return 1;
  }
  
  length = atoi(argv[2]);

  if (!length)
  {
    usage();
    return 1;
  }
  
  
  message[0] = 1;
  message[1] = length & 0xFF;
  message[2] = length >> 8;

  length *= SAMPLE_RATE * 6;
  length++;
  
  buffer = (unsigned char*)malloc(2 * length);
  if (buffer == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    close(fd);
    return 1;
  }
  
  write (fd, message, 3);

  count = 0;
  p = buffer + 1;
  int t = 0;  
  do
  {
    usleep(100000);
    n = read (fd, p, SAMPLE_RATE);
//    printf("n = %d\n", n);
    count += n;
    p += n;
    if (count > length)
      break;
    if (n == 0)
      t++;
  } while (t < 3);

  close(fd);
  
  printf("%d bytes read.\n", count);
  if (count != length)
  {
    free(buffer);
    fprintf(stderr, "Wrong read length. Should be %d.\n", length);
    return 1;
  }

  average1 = average2 = average3 = 0;
  
  sbuffer = (unsigned short*)(buffer + 2);
  count--;
  scount = 0;
  while (count)
  {
    average1 += *sbuffer++;
    average2 += *sbuffer++;
    average3 += *sbuffer++;
    count -= 6;
    scount++;
  }
  
  savg1 = average1 / scount;
  savg2 = average2 / scount;
  savg3 = average3 / scount;
  sbuffer = (unsigned short*)(buffer + 2);
  length = scount * sizeof(short) * 2;
  sbuffer11 = sbuffer1 = (unsigned short*)malloc(length);
  if (sbuffer1 == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    free(buffer);
    return 1;
  }

  sbuffer12 = sbuffer2 = (unsigned short*)malloc(length);
  if (sbuffer2 == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    free(buffer);
    free(sbuffer1);
    return 1;
  }

  sbuffer13 = sbuffer3 = (unsigned short*)malloc(length);
  if (sbuffer3 == NULL)
  {
    fprintf(stderr, "Out of memory.\n");
    free(buffer);
    free(sbuffer1);
    free(sbuffer2);
    return 1;
  }
  
  prev1 = 0x8000;
  prev2 = 0x8000;
  prev3 = 0x8000;
  while (scount--)
  {
    v = *sbuffer++;
    *sbuffer1++ = (v + prev1) / 2 - savg1;
    *sbuffer1++ = v - savg1;
    prev1 = v;

    v = *sbuffer++;
    *sbuffer2++ = (v + prev2) / 2 - savg2;
    *sbuffer2++ = v - savg2;
    prev2 = v;

    v = *sbuffer++;
    *sbuffer3++ = (v + prev3) / 2 - savg3;
    *sbuffer3++ = v - savg3;
    prev3 = v;
  }
  
  create_wave_file(argv[3], SAMPLE_RATE * 2, 1, 2, length, (unsigned char*)sbuffer11);
  create_wave_file(argv[4], SAMPLE_RATE * 2, 1, 2, length, (unsigned char*)sbuffer12);
  create_wave_file(argv[5], SAMPLE_RATE * 2, 1, 2, length, (unsigned char*)sbuffer13);
  
  free(buffer);
  free(sbuffer11);
  free(sbuffer12);
  free(sbuffer13);
  
  return 0;
}

