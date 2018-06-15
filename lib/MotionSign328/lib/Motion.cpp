#include "Motion.h"
#include "Data.h"

Motion::Motion(){
   _isMotion = false;
   lastTime = 0;
   lastNudge = 0;

   maxRange.max = 0;
   maxRange.min = 0xFFFF;

   this->resetCurrent();
}

void Motion::resetCurrent(){
  currRange.max = 0;
  currRange.min = 0xFFFF;
}

void Motion::nudgeMax(){
  unsigned long currMillis = millis();
  if(currMillis - lastNudge < (unsigned long)200){ return; }
  lastNudge = currMillis;
  if(maxRange.max > 2){maxRange.max--;}
  if(maxRange.min < 1023){maxRange.min++;}
}

uint16_t Motion::currAvg(){
  return (currRange.max >> 1) + (currRange.min >> 1);
}

uint8_t Motion::avgMap(uint8_t low, uint8_t high){
  return map(this->currAvg(), maxRange.min, maxRange.max, low, high);
}

uint16_t Motion::avgMapU16(uint16_t low, uint16_t high){
#ifdef PRINT_MOTION
  Serial.print(maxRange.max);
  Serial.print(" ");
  Serial.print(maxRange.min);
  Serial.print(" ");
  Serial.print(this->currAvg());
  Serial.print("\n");
#endif
  return map(this->currAvg(), maxRange.min, maxRange.max, low, high);
}

void Motion::setRangeWithValue(RangeU16 &range, uint16_t value){
  if(value > range.max){
    range.max = value;
  }
  if(value < range.min){
    range.min = value;
  }
  if(range.max > 1023 ){
    range.max = 0;
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

bool Motion::isTimeOut(){
  return (millis() - lastTime) > TIME_OUT;
}
