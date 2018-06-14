#include "MotionSignESP12.h"
#include "Arduino.h"

MotionSignESP12::MotionSignESP12(){
};

void MotionSignESP12::init(){
  signChip.init();
  internet.init();
  display.init();
}

void MotionSignESP12::run(){
  signChip.run(data);
  internet.run(data);
  display.run(data);
}
