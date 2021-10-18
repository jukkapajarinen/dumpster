#!/bin/bash

echo "Bash script to read data from Xiaomi Mi Temp/Hum Sensor V1.";

read -rp "Enter sensor mac address: " mac;
echo "Reading data infinitely. Press [Ctrl+c] to stop."
while true
do
  temp=$(timeout 30 /usr/bin/gatttool -b "$mac" --char-write-req --handle=0x10 -n 0100 --listen 2>&1 | grep -m 1 "Notification" | tail -1 | cut -c 42-54 | xxd -r -p);
  hum=$(timeout 30 /usr/bin/gatttool -b "$mac" --char-write-req --handle=0x10 -n 0100 --listen 2>&1 | grep -m 1 "Notification" | tail -1 | cut -c 64-74 | xxd -r -p);
  bat=$(timeout 30 /usr/bin/gatttool -b "$mac" --char-read --handle=0x18 2>&1 | cut -c 34-35 | tr "[:lower:]" "[:upper:]");
  bat=$(echo "ibase=16;$bat" | bc);
  echo "- Temperature: $temp, Humidity: $hum, Battery: $bat.";
done
