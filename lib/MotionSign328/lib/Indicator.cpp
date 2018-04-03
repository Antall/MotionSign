#include "Indicator.h"

const uint8_t OFF_POT_VALUE = 10;
const uint16_t STROBE_POT_VALUE = 500;

const uint16_t MAX_HUE_SPEED = 0x0100;
const uint8_t MIN_HUE_SPEED = 10;

const uint8_t MAX_STROBE_TIME = 500;
const uint8_t MIN_STROBE_TIME = 50;

const uint8_t UPDATE_DURRATION = 5;

void Indicator::init(){
  lastRun = 0;
  isOn = true;
  hue = 0;
  value = 0xFF;
}

ColorHSV Indicator::getColor(){
  if(isOn){
    return ColorHSV(hue, 0xFF, value);
  }else{
    return ColorHSV(hue, 0xFF, 0);
  }
}

void Indicator::run(Data &data){
  this->update(data);
  data.indicatorColor = this->getColor();
}

void Indicator::update(Data &data){
  Serial.println("HERE");
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_DURRATION){ return; }
  lastRun = currMillis;

  if(data.potValue < OFF_POT_VALUE){
    isOn = false;
    return;
  }
  else if ( data.potValue < 500) {
    isOn = true;
    hue += map(data.potValue, OFF_POT_VALUE, STROBE_POT_VALUE, MIN_HUE_SPEED, MAX_HUE_SPEED);
    value = map(data.potValue, OFF_POT_VALUE, STROBE_POT_VALUE, 20, 0xFF);
  }else{
    hue += MAX_HUE_SPEED;
    value = 0xFF;
    unsigned long strobeTime = map(data.potValue, STROBE_POT_VALUE, ANALOG_MAX, MAX_STROBE_TIME, MIN_STROBE_TIME);
    if( currMillis - lastStrobe > strobeTime){
      lastStrobe = currMillis;
      isOn = !isOn;
    }
  }
}
