#include "MotionTime.h"

MotionTime::MotionTime(){
  lastStep = 0;
  currMotion = 0;
  maxMotion = 0;
  minMotion = 0xFFFF;
}

void MotionTime::run(Sign &sign, SignData &data){

  // Update current and max motion
  if( data.analogPIR > currMotion ){
    currMotion = data.analogPIR;
  }
  if( data.analogPIR > maxMotion ){
    maxMotion = data.analogPIR;
  }
  if( data.analogPIR < minMotion ){
    minMotion = data.analogPIR;
  }

  unsigned long currMillis = millis();

  const unsigned long STEP_TIME = 50;

  if(currMillis - lastStep < STEP_TIME){ return; }
  lastStep = currMillis;

  ColorHSV color;
  if(currMillis - data.lastMotion > TIME_OUT){
    color = ColorHSV(HUE_GREEN, 0xFF, 0xFF);
  }else{
    uint8_t value = map(currMotion, minMotion, maxMotion, 10, 0xFF);
    color = ColorHSV(HUE_RED, 0xFF, value);
  }
  sign.pushRight(color);
  currMotion = 0;

}
