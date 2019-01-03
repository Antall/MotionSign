#include "Switch.h"

Switch::Switch(){

}

void Switch::init(uint8_t pin){
  pinID = pin;
  pinMode(pin, INPUT_PULLUP );
}

bool Switch::value(){
  return digitalRead(pinID);
}
