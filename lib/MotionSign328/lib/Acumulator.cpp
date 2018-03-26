#include "Acumulator.h"

Acumulator::Acumulator(){
  lastStep = 0;
  lastNudge = 0;
  this->resetPts();
}

void Acumulator::resetPts(){
  nextPt = 0;
  lastPixel = millis();
  for(uint8_t i=0; i<LED_WIDTH; i++){
    pts[i] = -2;
  }
}

void Acumulator::checkNudge(SignData &data, unsigned long currMillis){
  if(currMillis - lastNudge < 200){ return; }
  lastNudge = currMillis;
  data.motion.nudgeMax();
}

void Acumulator::run(Sign &sign, SignData &data){
  unsigned long currMillis = millis();
  this->checkNudge(data, currMillis);

  const unsigned long STEP_TIME = 60;

  if(currMillis - lastStep < STEP_TIME){ return; }
  lastStep = currMillis;

  uint16_t pixelStep = TIME_OUT / LED_WIDTH;

  if( data.motion.isMotion() ){
    this->resetPts();
  }else if( currMillis - lastPixel > pixelStep ){
    lastPixel = currMillis;
    pts[nextPt] = -1;
    nextPt++;
  }
  this->pushMotion(sign, data);

  //Calculate point locations
  for(uint8_t i=0; i<LED_WIDTH; i++){
    if(pts[i] <= -2){ continue; }
    if(pts[i] < LED_WIDTH-1-i ){ pts[i]++; }
  }

  //Color Green
  uint16_t hue = data.isReserved ? HUE_BLUE : HUE_GREEN;
  ColorHSV color = ColorHSV(hue, 0xFF, 0xFF);
  for(uint8_t i=0; i<LED_WIDTH; i++){
    if(pts[i] >= 0){
      sign.setColor(color, pts[i]);
    }
  }
}

void Acumulator::pushMotion(Sign &sign, SignData &data){
    uint8_t value = data.motion.avgMap(10, 0xFF);
    uint16_t hue = data.motion.avgMapU16(0,0xFFFF) - 0x6D00;
    ColorHSV color = ColorHSV(hue, 0xFF, 0xFF);
    sign.pushRight(color);
}

