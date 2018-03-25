#include <Adafruit_WS2801.h>
#define DEBUG

#include <MotionSign388.h>
MotionSign328 motionSign;

void setup(){

  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  motionSign.init();
}

void loop(){
  motionSign.run();
}
