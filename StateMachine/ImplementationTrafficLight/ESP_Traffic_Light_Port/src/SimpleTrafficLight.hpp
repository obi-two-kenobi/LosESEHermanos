//
//  SimpleTrafficLight.hpp
//  ImplementationTrafficLight
//
//  Created by Luca on 06/01/23.
//

#ifndef SimpleTrafficLight_hpp
#define SimpleTrafficLight_hpp
#include "utils.hpp"
class SimpleTrafficLight: public TrafficLight
{
public:
    SimpleTrafficLight(State state = State::Idle,
                       NormalRoutineTransition transition = NormalRoutineTransition::RED_TO_YELLOW,
                       std::string name = "TRAFFIC LIGHT",
                       double delay = 1000);
    void Update();
    
    void Feedback();
    
    void Delay(unsigned int milliseconds);
    
    void InitialFeedback();

    void SetUpIO(int redLed, int greenLed, int yellowLed);
    void WriteIO(int redLed, int greenLed, int yellowLed);
    
    
    
private:
    void HandleTransition(Transition transition = Transition::NONE);
    
    
    State _state;
    NormalRoutineState _normalRoutineState;
    NormalRoutineTransition _transition;
    std::string _name;
    double _delay;
    double lastTimeChanged;
    
};


#endif /* SimpleTrafficLight_hpp */
