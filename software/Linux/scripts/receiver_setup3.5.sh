#! /bin/sh

./serial_download /dev/ttyACM1 dds2 load 8
./serial_download /dev/ttyACM1 dds2 corr 1725
./serial_download /dev/ttyACM1 dds2 freq 0 1731800 -675 8
./serial_download /dev/ttyACM1 dds2 freq 1 3809075 -675 1
