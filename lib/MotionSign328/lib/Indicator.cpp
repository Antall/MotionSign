#include "Indicator.h"

const uint8_t OFF_POT_VALUE = 10;
const uint16_t STROBE_POT_VALUE = 500;

const uint8_t MAX_HUE_SPEED = 256;
const uint8_t MIN_HUE_SPEED = 10;

const uint8_t MAX_STROBE_TIME = 500;
const uint8_t MIN_STROBE_TIME = 50;

const uint8_t UPDATE_DURRATION = 5;

void Indicator::init(){
  lastRun = 0;
  isOn = true;
  hue = 0;
}

ColorHSV Indicator::getColor(){
  if(isOn){
    return ColorHSV(hue, 0xFF, 0xFF);
  }else{
    return ColorHSV(hue, 0xFF, 0);
  }
}

void Indicator::run(Data &data){
  this->update(data);
  data.indicatorColor = this->getColor();
}

void Indicator::update(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_DURRATION){ return; }
  lastRun = currMillis;

  isOn = true;
  if(data.potValue < OFF_POT_VALUE){
    return;
  }
  else if ( data.potValue < 500) {
    hue += map(data.potValue, OFF_POT_VALUE, STROBE_POT_VALUE, MIN_HUE_SPEED, MAX_HUE_SPEED);
  }else{
    unsigned long strobeTime = map(data.potValue, STROBE_POT_VALUE, ANALOG_MAX, MAX_STROBE_TIME, MIN_STROBE_TIME);
    if( currMillis - lastStrobe > strobeTime){
      isOn = !isOn;
    }
  }
}
