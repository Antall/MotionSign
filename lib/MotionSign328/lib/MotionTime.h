#ifndef MOTION_TIME_H
#define MOTION_TIME_H

#include "Arduino.h"
#include "Effect.h"

class MotionTime : public Effect {
  public:
    MotionTime();
    void run(Sign &sigh, Data &data);

  private:
    unsigned long lastStep;
};

#endif
