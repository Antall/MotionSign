#ifndef EFFECT_H
#define EFFECT_H

#include "Sign.h"
#include "Data.h"

class Effect{
  public:
    Effect();
    virtual void run(Sign &sign, Data &data);
};
#endif
