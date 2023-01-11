//
//  DoubleTrafficLight.cpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#include "DoubleTrafficLight.hpp"
void DoubleTrafficLight::Update()
{
    for(auto tl : TrafficLights)
        tl->Update();
}

void DoubleTrafficLight::Draw(int shiftx, int shifty )
{

    int times = 0;
    for(auto tl : TrafficLights){
        tl->Draw(shiftx*times, shifty);
        times+=2;
    }
        
}

DoubleTrafficLight::~DoubleTrafficLight()
{
    for(auto tl : TrafficLights)
        delete tl;
    TrafficLights.clear();
}


DoubleTrafficLight::DoubleTrafficLight(std::string PedName,std::string CarName)
{

    TrafficLights.push_back(new SimpleTrafficLight(LightColor::RED, Transition::YELLOW_TO_RED, PedName));
    TrafficLights.push_back(new SimpleTrafficLight(LightColor::GREEN, Transition::YELLOW_TO_GREEN, CarName));
    
}
