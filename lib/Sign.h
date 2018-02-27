#ifndef SIGN_H
#define SIGN_H

#include "Pixel.h"

const uint8_t LED_WIDTH = 7;
const uint8_t LED_COUNT = LED_WIDTH*2;

class Sign{
  public:
    void init();
    void black();
    Pixel* pixel(uint8_t index);
    void setHSV(uint16_t h, uint8_t s, uint8_t v);

  private:
    Pixel pixels[LED_COUNT];
};
#endif
