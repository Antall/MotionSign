#include "Effects.h"
#include "Pixel.h"

const uint8_t INDICATOR_COUNT = 1;

Effects::Effects(){
  this->reset();
  lastRun = 0;
}

void Effects::init(){
  sign.init();
  //strip = Adafruit_WS2801(LED_COUNT, DATA_PIN, CLK_PIN);
  strip = Adafruit_WS2801(LED_COUNT+INDICATOR_COUNT, WS2801_RGB);
  strip.begin();
  strip.show();
}

void Effects::reset(){
  //effect = &noEffect;
  effect = &signEffect;
}

void Effects::run(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun > UPDATE_DURRATION){
    lastRun = currMillis;
    effect -> run(sign, data);
    this -> updateStrip(data);
    strip.show();
    data.motion.resetCurrent();
  }
}

void Effects::updateStrip(Data &data){
  // Set Indicator at begining of string
  uint32_t color = ColorFromHSV(data.indicatorColor);
  for(uint8_t idx = 0; idx<INDICATOR_COUNT; idx++){
    strip.setPixelColor(idx, color);
  }

  // Set rest of string
  for(uint8_t idx = 0; idx<LED_COUNT; idx++){
    Pixel* pixel = sign.pixel(idx);
    strip.setPixelColor(idx+INDICATOR_COUNT, pixel->color());
  }
}
