#ifndef POT_INDICATOR
#define POT_INDICATOR

#include <Adafruit_NeoPixel.h>
#include "Data.h"

class PotIndicator {

  public:
    void init();
    void run(Data &data);

  private:
    Adafruit_NeoPixel strip;
};

#endif
