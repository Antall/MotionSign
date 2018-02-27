#ifndef OFFICE_SIGN_H
#define OFFICE_SIGN_H

#include "OpenPIR.h"
#include "SignData.h"
#include "Effects.h"

class OfficeSign{
  public:
    OfficeSign();
    void init();
    void run();

  private:
    OpenPIR openPIR;
    Effects effects;
    SignData data;
};

#endif
