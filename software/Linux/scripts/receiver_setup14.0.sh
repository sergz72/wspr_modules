#! /bin/sh

./serial_download /dev/ttyACM0 dds1 load 8
./serial_download /dev/ttyACM0 dds1 corr 1855
./serial_download /dev/ttyACM0 dds1 freq 0 14596825 -675 1
./serial_download /dev/ttyACM0 dds1 freq 1 2004900 -675 4
