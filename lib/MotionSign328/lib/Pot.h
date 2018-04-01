#ifndef POT_H
#define POT_H

#include "Data.h"
#include <Adafruit_NeoPixel.h>

class Pot {
  public:
    void init();
    void run(Data &data);

  private:
    Adafruit_NeoPixel strip;

};

#endif


