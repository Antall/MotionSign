#ifndef OPEN_PIR_H
#define OPEN_PIR_H

#include "Data.h"

class OpenPIR {
  public:
    void init();
    void run(Data &data);

  private:
    void getDigital(Data &data);
    void getAnalog(Data &data);
};

#endif
