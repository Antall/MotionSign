#include "MotionTime.h"

MotionTime::MotionTime(){
  lastStep = 0;
}

void MotionTime::run(Sign &sign, Data &data){

  unsigned long currMillis = millis();

  const unsigned long STEP_TIME = 50;

  if(currMillis - lastStep < STEP_TIME){ return; }
  lastStep = currMillis;

  ColorHSV color;
  uint8_t value = data.motion.avgMap(10, 0xFF);
  if(currMillis - data.motion.lastMotion() > TIME_OUT){
    color = ColorHSV(HUE_GREEN, 0xFF, value);
  }else{
    color = ColorHSV(HUE_RED, 0xFF, value);
  }
  sign.pushRight(color);

}
