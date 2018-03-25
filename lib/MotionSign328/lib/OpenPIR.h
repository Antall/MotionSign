#ifndef OPEN_PIR_H
#define OPEN_PIR_H

#include "SignData.h"

class OpenPIR {
  public:
    void init();
    void run(SignData &data);

  private:
    void getDigital(SignData &data);
    void getAnalog(SignData &data);
};

#endif
