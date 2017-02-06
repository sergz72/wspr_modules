#! /bin/sh

./serial_download /dev/ttyACM0 dds1 load 8
./serial_download /dev/ttyACM0 dds1 corr 1725
./serial_download /dev/ttyACM0 dds1 freq 0 1731800 -675 8
./serial_download /dev/ttyACM0 dds1 freq 1 3809075 -675 1
