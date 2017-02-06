#include "wave_writer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
  /* RIFF Chunk Descriptor */
  unsigned char       RIFF[4];        // RIFF Header Magic header
  unsigned int        chunkSize;      // RIFF Chunk Size
  unsigned char       WAVE[4];        // WAVE Header
                                      /* "fmt" sub-chunk */
  unsigned char       FMT[4];         // FMT header
  unsigned int        subchunk1Size;  // Size of the fmt chunk
  unsigned short      audioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
  unsigned short      numOfChan;      // Number of channels 1=Mono 2=Sterio
  unsigned int        samplesPerSec;  // Sampling Frequency in Hz
  unsigned int        bytesPerSec;    // bytes per second
  unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo
  unsigned short      bitsPerSample;  // Number of bits per sample
                                      /* "data" sub-chunk */
  unsigned char       subchunk2ID[4]; // "data"  string
  unsigned int        subchunk2Size;  // Sampled data length
} WaveHeader;

int create_wave_file(const char *file_name, int sample_rate, int channels, int data_size, int buffer_size, unsigned char *buffer)
{
  WaveHeader header;
  int fd, rc;
  
  strcpy(header.RIFF, "RIFF");
  strcpy(header.WAVE, "WAVE");
  strcpy(header.FMT, "fmt ");
  strcpy(header.subchunk2ID, "data");
  
  header.chunkSize = 36 + buffer_size;
  header.subchunk1Size = 16;
  header.numOfChan = channels;
  header.samplesPerSec = sample_rate;
  header.bytesPerSec = sample_rate * data_size * channels;
  header.audioFormat = 1; // PCM
  header.blockAlign = data_size * channels;
  header.bitsPerSample = data_size * 8;
  header.subchunk2Size = buffer_size;
  
  fd = open(file_name, O_WRONLY | O_CREAT, 0644);
  if (fd == -1)
  {
    perror ("open");
    return 1;
  }

  rc = write (fd, &header, sizeof(WaveHeader));
  if(rc != sizeof(WaveHeader))
  {
    perror("write");
    close(fd);
    return 1;
  }
  
  rc = write (fd, buffer, buffer_size);
  if(rc != buffer_size)
  {
    perror("write");
    close(fd);
    return 1;
  }
  
  close(fd);
  
  return 0;
}