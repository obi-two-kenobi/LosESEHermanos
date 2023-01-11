//
//  SimpleTrafficLight.hpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#ifndef SimpleTrafficLight_hpp
#define SimpleTrafficLight_hpp

#include "utils/utils.hpp"
class SimpleTrafficLight: public TrafficLight
{
public:
    SimpleTrafficLight(LightColor state = LightColor::RED,
                       Transition transition = Transition::YELLOW_TO_RED,
                       std::string name = "TRAFFIC LIGHT",
                       double delay = 2);
    void Update();
    
    
    void Draw(int shiftx = 0, int shifty = 0);
    
    
private:
    void HandleTransition(Transition transition);
    
    
    LightColor _state;
    Transition _transition;
    std::string _name;
    double _delay;
    double lastTimeChanged;
    
};

void gotoxy(int x,int y);
#endif /* SimpleTrafficLight_hpp */
