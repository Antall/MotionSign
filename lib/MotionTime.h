#ifndef MOTION_TIME_H
#define MOTION_TIME_H

#include "Arduino.h"
#include "Effect.h"

class MotionTime : public Effect {
  public:
    MotionTime();
    void run(Sign &sigh, SignData &data);

  private:
    unsigned long lastStep;
    uint16_t currMotion;
    uint16_t maxMotion;
    uint16_t minMotion;
};

#endif
