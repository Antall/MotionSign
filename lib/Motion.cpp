#include "Motion.h"

Motion::Motion(){
   _isMotion = false;
   lastTime = 0;

   maxRange.max = 0;
   maxRange.min = 0xFFFF;

   this->resetCurrent();
}

void Motion::resetCurrent(){
  currRange.max = 0;
  currRange.min = 0xFFFF;
}

uint16_t Motion::currAvg(){
  return (currRange.max >> 1) + (currRange.min >> 1);
}

uint8_t Motion::avgMap(uint8_t low, uint8_t high){
  uint8_t rtn = map(this->currAvg(), maxRange.min, maxRange.max, low, high);
  return rtn;
}

void Motion::setRangeWithValue(RangeU16 &range, uint16_t value){
  if(value > range.max){
    range.max = value;
  }
  if(value < range.min){
    range.min = value;
  }
}

unsigned long Motion::lastMotion(){
  return lastTime;
}

void Motion::setAnalog(uint16_t newValue){

  this->setRangeWithValue(currRange, newValue);
  this->setRangeWithValue(maxRange, newValue);

}

void Motion::setDigital(bool newValue){
  _isMotion = newValue;

  if (newValue == HIGH){
    lastTime = millis();
  }
}

bool Motion::isMotion(){
  return _isMotion;
}
