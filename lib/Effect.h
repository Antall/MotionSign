#ifndef EFFECT_H
#define EFFECT_H

#include "Sign.h"
#include "SignData.h"

class Effect{
  public:
    Effect();
    virtual void run(Sign &sign, SignData &data);
};
#endif
