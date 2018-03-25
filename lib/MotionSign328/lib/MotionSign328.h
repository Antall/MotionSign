#ifndef MOTION_SIGN_H
#define MOTION_SIGN_H

#include "OpenPIR.h"
#include "SignData.h"
#include "Effects.h"

class MotionSign328{
  public:
    MotionSign328();
    void init();
    void run();

  private:
    OpenPIR openPIR;
    Effects effects;
    SignData data;
};

#endif
