//
//  QuadriTrafficLight.cpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#include "QuadriTrafficLight.hpp"


QuadriTrafficLight::QuadriTrafficLight() {
    
    for (int i=1; i<5; i++) {
        
        if(i%2==0)
            TrafficLights.push_back(new SimpleTrafficLight(LightColor::RED, Transition::YELLOW_TO_RED, "TL" +std::to_string(i)));
        else
            TrafficLights.push_back(new SimpleTrafficLight(LightColor::GREEN, Transition::YELLOW_TO_GREEN, "TL" +std::to_string(i)));
        
    }
    
}

void QuadriTrafficLight::Draw(int shiftx,  int shifty )
{
    int times = 0;
    int moltx[] = {0,17,51, 34};
    int molty[] = {15, 0, 15, 30};
    
    for(auto tl : TrafficLights){
        tl->Draw(moltx[times] + shiftx, molty[times] + shifty);
        times++;;
    }
}

QuadriTrafficLight::~QuadriTrafficLight()
{
    for(auto tl : TrafficLights)
        delete tl;
    TrafficLights.clear();
}

void QuadriTrafficLight::Update()
{
    for(auto tl : TrafficLights)
        tl->Update();
}
