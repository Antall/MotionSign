#include "Arduino.h"
#include "OpenPIR.h"
#include <avr/io.h>


#define PIR_AOUT A0  // PIR analog output on A0
#define PIR_DOUT 2   // PIR digital output on D2

#define PRINT_TIME 100 // Rate of serial printouts

unsigned long lastPrint = 0; // Keep track of last serial out

void OpenPIR::init(){
  // Analog and digital pins should both be set as inputs:
  pinMode(PIR_AOUT, INPUT);
  pinMode(PIR_DOUT, INPUT);

}

void OpenPIR::run(SignData &data){
  this->getDigital(data);
  this->getAnalog(data);
}

void OpenPIR::getAnalog(SignData &data){
  data.analogPIR = analogRead(PIR_AOUT);

  //float voltage = (float) data.analogPIR / 1024.0 * 5.0;
  // Print the reading from the digital pin.
  // Mutliply by 5 to maintain scale with AOUT.
  /*
  Serial.print(5 * digitalRead(PIR_DOUT));
  Serial.print(',');    // Print a comma
  Serial.print(2.5);    // Print the upper limit
  Serial.print(',');    // Print a comma
  Serial.print(1.7);    // Print the lower limit
  Serial.print(',');    // Print a comma
  Serial.print(voltage); // Print voltage
  Serial.println();
  */

}

void OpenPIR::getDigital(SignData &data){
  // The OpenPIR's digital output is active high
  data.isMotion = digitalRead(PIR_DOUT);

  if (data.isMotion == HIGH){
    data.lastMotion = millis();
  }
}
