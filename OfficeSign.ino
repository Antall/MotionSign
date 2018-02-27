#include <Adafruit_WS2801.h>
#undef DEBUG

#include <OfficeSign.h>
OfficeSign officeSign;

void setup(){

  #ifdef DEBUG
  Serial.begin(115200);
  #endif

  officeSign.init();
}

void loop(){
  officeSign.run();
}
