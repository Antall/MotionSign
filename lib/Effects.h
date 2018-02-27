#ifndef EFFECTS_H
#define EFFECTS_H

#include "Adafruit_WS2801.h"
#include "SolidColor.h"

#define DATA_PIN 11
#define CLK_PIN 13

typedef const enum _EFFECTS {

} EFFECTS;

#include "Effect.h"

const uint8_t UPDATE_DURRATION = 5;

class Effects{
  public:
    Effects();
    void init();
    void run(SignData &data);
    void reset();

  private:
    unsigned long lastRun;
    unsigned long lastStep;

    Sign sign;
    Adafruit_WS2801 strip;

    Effect* effect;
    Effect noEffect;
    SolidColor solidColor;

    void updateStrip();
};
#endif

