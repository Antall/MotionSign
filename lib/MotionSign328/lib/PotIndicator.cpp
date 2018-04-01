#include "PotIndicator.h"

#define POT_INDICATOR_PIN 2

void PotIndicator::init(){
  strip = Adafruit_NeoPixel(1, POT_INDICATOR_PIN, NEO_GRB + NEO_KHZ800);

}

void PotIndicator::run(Data &data){

}
