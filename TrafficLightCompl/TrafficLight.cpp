//
//  TrafficLight.cpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#include "TrafficLight.hpp"

NormalRoutineState TrafficLight::NormalRoutine(NormalRoutineTransition transition, NormalRoutineState _state)
{
    switch (_state) {
        case NormalRoutineState::RED:
            if (transition == NormalRoutineTransition::RED_TO_YELLOW) {
                return NormalRoutineState::YELLOWRED;
            }
            if (TO_INT(transition) == TO_INT(Transition::NONE)){
                return _state;
            }
            return NormalRoutineState::ERROR;
            break;
            
        case NormalRoutineState::YELLOW:
            if (transition == NormalRoutineTransition::YELLOW_TO_RED){
                return NormalRoutineState::RED;
            }
            if (TO_INT(transition) == TO_INT(Transition::NONE)){
                return _state;
            }
            return NormalRoutineState::ERROR;
            break;
            
        case NormalRoutineState::YELLOWRED:
            if (transition == NormalRoutineTransition::YELLOW_TO_GREEN) {
                return NormalRoutineState::GREEN;
            }
            if (TO_INT(transition) == TO_INT(Transition::NONE)){
                return _state;
            }
            return NormalRoutineState::ERROR;
            break;
        
        case NormalRoutineState::GREEN:
            if (transition==NormalRoutineTransition::GREEN_TO_YELLOW) {
                return  NormalRoutineState::YELLOW;
            }
            if (TO_INT(transition) == TO_INT(Transition::NONE)){
                return _state;
            }
            return NormalRoutineState::ERROR;
            break;
            
        default:
            if (TO_INT(transition) == TO_INT(Transition::ERROR_FIXED)){
                return NormalRoutineState::RED;
            }
            if (TO_INT(transition) == TO_INT(Transition::NONE)){
                return _state;
            }
            return NormalRoutineState::ERROR;
            break;
    }
}


bool TrafficLight::IsWorkintTime()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(1,10); // distribution in range [1, 6]

    
    if(dist10(rng) + 1 <= 3 )
        return true;
    else
        return false;
}


bool TrafficLight::IsBlinkingYellowTime()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(1,10); // distribution in range [1, 6]

    
    if(dist10(rng) + 1 <= 3 )
        return true;
    else
        return false;
}


