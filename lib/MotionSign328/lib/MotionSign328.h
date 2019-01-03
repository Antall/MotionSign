#ifndef MOTION_SIGN_H
#define MOTION_SIGN_H

#include "OpenPIR.h"
#include "Data.h"
#include "Effects.h"
#include "Internet.h"
#include "Pot.h"
#include "Indicator.h"
#include "Switch.h"

#define DOOR_SWITCH_PIN 3

class MotionSign328{
  public:
    MotionSign328();
    void init();
    void run();

  private:

    Switch doorSwitch;
    OpenPIR openPIR;
    Effects effects;
    Data data;
    Internet internet;
    Pot pot;
    Indicator indicator;
};

#endif
