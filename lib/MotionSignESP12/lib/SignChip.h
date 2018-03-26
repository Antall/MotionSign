#ifndef SIGN_CHIP_H
#define SIGN_CHIP_H

#include "Data.h"

class SignChip {
  public:
    void init();
    void run(Data &data);

  public:
    unsigned long lastRun;
};

#endif
