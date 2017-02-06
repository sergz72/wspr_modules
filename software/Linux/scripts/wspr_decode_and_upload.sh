#! /bin/sh

if [ $# -ne 9 ]
then
  echo "Usage: wspr_decode_and_upload.sh wav_file_folder timestamp call grid frequency1(MHz) frequency2(MHz) frequency3(MHz) version mode(2 or 15)"
  exit 1
fi

wav_folder=$1
spot_time=$2
call=$3
grid=$4
freq1=$5
freq2=$6
freq3=$7
version=$8
mode=$9

log_file=decode_out/$spot_time.out

mode_option=

if [ $mode = 15 ]; then
  mode_option=-m
fi

./wsprd -f $freq1 -a wsprd_out1 $mode_option $wav_folder/$spot_time\_1.wav >$log_file 2>&1
cat wsprd_out1/wspr_spots.txt
./wsprupload wsprd_out1/wspr_spots.txt $freq1 $spot_time $call $grid $version $mode >>$log_file 2>&1
rm -f $wav_folder/$spot_time\_1.wav

./wsprd -f $freq2 -a wsprd_out2 $mode_option $wav_folder/$spot_time\_2.wav >>$log_file 2>&1
cat wsprd_out2/wspr_spots.txt
./wsprupload wsprd_out2/wspr_spots.txt $freq2 $spot_time $call $grid $version $mode >>$log_file 2>&1
rm -f $wav_folder/$spot_time\_2.wav

./wsprd -f $freq3 -a wsprd_out3 $mode_option $wav_folder/$spot_time\_3.wav >>$log_file 2>&1
cat wsprd_out3/wspr_spots.txt
./wsprupload  wsprd_out3/wspr_spots.txt $freq3 $spot_time $call $grid $version $mode >>$log_file 2>&1
rm -f $wav_folder/$spot_time\_3.wav

sudo rdate -s ntp.time.in.ua

