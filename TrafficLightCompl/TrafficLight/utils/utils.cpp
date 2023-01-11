//
//  utils.cpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#include "utils.hpp"

std::ostream& operator << ( std::ostream& outs, const LightColor& p )
{
    switch (p) {
        case LightColor::RED:
            return outs << ANSI_RED "RED" ANSI_BLACK;
            break;
        case LightColor::YELLOW:
            return outs << ANSI_YELLOW "YELLOW" ANSI_BLACK;
            break;
        case LightColor::GREEN:
            return outs << ANSI_GREEN "GREEN" ANSI_BLACK;
            break;
        default:
            return outs << "ERROR";
            break;
    }
}


std::ostream& operator << ( std::ostream& outs, const Transition& p )
{
    switch (p) {
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
Transition& operator++( Transition &c ) {
    using IntType = typename std::underlying_type<Transition>::type;
  c = static_cast<Transition>( static_cast<IntType>(c) + 1 );
  if ( c == static_cast<Transition>(4) )
    c = static_cast<Transition>(0);
  return c;
}

// Special behavior for Colors++
Transition operator++( Transition &c, int ) {
  Transition result = c;
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
