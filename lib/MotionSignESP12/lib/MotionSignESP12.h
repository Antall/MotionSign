#ifndef MOTION_SIGN_H
#define MOTION_SIGN_H

#include "Data.h"
#include "SignChip.h"
#include "Internet.h"
#include "Display.h"

class MotionSignESP12{
  public:
    MotionSignESP12();
    void init();
    void run();

  private:
    SignChip signChip;
    Data data;
    Internet internet;
    Display display;
};

#endif
