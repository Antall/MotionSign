#ifndef PIXEL_H
#define PIXEL_H

#include "Arduino.h"
#include "Data.h"
#include "ColorHSV.h"

class Pixel{
  public:
    Pixel();
    ColorHSV hsv;
    //uint8_t x;
    //uint8_t y;

    uint32_t color();
    void setFrom(Pixel* pixel);
    void set(uint16_t h, uint8_t s, uint8_t v);

};

uint32_t ColorFromHSV(ColorHSV hsv);
#endif
