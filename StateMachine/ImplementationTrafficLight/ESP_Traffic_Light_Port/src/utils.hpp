//
//  utils.hpp
//  ImplementationTrafficLight
//
//  Created by Luca on 06/01/23.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <csignal>
#include <Arduino.h>
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLACK   "\x1b[0m"
#define RED_LED 4
#define YELLOW_LED 5
#define GREEN_LED 6
enum class Transition
{
    ERROR  = 0,
    ERROR_FIXED = 1,
    EMERGENCY_VEHICLE_PASSED = 2,
    EMERGENCY_VEHICLE = 3,
    ERROR_UNFIXABLE = 4,
    NONE = 5,
    BLINKING_YELLOW  =6,
    BLINKING_YELLOW_STOP = 7
};
std::ostream& operator << ( std::ostream& outs, const Transition& p );


enum class NormalRoutineTransition
{
    RED_TO_YELLOW = 0,
    YELLOW_TO_GREEN = 1,
    GREEN_TO_YELLOW = 2,
    YELLOW_TO_RED = 3,
    
};
NormalRoutineTransition& operator++( NormalRoutineTransition &c ) ;
NormalRoutineTransition operator++( NormalRoutineTransition &c, int );
std::ostream& operator << ( std::ostream& outs, const NormalRoutineTransition& p );

enum class NormalRoutineState
{
    RED,
    YELLOW,
    GREEN,
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


class TrafficLight
{
public:
    virtual ~TrafficLight() = default;
    
    virtual void Update()=0;
    virtual void Feedback() = 0;
    virtual void Delay(unsigned int milliseconds)=0;
    virtual bool IsWorkintTime();
    virtual bool IsBlinkingYellowTime();
    virtual NormalRoutineState NormalRoutine(NormalRoutineTransition transition, NormalRoutineState _state);
};


enum class Mode
{
    SIMPLE,
    DOUBLE,
    QUADRI
};
std::ostream& operator << ( std::ostream& outs, const Mode& p );
Mode& operator--( Mode &c ) ;
Mode operator--( Mode &c, int );

Mode& operator++( Mode &c ) ;
Mode operator++( Mode &c, int );



#endif /* utils_hpp */
