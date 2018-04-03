#include <Adafruit_WS2801.h>
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

//#define __AVR_ATtiny85__
#ifndef __AVR_ATtiny85__
  #define DEBUG
  //#include <IRremote.h>
#endif

#include <MotionSign328.h>
MotionSign328 motionSign;

void setup(){

  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 8000000) clock_prescale_set(clock_div_1);
  #endif

  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  motionSign.init();
}

void loop(){
  motionSign.run();
}
