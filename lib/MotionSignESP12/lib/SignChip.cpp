#include "SignChip.h"
#include "Arduino.h"
#define OCCUPIED_PIN 4
#define RESERVED_PIN 5

const uint8_t UPDATE_TIME = 50;

void SignChip::init(){
  lastRun = 0;
  pinMode(OCCUPIED_PIN, INPUT );
  pinMode(RESERVED_PIN, OUTPUT );
}
void SignChip::run(Data &data){
  unsigned long currMillis = millis();
  if(currMillis - lastRun < UPDATE_TIME){ return; }
  lastRun = currMillis;

  data.isOccupied = digitalRead(OCCUPIED_PIN);
  digitalWrite(RESERVED_PIN, data.isReserved );
}
