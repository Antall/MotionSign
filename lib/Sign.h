#ifndef SIGN_H
#define SIGN_H

#include "Pixel.h"

const uint8_t LED_WIDTH = 7;
const uint8_t LED_HEIGHT = 2;
const uint8_t LED_COUNT = LED_WIDTH*LED_HEIGHT;

class Sign{
  public:
    void init();
    void black();
    Pixel* pixel(uint8_t index);
    Pixel* pixel(uint8_t x, uint8_t y);
    void setHSV(uint16_t h, uint8_t s, uint8_t v);
    void setColor(ColorHSV color);
    void pushRight(ColorHSV color);

  private:
    Pixel pixels[LED_COUNT];
    uint8_t ledXY[LED_COUNT][2] = {
      {0,0}, {1,0}, {2,0}, {3,0}, {4,0}, {5,0}, {6,0},
      {6,1}, {5,1}, {4,1}, {3,1}, {2,1}, {1,1}, {0,1},
    };

};
#endif
