#ifndef EFFECTS_H
#define EFFECTS_H

#define USE_SOILD_COLOR 0
#define USE_MOTION_TIME 1

#include "Adafruit_WS2801.h"
#if USE_SOILD_COLOR
  #include "SolidColor.h"
#elif USE_MOTION_TIME
  #include "MotionTime.h"
#endif

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
#if USE_SOILD_COLOR
    SolidColor signEffect;
#elif USE_MOTION_TIME
    MotionTime signEffect;
#endif

    void updateStrip();
};
#endif

