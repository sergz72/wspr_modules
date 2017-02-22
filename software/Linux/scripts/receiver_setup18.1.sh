#! /bin/sh

./serial_download /dev/ttyACM1 dds3 load 8
./serial_download /dev/ttyACM1 dds3 corr 1910
./serial_download /dev/ttyACM1 dds3 freq 0 13107805 -675 1
./serial_download /dev/ttyACM1 dds3 freq 1 4996795 -675 1
