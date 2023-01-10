#include <Arduino.h>
#include <iostream>
#include "SimpleTrafficLight.hpp"
std::list<int> HandleTransitionTimes, UpdateTimes;
void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
}

void loop() {
  SimpleTrafficLight ampel = SimpleTrafficLight();

  while (true)
  {
    ampel.Update();
    if(UpdateTimes.size()>=100){
      std::cout<<"Update Times:\n";
      for(auto& time : UpdateTimes){
        std::cout << time << ", ";
      }
      std::cout << std::endl;

      std::cout<<"HandleTransition Times:\n";
      for(auto& time : HandleTransitionTimes){
        std::cout << time << ", ";
      }
      std::cout << std::endl;  

      while (true)
      {
        delay(1000);
      }
      
    }
  }
  
}