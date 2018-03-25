#ifndef SIGN_DATA_H
#define SIGN_DATA_H

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF

#include "Arduino.h"
#include "Range.h"
#include "Motion.h"

const uint8_t UINT8_MAX_2 = UINT8_MAX/2;
const uint16_t HUE_GREEN = (120*0xFF/360) << 8;
const uint16_t HUE_RED = (0/360) << 8;
const uint16_t HUE_BLUE = (240*0xFF/360) << 8;

struct SignData{
  Motion motion;
};
#endif
