#include "Motion.h"

Motion::Motion(){
   _isMotion = false;
   lastTime = 0;

   maxRange.max = 0xFFFF;
   maxRange.min = 0;

   this->resetCurrent();
}

void Motion::resetCurrent(){
   currRange.max = 0xFFFF;
   currRange.min = 0;
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
