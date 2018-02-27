#ifndef PIXEL_H
#define PIXEL_H

#include "Arduino.h"
#include "SignData.h"

class Pixel{
  public:
    Pixel();
    uint16_t hue;
    uint8_t saturation;
    uint8_t value;
    uint32_t color();
};
#endif
