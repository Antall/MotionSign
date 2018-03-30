#ifndef INTERNET_H
#define INTERNET_H

#include "Data.h"

class Internet {
  public:
    void init();
    void run(Data &data);

  private:
    unsigned long lastRun;
};

#endif
