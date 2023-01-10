#include <Arduino.h>
#include <iostream>
#include "SimpleTrafficLight.hpp"

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
}

void loop() {
  SimpleTrafficLight ampel = SimpleTrafficLight();

  while (true)
  {
    ampel.Update();
  }
  
}