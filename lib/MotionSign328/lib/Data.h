#ifndef DATA_H
#define DATA_H

#define UINT8_MAX 0xFF
#define UINT16_MAX 0xFFFF
#define ANALOG_MAX 1023
//#define PRINT_MOTION

#include "Arduino.h"
#include "Range.h"
#include "Motion.h"
#include "ColorHSV.h"

const uint8_t UINT8_MAX_2 = UINT8_MAX/2;
const uint16_t HUE_GREEN = ((uint32_t)120*0xFF/360) << 8;
const uint16_t HUE_RED = (0/360) << 8;
const uint16_t HUE_BLUE = ((uint32_t)240*0xFF/360) << 8;

const unsigned long TIME_OUT = (unsigned long)60*3*1000;

struct Data{
  Motion motion;
  uint16_t potValue;
  bool isReserved;
  ColorHSV indicatorColor;
};
#endif
