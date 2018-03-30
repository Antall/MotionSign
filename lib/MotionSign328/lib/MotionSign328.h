#ifndef MOTION_SIGN_H
#define MOTION_SIGN_H

#include "OpenPIR.h"
#include "Data.h"
#include "Effects.h"
#include "Internet.h"

class MotionSign328{
  public:
    MotionSign328();
    void init();
    void run();

  private:
    OpenPIR openPIR;
    Effects effects;
    Data data;
    Internet internet;
};

#endif
