#include "Sign.h"

void Sign::init(){
  for(uint8_t i = 0; i< LED_COUNT; i++){
      Pixel* pixel = &pixels[i];
  }
}

void Sign::black(){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    pixel->value = 0;
  }
}

void Sign::setHSV(uint16_t h, uint8_t s, uint8_t v){
  for(uint8_t i; i<LED_COUNT; i++){
    Pixel *pixel = this->pixel(i);
    pixel->hue = h;
    pixel->saturation = s;
    pixel->value = v;
  }
}

Pixel* Sign::pixel(uint8_t index){
  return &pixels[index];
}
