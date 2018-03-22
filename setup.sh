#!/usr/bin/env bash
cd ~/Documents/Arduino
ln -s $(pwd)/OfficeSign/lib $(pwd)/libraries/OfficeSign
cd ~/Documents/Arduino/libraries
git clone git@github.com:adafruit/Adafruit-WS2801-Library.git Adafruit_WS2801
cd ~/Documents
ln -s $(pwd)/Arduino/OfficeSign/eagle $(pwd)/eagle/OfficeSign
echo "Finished"
