#ifndef WAVE_WRITER_H
#define WAVE_WRITER_H

int create_wave_file(const char *file_name, int sample_rate, int channels, int data_size, int buffer_size, unsigned char *buffer);

#endif /* WAVE_WRITER_H */

