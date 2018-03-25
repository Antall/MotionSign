#!/usr/bin/env bash
cd ~/Documents/Arduino

# ATMEGA 328 Setup
ln -sf $(pwd)/MotionSign/lib/MotionSign328/lib $(pwd)/libraries/MotionSign328
mkdir -p $(pwd)/MotionSign328
ln -sf $(pwd)/MotionSign/lib/MotionSign328/MotionSign328.ino $(pwd)/MotionSign328/MotionSign328.ino

#ESP-12 Setup
ln -sf $(pwd)/MotionSign/lib/MotionSignESP12/lib $(pwd)/libraries/MotionSignESP12
mkdir -p $(pwd)/MotionSignESP12
ln -sf $(pwd)/MotionSign/lib/MotionSignESP12/MotionSignESP12.ino $(pwd)/MotionSignESP12/MotionSignESP12.ino

cd ~/Documents/Arduino/libraries
git clone git@github.com:adafruit/Adafruit-WS2801-Library.git Adafruit_WS2801
cd ~/Documents
ln -sf $(pwd)/Arduino/MotionSign/eagle $(pwd)/eagle/OfficeSign
echo "Finished"
