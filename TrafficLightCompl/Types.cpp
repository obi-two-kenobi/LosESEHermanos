//
//  Types.cpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#include "Types.hpp"
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

// Special behavior for ++Colors
NormalRoutineTransition& operator++( NormalRoutineTransition &c ) {
    using IntType = typename std::underlying_type<NormalRoutineTransition>::type;
  c = static_cast<NormalRoutineTransition>( static_cast<IntType>(c) + 1 );
  if ( c == static_cast<NormalRoutineTransition>(14) )
    c = static_cast<NormalRoutineTransition>(10);
  return c;
}

// Special behavior for Colors++
NormalRoutineTransition operator++( NormalRoutineTransition &c, int ) {
  NormalRoutineTransition result = c;
  ++c;
  return result;
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
        case Transition::RED_TO_YELLOW:
            return outs << "RED_TO_YELLOW";
            break;
        case Transition::YELLOW_TO_GREEN:
            return outs << "YELLOW_TO_GREEN";
            break;
        case Transition::GREEN_TO_YELLOW:
            return outs << "GREEN_TO_YELLOW";
            break;
        case Transition::YELLOW_TO_RED:
            return outs << "YELLOW_TO_RED";
            break;
        default:
            return outs << "ERROR";
            break;
    }
}
