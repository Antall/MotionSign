#include "Pot.h"
#include "Pixel.h"

#define POT_AIN A1
#define POT_INDICATOR_PIN 2

const uint8_t INDICATOR_COUNT = 1;

void Pot::init(){
  pinMode(POT_AIN, INPUT);
  strip = Adafruit_NeoPixel(INDICATOR_COUNT, POT_INDICATOR_PIN, NEO_GRB + NEO_KHZ800);
}

void Pot::run(Data &data){
  data.potValue = analogRead(POT_AIN);

  uint32_t color = ColorFromHSV(data.indicatorColor);
  for(uint8_t i=0; i<INDICATOR_COUNT; i++){
    strip.setPixelColor(i, color);
  }
}


