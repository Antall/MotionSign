#include "Internet.h"
#include "Arduino.h"
#define OCCUPIED_PIN 5
#define RESERVED_PIN 6

const unsigned long UPDATE_TIME = 50;

void Internet::init(){
  lastRun = 0;
  pinMode(OCCUPIED_PIN, OUTPUT );
  pinMode(RESERVED_PIN, INPUT );
}
void Internet::run(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_TIME){ return; }
  lastRun = currMillis;

  data.isReserved = digitalRead(RESERVED_PIN);
  digitalWrite(OCCUPIED_PIN, !data.motion.isTimeOut() );

}
