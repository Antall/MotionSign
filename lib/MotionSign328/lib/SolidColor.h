#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "Arduino.h"
#include "Effect.h"

class SolidColor : public Effect {
  public:
    SolidColor();
    void run(Sign &sign, Data &data);
  
  private:
    uint16_t hue;
};

#endif
