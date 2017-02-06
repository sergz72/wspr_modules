#! /bin/sh

if [ $# -ne 5 ]
then
  echo "Usage: wspr_receiver.sh frequency1(MHz) frequency2(MHz) frequency3(MHz) device_name mode(2 or 15)"
  exit 1
fi

call=UR4UCC
grid=KO50cn
version=1.7.0

wav_folder=wav_files

freq1=$1
freq2=$2
freq3=$3
device=$4
mode=$5
interval=$(($mode * 60))

#echo $device

while true
do
  current_time=$(date +%s)
  next_time=$((($current_time / $interval + 1) * $interval))
  filename1=$next_time\_1.wav
  filename2=$next_time\_2.wav
  filename3=$next_time\_3.wav
  echo Next run: `date -d @$next_time`
  while [ $(date +%s) -lt $next_time ]; do
    sleep 0.1
  done
  ./serial_download $device 114 $wav_folder/$filename1 $wav_folder/$filename2 $wav_folder/$filename3
  if [ $? -ne 0 ]
  then
    echo Serial download failure.
  else
    echo Done!
    ./wspr_decode_and_upload.sh $wav_folder $next_time $call $grid $freq1 $freq2 $freq3 $version $mode &
  fi
done
