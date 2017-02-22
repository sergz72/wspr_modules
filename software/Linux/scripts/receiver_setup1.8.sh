#! /bin/sh

./serial_download /dev/ttyACM1 dds1 load 8
./serial_download /dev/ttyACM1 dds1 corr 1725
./serial_download /dev/ttyACM1 dds1 freq 0 1731900 -675 8
./serial_download /dev/ttyACM1 dds1 freq 1 2053075 -675 1

