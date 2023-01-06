//
//  utils.cpp
//  ImplementationTrafficLight
//
//  Created by Luca on 06/01/23.
//

#include "utils.hpp"
std::ostream& operator << ( std::ostream& outs, const NormalRoutineState& p )
{
    switch (p) {
        case NormalRoutineState::RED:
            return outs <<  "RED" ;
            break;
        case NormalRoutineState::YELLOW:
            return outs <<  "YELLOW" ;
            break;
        case NormalRoutineState::GREEN:
            return outs <<  "GREEN" ;
            break;
        default:
            return outs << "ERROR";
            break;
    }
}
std::ostream& operator << ( std::ostream& outs, const State& p )
{
    switch (p) {
        case State::Idle:
            return outs <<  "Idle" ;
            break;
        case State::NormalRoutine:
            return outs <<  "NormalRoutine" ;
            break;
        case State::SafeMode:
            return outs <<  "SafeMode" ;
            break;
        case State::BlinkingRed:
            return outs <<  "BlinkingRed" ;
            break;
        case State::BlinkingYellow:
            return outs <<  "BlinkingYellow" ;
            break;
        
        default:
            return outs << "ERROR";
            break;
    }
}


std::ostream& operator << ( std::ostream& outs, const NormalRoutineTransition& p )
{
    switch (p) {
        case NormalRoutineTransition::RED_TO_YELLOW:
            return outs << "RED_TO_YELLOW";
            break;
        case NormalRoutineTransition::YELLOW_TO_GREEN:
            return outs << "YELLOW_TO_GREEN";
            break;
        case NormalRoutineTransition::GREEN_TO_YELLOW:
            return outs << "GREEN_TO_YELLOW";
            break;
        case NormalRoutineTransition::YELLOW_TO_RED:
            return outs << "YELLOW_TO_RED";
            break;
        default:
            return outs << "ERROR";
            break;
    }
}
std::ostream& operator << ( std::ostream& outs, const Mode& p )
{
    switch (p) {
        case Mode::SIMPLE:
            return outs << "SIMPLE";
            break;
        case Mode::DOUBLE:
            return outs << "DOUBLE";
            break;
        case Mode::QUADRI:
            return outs << "QUADRI";
            break;
        default:
            return outs << "ERROR";
            break;
    }
}
// Special behavior for ++Colors
NormalRoutineTransition& operator++( NormalRoutineTransition &c ) {
    using IntType = typename std::underlying_type<NormalRoutineTransition>::type;
  c = static_cast<NormalRoutineTransition>( static_cast<IntType>(c) + 1 );
  if ( c == static_cast<NormalRoutineTransition>(4) )
    c = static_cast<NormalRoutineTransition>(0);
  return c;
}

// Special behavior for Colors++
NormalRoutineTransition operator++( NormalRoutineTransition &c, int ) {
  NormalRoutineTransition result = c;
  ++c;
  return result;
}



Mode& operator--( Mode &c )
{
    using IntType = typename std::underlying_type<Mode>::type;
  c = static_cast<Mode>( static_cast<IntType>(c) - 1 );
  if ( c == static_cast<Mode>(-1) )
    c = static_cast<Mode>(2);
  return c;
}
Mode operator--( Mode &c, int )
{
    Mode result = c;
  --c;
  return result;
}


Mode& operator++( Mode &c )
{
    using IntType = typename std::underlying_type<Mode>::type;
  c = static_cast<Mode>( static_cast<IntType>(c) + 1 );
  if ( c == static_cast<Mode>(3) )
    c = static_cast<Mode>(0);
  return c;
}
Mode operator++( Mode &c, int )
{
    Mode result = c;
  ++c;
  return result;
}


NormalRoutineState TrafficLight::NormalRoutine(NormalRoutineTransition transition, NormalRoutineState _state)
{
    switch (_state) {
        case NormalRoutineState::RED:
            if (transition == NormalRoutineTransition::RED_TO_YELLOW) {
                return NormalRoutineState::YELLOW;
            }
            return NormalRoutineState::ERROR; 
            break;
            
        case NormalRoutineState::YELLOW:
            if (transition == NormalRoutineTransition::YELLOW_TO_GREEN) {
                return NormalRoutineState::GREEN;
            }else if (transition == NormalRoutineTransition::YELLOW_TO_RED){
                return NormalRoutineState::RED;
            }
            return NormalRoutineState::ERROR;
            break;
        
        case NormalRoutineState::GREEN:
            if (transition==NormalRoutineTransition::GREEN_TO_YELLOW) {
                return  NormalRoutineState::YELLOW;
            }
            return NormalRoutineState::ERROR;
            break;
            
        default:
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


std::ostream& operator << ( std::ostream& outs, const Transition& p ){
    switch (p) {
        case Transition::ERROR:
            return outs << "ERROR";
            break;
        case Transition::ERROR_FIXED:
            return outs << "ERROR_FIXED";
            break;
        case Transition::EMERGENCY_VEHICLE:
            return outs << "GREEN_TO_YELLOW";
            break;
        case Transition::EMERGENCY_VEHICLE_PASSED:
            return outs << "YELLOW_TO_RED";
            break;
        case Transition::ERROR_UNFIXABLE:
            return outs << "ERROR_UNFIXABLE";
            break;
        case Transition::NONE:
            return outs <<  "NONE" ;
            break;
        case Transition::BLINKING_YELLOW:
            return outs <<  "BLINKING_YELLOW" ;
            break;
        case Transition::BLINKING_YELLOW_STOP:
            return outs <<  "BLINKING_YELLOW_STOP" ;
            break;
        default:
            return outs << "ERROR";
            break;
    }
}
