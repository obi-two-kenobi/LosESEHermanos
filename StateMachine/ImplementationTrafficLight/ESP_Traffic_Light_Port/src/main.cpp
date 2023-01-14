#include <Arduino.h>
#include <iostream>
#include "SimpleTrafficLight.hpp"
void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  
}

void loop() {
  SimpleTrafficLight ampel = SimpleTrafficLight();

  while (true)
  {
    ampel.Update();    
    
  }
  
}