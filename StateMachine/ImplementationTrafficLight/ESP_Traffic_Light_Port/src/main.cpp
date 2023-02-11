#include <iostream>
#include "SimpleTrafficLight.hpp"

SimpleTrafficLight ampel = SimpleTrafficLight();

void setup() {
  Serial.begin(115200);
  ampel.SetUpIO(RED_LED,GREEN_LED,YELLOW_LED);
  
}

void loop() {
  while (true)
  {
    ampel.Update();    
  }
}