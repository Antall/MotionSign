#include "Arduino.h"
#include "OpenPIR.h"


#define PIR_AOUT A0  // PIR analog output on A0
#define PIR_DOUT 2   // PIR digital output on D2
#define LED_PIN  13  // LED to illuminate on motion

#define PRINT_TIME 100 // Rate of serial printouts

unsigned long lastPrint = 0; // Keep track of last serial out

void OpenPIR::init(){
  // Analog and digital pins should both be set as inputs:
  pinMode(PIR_AOUT, INPUT);
  pinMode(PIR_DOUT, INPUT);

  // Configure the motion indicator LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Turn the LED off

}

void OpenPIR::run(SignData &data){
  this->getDigital(data);
  this->getAnalog(data);
}

void OpenPIR::getAnalog(SignData &data){
  data.analogPIR = analogRead(PIR_AOUT);
}

void OpenPIR::getDigital(SignData &data){
  // The OpenPIR's digital output is active high
  data.isMotion = digitalRead(PIR_DOUT);

  // If motion is detected, turn the onboard LED on:
  if (data.isMotion == HIGH){
    digitalWrite(LED_PIN, HIGH);
  } else { // Otherwise turn the LED off:
    digitalWrite(LED_PIN, LOW);
  }

}
