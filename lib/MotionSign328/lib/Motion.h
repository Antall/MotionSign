#ifndef MOTION_H
#define MOTION_H

#include "Range.h"

class Motion{
  public:
    Motion();
    void setAnalog(uint16_t newValue);
    void setDigital(bool newValue);
    void resetCurrent();
    void nudgeMax();

    bool isMotion();
    bool isTimeOut();
    unsigned long lastMotion();
    uint16_t currAvg();
    uint8_t avgMap(uint8_t low, uint8_t high);
    uint16_t avgMapU16(uint16_t low, uint16_t high);

  private:
    void setRangeWithValue(RangeU16 &range, uint16_t value);

    bool _isMotion;
    unsigned long lastTime;
    unsigned long lastNudge;
    uint16_t lastAnalog;

    RangeU16 quietRange;
    RangeU16 currRange;
    RangeU16 maxRange;
};

#endif
