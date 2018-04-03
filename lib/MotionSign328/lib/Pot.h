#ifndef POT_H
#define POT_H

#include "Data.h"
#include <Adafruit_NeoPixel.h>

class Pot {
  public:
    void init();
    void run(Data &data);

  private:
    unsigned long lastRun;
    Adafruit_NeoPixel strip;
};

#endif


