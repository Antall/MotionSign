#ifndef INTERNET_H
#define INTERNET_H

#include "SignData.h"

class Internet {
  public:
    void init();
    void run(SignData &data);

  private:
    unsigned long lastRun;
};

#endif
