#include "Acumulator.h"

const uint16_t TIME_OUT = 3*60;

Acumulator::Acumulator(){
  lastStep = 0;
  this->resetPts();
}

void Acumulator::resetPts(){
  nextPt = 0;
  for(uint8_t i=0; i<LED_WIDTH; i++){
    pts[i] = -2;
  }
}

void Acumulator::run(Sign &sign, SignData &data){
  unsigned long currMillis = millis();

  const unsigned long STEP_TIME = 50;

  if(currMillis - lastStep < STEP_TIME){ return; }
  lastStep = currMillis;

  ColorHSV color;

  uint16_t pixelStep = TIME_OUT / LED_WIDTH;

  if(currMillis - data.motion.lastMotion() < pixelStep){
    this->resetPts();
  }else if( currMillis - lastPixel > pixelStep ){
    pts[nextPt] = -1;
  }
  this->pushMotion(sign, data);

  //Calculate point locations
  for(uint8_t i=0; i<LED_WIDTH; i++){
    if(pts[i] <= -2){ continue; }
    if(pts[i] < i ){ pts[i]++; }
  }

  //Color Green
  ColorHSV green = ColorHSV(HUE_GREEN, 0xFF, 0xFF);
  for(uint8_t i=0; i<LED_WIDTH; i++){
    if(pts[i] >= 0){
      sign.setColor(green, pts[i]);
    }
  }

}

void Acumulator::pushMotion(Sign &sign, SignData &data){
    uint8_t value = data.motion.avgMap(10, 0xFF);
    ColorHSV color = ColorHSV(HUE_RED, 0xFF, value);
    sign.pushRight(color);
}

