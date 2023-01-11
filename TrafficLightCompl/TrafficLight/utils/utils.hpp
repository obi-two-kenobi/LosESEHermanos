//
//  utils.hpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>

#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLACK   "\x1b[0m"


enum class Transition
{
    RED_TO_YELLOW = 0,
    YELLOW_TO_GREEN = 1,
    GREEN_TO_YELLOW = 2,
    YELLOW_TO_RED = 3,
    
};
Transition& operator++( Transition &c ) ;
Transition operator++( Transition &c, int );
std::ostream& operator << ( std::ostream& outs, const Transition& p );

enum class LightColor
{
    RED,
    YELLOW,
    GREEN
};

std::ostream& operator << ( std::ostream& outs, const LightColor& p );


class TrafficLight
{
public:
    virtual void Update()=0;
    virtual void Draw(int shiftx = 0, int shifty = 0)=0;
    virtual ~TrafficLight() = default;
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
