#include "MotionSignESP12.h"
#include "Arduino.h"

MotionSignESP12::MotionSignESP12(){
};

void MotionSignESP12::init(){
  signChip.init();
  internet.init();
}

void MotionSignESP12::run(){
  Serial.print(data.isReserved);
  signChip.run(data);
  internet.run(data);
}
