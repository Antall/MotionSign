#include "Sign.h"

void Sign::init(){
  for(uint8_t i = 0; i< LED_COUNT; i++){
      Pixel* pixel = &pixels[i];
  }
}

void Sign::black(){
  for(uint8_t i = 0; i<LED_COUNT; i++){
    Pixel *pixel = &pixels[i];
    pixel->hsv.val = 0;
  }
}

void Sign::setHSV(uint16_t h, uint8_t s, uint8_t v){
  ColorHSV color = ColorHSV(h, s, v);
  this->setColor(color);
}

void Sign::setColor(ColorHSV color){
  for(uint8_t i=0; i<LED_COUNT; i++){
    Pixel *pixel = this->pixel(i);
    pixel->hsv = color;
  }
}

void Sign::setColor(ColorHSV color, uint8_t x){
  for(uint8_t j=0; j<LED_HEIGHT; j++){
    Pixel* pixel = this->pixel(x,j);
    pixel->hsv = color;
  }
}

void Sign::pushRight(ColorHSV color){
  for(uint8_t j=0; j<LED_HEIGHT; j++){
    for(int8_t i=LED_WIDTH-2; i>=0; i--){
      Pixel* rightPixel = this->pixel(i+1,j);
      Pixel* leftPixel = this->pixel(i,j);
      rightPixel->setFrom(leftPixel);
    }
    Pixel* firstPixel = this->pixel(0,j);
    firstPixel->hsv = color;
  }
}

Pixel* Sign::pixel(uint8_t index){
  uint8_t x = ledXY[index][0];
  uint8_t y = ledXY[index][1];
  return &pixels[LED_HEIGHT*x+y];
}

Pixel* Sign::pixel(uint8_t x, uint8_t y){
  if(x > LED_WIDTH && x < 128){ x = LED_WIDTH-1; }
  else if( x > LED_WIDTH){ x = 0; }

  if(y > LED_HEIGHT && y < 128){ y = LED_HEIGHT-1; }
  else if( y > LED_HEIGHT){ y = 0; }

  return &pixels[LED_HEIGHT*x+y];
}

