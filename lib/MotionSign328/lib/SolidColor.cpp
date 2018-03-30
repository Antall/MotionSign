#include "SolidColor.h"

SolidColor::SolidColor(){
  hue = 0x0000;
}

void SolidColor::run(Sign &sign, Data &data){

  unsigned long currMillis = millis();

  hue += 100;

  if(currMillis - data.motion.lastMotion() > TIME_OUT){
    sign.setHSV(HUE_RED, 0xFF,0xFF);
  }else{
    sign.setHSV(hue, 0xFF,0xFF);
    //sign.setHSV(HUE_GREEN, 0xFF,0xFF);
  }

}
