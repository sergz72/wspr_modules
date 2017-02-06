#! /bin/sh

./serial_download /dev/ttyACM0 dds2 load 8
./serial_download /dev/ttyACM0 dds2 corr 1860
./serial_download /dev/ttyACM0 dds2 freq 0 10640175 -675 1
./serial_download /dev/ttyACM0 dds2 freq 1 2005900 -675 4
