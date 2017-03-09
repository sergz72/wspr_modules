#! /bin/sh

./serial_download /dev/ttyACM0 dds1 load 8
./serial_download /dev/ttyACM0 dds1 corr 1818
./serial_download /dev/ttyACM0 dds1 freq 0 4997005 -675 1
./serial_download /dev/ttyACM0 dds1 freq 1 23127595 -675 1
./serial_download /dev/ttyACM0 dds1 drive 1 4
