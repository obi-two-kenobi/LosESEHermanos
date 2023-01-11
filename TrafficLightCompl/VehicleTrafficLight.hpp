//
//  VehicleTrafficLight.hpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#ifndef VehicleTrafficLight_hpp
#define VehicleTrafficLight_hpp

#include "include.h"

#include "TrafficLight.hpp"
class VehicleTrafficLight: public TrafficLight
{
public:
    VehicleTrafficLight(NormalRoutineState state = NormalRoutineState::RED,
                       NormalRoutineTransition transition = NormalRoutineTransition::RED_TO_YELLOW,
                       std::string name = "VEHICLE TRAFFIC LIGHT",
                       double delay = 1000);
    
    VehicleTrafficLight(std::string name = "VEHICLE TRAFFIC LIGHT",
                       double delay = 1000);
    
    VehicleTrafficLight(double delay = 1000);
    
    void Update();
    
    void Feedback();
    
    void Delay(unsigned int milliseconds);
    
    void InitialFeedback();
    
    void Draw();
    
    
    
    
private:
    void HandleTransition(Transition transition = Transition::NONE);
    
    
    State _state;
    NormalRoutineState _normalRoutineState;
    NormalRoutineTransition _transition;
    std::string _name;
    double _delay;
    double lastTimeChanged;
    
    
};


#endif /* VehicleTrafficLight_hpp */
