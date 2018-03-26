#ifndef ACUMULATOR_H
#define ACUMULATOR_H

#include "Arduino.h"
#include "Effect.h"

class Acumulator : public Effect {
  public:
    Acumulator();
    void run(Sign &sigh, SignData &data);

  private:
    void resetPts();
    void pushMotion(Sign &sign, SignData &data);
    void checkNudge(SignData &data, unsigned long millis);

    int8_t pts[LED_WIDTH];
    uint8_t nextPt;

    unsigned long lastStep;
    unsigned long lastPixel;
    unsigned long lastNudge;
};

#endif
