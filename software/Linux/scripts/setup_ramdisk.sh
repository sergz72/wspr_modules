#! /bin/sh

mkdir /mnt/ramdisk/1
mkdir /mnt/ramdisk/1/wav_files
mkdir /mnt/ramdisk/1/decode_out
mkdir /mnt/ramdisk/1/wsprd_out1
mkdir /mnt/ramdisk/1/wsprd_out2
mkdir /mnt/ramdisk/1/wsprd_out3
cp *.sh serial_download wsprupload wsprd /mnt/ramdisk/1

mkdir /mnt/ramdisk/2
mkdir /mnt/ramdisk/2/wav_files
mkdir /mnt/ramdisk/2/decode_out
mkdir /mnt/ramdisk/2/wsprd_out1
mkdir /mnt/ramdisk/2/wsprd_out2
mkdir /mnt/ramdisk/2/wsprd_out3
cp *.sh serial_download wsprupload wsprd /mnt/ramdisk/2
