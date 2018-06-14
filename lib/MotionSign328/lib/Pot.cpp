#include "Pot.h"
#include "Pixel.h"

#define POT_AIN A1
#define POT_INDICATOR_PIN 3

const uint8_t INDICATOR_COUNT = 2;
const unsigned long UPDATE_DURRATION = 5;

void Pot::init(){
  lastRun = 0;
  pinMode(POT_AIN, INPUT);
  pinMode(POT_INDICATOR_PIN, OUTPUT);
  strip = Adafruit_NeoPixel(INDICATOR_COUNT, POT_INDICATOR_PIN, NEO_GRB + NEO_KHZ800);
  strip.begin();
}

void Pot::run(Data &data){

  data.potValue = analogRead(POT_AIN);
  
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_DURRATION){ return; }
  lastRun = currMillis;

  //analogWrite(POT_INDICATOR_PIN, val);
  //digitalWrite(POT_INDICATOR_PIN, isOn );

  //ColorHSV hsv = ColorHSV(HUE_RED, 0xFF, 0xFF);
  uint32_t color = ColorFromHSV(data.indicatorColor);
  //uint32_t color = ColorFromHSV(hsv);

  for(uint8_t i=0; i<INDICATOR_COUNT; i++){
    strip.setPixelColor(i, color);
  }
  strip.show();
}


