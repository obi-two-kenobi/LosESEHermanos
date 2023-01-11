//
//  SimpleTrafficLight.cpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#include "SimpleTrafficLight.hpp"
SimpleTrafficLight::SimpleTrafficLight(LightColor state,Transition transition,std::string name,double delay)
    :_state(state),_transition(transition),_name( name),_delay(delay)
{
    
    
};





void SimpleTrafficLight::Update()
{
    if(difftime( time(0), lastTimeChanged) > this->_delay){
        this->HandleTransition(_transition);
        _transition++;
        lastTimeChanged = time(0);
        //std::cout <<_transition<<std::endl;
    }
        
}


void SimpleTrafficLight::Draw(int shiftx, int shifty)
{
    switch (_state) {
        case LightColor::RED:
            gotoxy(shiftx,shifty+1);
            std::cout << " ------------";
            gotoxy(shiftx,shifty+2);
            std::cout << "|"<<ANSI_RED "oooooooooooo" ANSI_BLACK"|";
            gotoxy(shiftx,shifty+3);
            std::cout << "|"<<ANSI_RED "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+4);
            std::cout << "|"<<ANSI_RED "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+5);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+6);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+7);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+8);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+9);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+10);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+11);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+12);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+13);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+14);
            std::cout << "     ||       "<<std::endl;
            gotoxy(shiftx,shifty+15);
            break;
        case LightColor::YELLOW:
            gotoxy(shiftx,shifty+1);
            std::cout << " ------------";
            gotoxy(shiftx,shifty+2);
            std::cout << "|"<<ANSI_BLACK "oooooooooooo" ANSI_BLACK"|";
            gotoxy(shiftx,shifty+3);
            std::cout << "|"<<ANSI_BLACK "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+4);
            std::cout << "|"<<ANSI_BLACK "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+5);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+6);
            std::cout <<"|"<< ANSI_YELLOW "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+7);
            std::cout <<"|"<< ANSI_YELLOW "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+8);
            std::cout <<"|"<< ANSI_YELLOW "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+9);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+10);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+11);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+12);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+13);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+14);
            std::cout << "     ||       "<<std::endl;
            gotoxy(shiftx,shifty+15);
            break;
        case LightColor::GREEN:
            gotoxy(shiftx,shifty+1);
            std::cout << " ------------";
            gotoxy(shiftx,shifty+2);
            std::cout << "|"<<ANSI_BLACK "oooooooooooo" ANSI_BLACK"|";
            gotoxy(shiftx,shifty+3);
            std::cout << "|"<<ANSI_BLACK "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+4);
            std::cout << "|"<<ANSI_BLACK "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+5);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+6);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+7);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+8);
            std::cout << ANSI_BLACK "|oooooooooooo|" ANSI_BLACK<<std::endl;
            gotoxy(shiftx,shifty+9);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+10);
            std::cout << "|"<<ANSI_GREEN "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+11);
            std::cout << "|"<<ANSI_GREEN "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+12);
            std::cout << "|"<<ANSI_GREEN "oooooooooooo" ANSI_BLACK"|"<<std::endl;
            gotoxy(shiftx,shifty+13);
            std::cout << " ------------"<<std::endl;
            gotoxy(shiftx,shifty+14);
            std::cout << "     ||       "<<std::endl;
            gotoxy(shiftx,shifty+15);
            break;
        default:
            break;
    }
    

    std::cout << "[" + _name+"]: " << _state << std::endl;
    
}

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

void SimpleTrafficLight::HandleTransition(Transition transition) {
    
        
        switch (_state) {
            case LightColor::RED:
                if (transition == Transition::RED_TO_YELLOW) {
                    _state = LightColor::YELLOW;
                }
                break;
                
            case LightColor::YELLOW:
                if (transition == Transition::YELLOW_TO_GREEN) {
                    _state = LightColor::GREEN;
                }else if (transition == Transition::YELLOW_TO_RED){
                    _state = LightColor::RED;
                }
                
                break;
            
            case LightColor::GREEN:
                if (transition==Transition::GREEN_TO_YELLOW) {
                    _state = LightColor::YELLOW;
                }
                
                break;
                
            default:
                break;
        
        
    }

}

