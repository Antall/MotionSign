#include "Effects.h"

Effects::Effects(){
  this->reset();
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip.begin();
  strip.show();
}

void Effects::reset(){
  //effect = &noEffect;
  effect = &solidColor;
}

void Effects::run(SignData &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    effect -> run(sign, data);
    this -> updateStrip();
    strip.show();
  }
}

void Effects::updateStrip(){
  uint8_t offset = 0;
  for(uint8_t idx = offset; idx< LED_COUNT; idx++){
    Pixel* pixel = sign.pixel(idx);
    strip.setPixelColor(idx-offset, pixel->color());
  }
}
