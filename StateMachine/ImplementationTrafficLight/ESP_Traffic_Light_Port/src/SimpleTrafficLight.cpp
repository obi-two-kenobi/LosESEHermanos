//
//  SimpleTrafficLight.cpp
//  ImplementationTrafficLight
//
//  Created by Luca on 06/01/23.
//

#include "SimpleTrafficLight.hpp"
SimpleTrafficLight::SimpleTrafficLight(State state,NormalRoutineTransition transition,std::string name,double delay)
:_state(state),_transition(transition),_name( name),_delay(delay), _normalRoutineState(NormalRoutineState::RED)
{
    
    this->InitialFeedback();
    
};
void SimpleTrafficLight::InitialFeedback(){
    std::cout<< "NAME   |   STATE   |   TRANSITION\n";
    std::cout <<"[" << _name << "]->["<<_state << "]->["<<_normalRoutineState <<"]"<<std::endl;
}
void SimpleTrafficLight::Update()
{
   
    this->HandleTransition();
    this->Delay(_delay);
    this->Feedback();
    
    
        
}
void SimpleTrafficLight::Delay(unsigned int milliseconds)
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds ms;
    std::this_thread::sleep_for(ms(milliseconds));
}



void SimpleTrafficLight::Feedback()
{
    std::cout <<"[" << _name << "]->["<<_state <<"]->["<<_normalRoutineState << "] with "<<_transition<<std::endl;
    this->WriteIO(0,0,0);
    switch(_normalRoutineState){
        case NormalRoutineState::RED:
            this->WriteIO(1,0,0);
            break;
        case NormalRoutineState::YELLOWRED:
            this->WriteIO(1,0,1);
            break;
        case NormalRoutineState::YELLOW:
            this->WriteIO(0,0,1);
            break;
        case NormalRoutineState::GREEN:
            this->WriteIO(0,1,0);
            break;
        case NormalRoutineState::ERROR:
            while (true)
            {
                this->WriteIO(1,0,0);
                this->Delay(1000);
                this->WriteIO(0,0,0);
                this->Delay(1000);
            }
            break;
    }
}




void SimpleTrafficLight::HandleTransition(Transition transition) {
    
    
    
    switch (_state) {
        case State::NormalRoutine:
            if(transition == Transition::EMERGENCY_VEHICLE)
            {
                _state=State::BlinkingRed;
                _normalRoutineState = NormalRoutineState::RED;
                return;
            }
            if (this->IsBlinkingYellowTime() || transition == Transition::BLINKING_YELLOW) {
                _state=State::BlinkingYellow;
                _normalRoutineState = NormalRoutineState::YELLOW;
                return;
            }
            {
                
                auto result = this->NormalRoutine(this ->_transition, this->_normalRoutineState);
                if (result != NormalRoutineState::ERROR) {
                    this->_normalRoutineState = result;
                    
                }
                else
                {
                    //this->_normalRoutineState = NormalRoutineState::RED;
                    this->_state= State::SafeMode;
                }
                this->_transition++;
         
            }
            
            break;
        case State::Idle:
            // following the state machine, it goes directly to the normal routine
            // we initialize it as well
            _state = State::NormalRoutine;
            _normalRoutineState = NormalRoutineState::RED;
            _transition = NormalRoutineTransition::RED_TO_YELLOW;
            break;
        case State::BlinkingYellow:
            
            /*
             Blink Yellow
             */
            if(transition == Transition::EMERGENCY_VEHICLE)
            {
                _state=State::BlinkingRed;
                _normalRoutineState = NormalRoutineState::RED;
                return;
            }
            
            if (this->IsWorkintTime() || transition == Transition::BLINKING_YELLOW_STOP) {
                _state = State::NormalRoutine;
                _normalRoutineState = NormalRoutineState::RED;
                _transition = NormalRoutineTransition::RED_TO_YELLOW;
                return;
            }
            
            
            break;
        case State::BlinkingRed:
            /*
             Blink Red
             */
            if (transition == Transition::EMERGENCY_VEHICLE_PASSED) {
                _state = State::NormalRoutine;
                _normalRoutineState = NormalRoutineState::RED;
                _transition = NormalRoutineTransition::RED_TO_YELLOW;
                return;
            }
            
            
            
            break;
        case State::SafeMode:
            //in this case, we are going to just quit;
            std::cout << "\n\n THE ERROR WAS UNFIXABLE \n\n";
            exit(1);
        default:
            break;
    }
    
    
    
    

}

void SimpleTrafficLight::SetUpIO(int redLed, int greenLed, int yellowLed) {
    #ifdef ARDUINO
        pinMode(redLed, OUTPUT);
        pinMode(greenLed, OUTPUT);
        pinMode(yellowLed, OUTPUT);
    #elif defined(__linux__)
        setUpSysfs(redLed, greenLed, yellowLed);
    #elif defined(_WIN32)
        setUpWinIo(redLed, greenLed, yellowLed);    
    #endif
}

void SimpleTrafficLight::WriteIO(int redLedVal, int greenLedVal, int yellowLedVal) {
    #ifdef ARDUINO
        digitalWrite(RED_LED, redLedVal);
        digitalWrite(GREEN_LED, greenLedVal);
        digitalWrite(YELLOW_LED, yellowLedVal);

    #elif defined(__linux__)
        writeSysfs(redLedVal, greenLedVal, yellowLedVal);

    #elif defined(_WIN32)
        writeWinIo(redLedVal, greenLedVal, yellowLedVal);
    #endif
}