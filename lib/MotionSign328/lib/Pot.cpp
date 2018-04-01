#include "Pot.h"

#define POT_AIN A1

void Pot::init(){
  pinMode(POT_AIN, INPUT);
}

void Pot::run(Data &data){
  data.potValue = analogRead(POT_AIN);
}


