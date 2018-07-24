#include "Motion.h"
#include "Data.h"

Motion::Motion(){
   _isMotion = false;
   lastTime = 0;
   lastNudge = 0;

   maxRange.max = 0;
   maxRange.min = 0xFFFF;

   quietRange.max = 515;
   quietRange.min = 360;

   lastAnalog = 420;

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
  if(maxRange.max > quietRange.max){maxRange.max--;}
  if(maxRange.min < quietRange.min){maxRange.min++;}
}

uint16_t Motion::currAvg(){
  return (currRange.max + currRange.min) >> 1;
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
  Serial.print(currRange.max);
  Serial.print(" ");
  Serial.print(currRange.min);
  Serial.print(" ");
  Serial.print(this->currAvg());
  Serial.print(" ");
  Serial.print(quietRange.max);
  Serial.print(" ");
  Serial.print(quietRange.min);

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
  if(range.max > ANALOG_MAX ){
    range.max = ANALOG_MAX;
  }
}

unsigned long Motion::lastMotion(){
  return lastTime;
}

void Motion::setAnalog(uint16_t newValue){
  lastAnalog = min(newValue, ANALOG_MAX);

  this->setRangeWithValue(currRange, newValue);
  this->setRangeWithValue(maxRange, newValue);

}

void Motion::setDigital(bool newValue){
  _isMotion = newValue;

  if(lastAnalog > quietRange.max || lastAnalog < quietRange.min ){
    _isMotion = true;
  }

  if(_isMotion){
    lastTime = millis();
  }
}

bool Motion::isMotion(){
  return (millis() - lastTime) < IS_MOTION_TIME;
}

bool Motion::isTimeOut(){
  return (millis() - lastTime) > TIME_OUT;
}
