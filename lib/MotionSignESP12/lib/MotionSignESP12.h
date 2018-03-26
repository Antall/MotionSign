#ifndef MOTION_SIGN_H
#define MOTION_SIGN_H

#include "Data.h"
#include "SignChip.h"
#include "Internet.h"

class MotionSignESP12{
  public:
    MotionSignESP12();
    void init();
    void run();

  private:
    SignChip signChip;
    Data data;
    Internet internet;
};

#endif
