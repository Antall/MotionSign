#define DEBUG
#include <MotionSignESP12.h>
MotionSignESP12 motionSign;

void setup(){

  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  motionSign.init();
}

void loop(){
  motionSign.run();
}
