#ifndef SWITCH_H
#define SWITCH_H

#include "Arduino.h"

class Switch {
  public:
    Switch();
    void init( uint8_t pin );
    bool value();

  private:
    uint8_t pinID;

};

#endif
