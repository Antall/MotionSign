#ifndef INDICATOR
#define INDICATOR

#include "Data.h"
#include "ColorHSV.h"

class Indicator {

  public:
    void init();
    void run(Data &data);
    ColorHSV getColor();

  private:
    unsigned long lastStrobe;
    unsigned long lastRun;
    uint16_t hue;
    bool isOn;

    void update(Data &data);

};

#endif
