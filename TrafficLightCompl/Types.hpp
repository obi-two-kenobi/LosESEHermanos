//
//  Types.hpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#ifndef Types_hpp
#define Types_hpp

#include "include.h"

#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define ANSI_BLACK   "\x1b[0m"

// #define RTY "10"
// #define YTG "11"
// #define GTY "12"
// #define YTR "13"

// #define RED_MSG "40"
// #define GREEN_MSG "50"
// #define YELLOW_MSG "60"

#define TO_INT(x) static_cast<int>(x)
#define TO_NRT(x) static_cast<NormalRoutineTransition>(x)
#define TO_TRA(x) static_cast<Transition>(x)
#define TO_CHAR(x) static_cast<char*>(TO_INT(x))

enum class Transition
{
    ERROR  = 0,
    ERROR_FIXED = 1,
    EMERGENCY_VEHICLE_PASSED = 2,
    EMERGENCY_VEHICLE = 3,
    ERROR_UNFIXABLE = 4,
    NONE = 5,
    BLINKING_YELLOW  =6,
    BLINKING_YELLOW_STOP = 7,
    RED_TO_YELLOW = 10,
    YELLOW_TO_GREEN = 11,
    GREEN_TO_YELLOW = 12,
    YELLOW_TO_RED = 13,
    ODD = 99,
    EVEN = 98
    
};

std::ostream& operator << ( std::ostream& outs, const Transition& p );



enum class NormalRoutineTransition
{
    // need to make sure the int value is the same as those in Transition, otherwise Controller.cpp may break:
    // _pipe of VehicleTrafficLight should be fed with Transition, but sometimes it's fed with NormalRoutineTransition in Controller.cpp
    RED_TO_YELLOW = static_cast<int>(Transition::RED_TO_YELLOW),
    YELLOW_TO_GREEN = static_cast<int>(Transition::YELLOW_TO_GREEN),
    GREEN_TO_YELLOW = static_cast<int>(Transition::GREEN_TO_YELLOW),
    YELLOW_TO_RED = static_cast<int>(Transition::YELLOW_TO_RED)
};
// num of elements in NormalRoutineTransition, for TrafficLightTest.cpp
const int NormalRoutineTransitionNum = 4;




NormalRoutineTransition& operator++( NormalRoutineTransition &c ) ;
NormalRoutineTransition operator++( NormalRoutineTransition &c, int );
std::ostream& operator << ( std::ostream& outs, const NormalRoutineTransition& p );

// indicate color of the traffic light
enum class NormalRoutineState
{
    RED,
    YELLOW,
    GREEN,
    YELLOWRED,
    BLACK,
    ERROR
};
enum class State
{
    
    SafeMode,
    BlinkingRed,
    BlinkingYellow,
    NormalRoutine,
    Idle
    
};

std::ostream& operator << ( std::ostream& outs, const NormalRoutineState& p );
std::ostream& operator << ( std::ostream& outs, const State& p );


enum class ControllerState
{
    INIT,
    NORMAL_ROUTINE,
    BLINKING_YELLOW,
    BLINKING_RED,
    BLINKING_RED_TO_NORMAL,
    CHOSEN_ROUTINE
};
NormalRoutineTransition& operator++( NormalRoutineTransition &c ) ;
NormalRoutineTransition operator++( NormalRoutineTransition &c, int );




#endif /* Types_hpp */
