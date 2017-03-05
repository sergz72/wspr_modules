#! /bin/sh

./serial_download /dev/ttyACM0 dds1 load 8
./serial_download /dev/ttyACM0 dds1 corr 1785
./serial_download /dev/ttyACM0 dds1 freq 0 4996775 -675 1
./serial_download /dev/ttyACM0 dds1 freq 1 45296225 -675 1
./serial_download /dev/ttyACM0 dds1 drive 1 6
