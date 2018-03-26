#ifndef INTERNET_H
#define INTERNET_H

#include "Data.h"

class Internet {
  public:
    void init();
    void run(Data &data);

  private:
    void getReserved(Data &data);
    void postOccupied(Data &data);
    unsigned long lastRun;
};
#endif
