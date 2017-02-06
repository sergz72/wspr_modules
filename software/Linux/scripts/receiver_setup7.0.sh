#! /bin/sh

./serial_download /dev/ttyACM0 dds3 load 8
./serial_download /dev/ttyACM0 dds3 corr 1800
./serial_download /dev/ttyACM0 dds3 freq 0 7540075 -675 1
./serial_download /dev/ttyACM0 dds3 freq 1 2005900 -675 4
