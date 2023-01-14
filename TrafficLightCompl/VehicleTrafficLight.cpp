//
//  VehicleTrafficLight.cpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#include "VehicleTrafficLight.hpp"

#if DEBUG
static std::mutex tMutex;
#endif

VehicleTrafficLight::VehicleTrafficLight(NormalRoutineState state,NormalRoutineTransition transition,std::string name,double delay)
:_state(State::Idle),_transition(transition),_name( name),_delay(delay), _normalRoutineState(NormalRoutineState::RED)
{

    this->_normalRoutineState = state;
    //this->InitialFeedback();
    
};



VehicleTrafficLight::VehicleTrafficLight(std::string name, double delay):_state(State::Idle),_transition(NormalRoutineTransition::RED_TO_YELLOW),_name(name), _delay(delay)
{
    
}

VehicleTrafficLight::VehicleTrafficLight(double delay):
_state(State::Idle),_transition(NormalRoutineTransition::RED_TO_YELLOW),_name("TRAFFIC LIGHT"), _delay(delay)
{
    
}




void VehicleTrafficLight::InitialFeedback(){
    std::cout<< "NAME   |   STATE   |   TRANSITION\n";
    std::cout <<"[" << _name << "]->["<<_state << "]->["<<_normalRoutineState <<"]"<<std::endl;
}
void VehicleTrafficLight::Update()
{
    ssize_t nbytes;
    char inbuf[2] = {};
    nbytes = read(_ColorPipe[0], inbuf, 2);
    if ( nbytes> 0)
    {
        //std::cout << inbuf<<std::endl;
        Transition temp;
        try {
             temp = static_cast<Transition>(std::stoi(std::string(inbuf)));
        } catch (...) {}

#if DEBUG
        tMutex.lock();
        std::cout << "Name: " << _name << " Trans: " << temp << "; Before: " << _state << ' ' << _normalRoutineState;
#endif
        this->HandleTransition(temp);
#if DEBUG
        std::cout << "; After: " << _state << ' ' << _normalRoutineState << std::endl;
        tMutex.unlock();
#endif
        this->Delay(_delay);
        this->Draw();

        //close(_pipe[0]);
    }
        
    
    
}
void VehicleTrafficLight::Delay(unsigned int milliseconds)
{
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds ms;
    std::this_thread::sleep_for(ms(milliseconds));
}



void VehicleTrafficLight::Feedback()
{
    std::cout <<"[" << _name << "]->["<<_state <<"]->["<<_normalRoutineState << "] with "<<_transition<<std::endl;
}




void VehicleTrafficLight::HandleTransition(Transition transition) {
    
    if (transition == Transition::ODD) {
        _normalRoutineState = NormalRoutineState::RED;
        _state = State::Idle;
        return;
    }
    if (transition == Transition::EVEN) {
        _normalRoutineState = NormalRoutineState::GREEN;
        _state = State::Idle;
        return;
    }
    if(transition == Transition::ERROR)
        _state=State::SafeMode;
    switch (_state) {
        case State::NormalRoutine:
            if(transition == Transition::EMERGENCY_VEHICLE)
            {
                _state=State::BlinkingRed;
                _normalRoutineState = NormalRoutineState::RED;
                return;
            }
            if ( transition == Transition::BLINKING_YELLOW) {
                _state=State::BlinkingYellow;
                _normalRoutineState = NormalRoutineState::YELLOW;
                return;
            }
            {
                
                
                
                int temp = TO_INT(transition);
                //std::cout << temp;
                auto result = this->NormalRoutine(TO_NRT(temp), this->_normalRoutineState);
                //std::cout <<transition<<std::endl;
                // if (result != NormalRoutineState::ERROR) {
                    
                this->_normalRoutineState = result;
                    
                // }
//                else
//                {
//
//                    //this->_normalRoutineState = NormalRoutineState::RED;
//                    this->_state= State::SafeMode;
//                }
                //this->_transition++;
         
            }
            
            break;
        case State::Idle:
            // following the state machine, it goes directly to the normal routine
            // we initialize it as well
            _state = State::NormalRoutine;
            //_normalRoutineState = NormalRoutineState::RED;
            //_transition = NormalRoutineTransition::RED_TO_YELLOW;
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

            if (transition == Transition::BLINKING_YELLOW_STOP) {
                _state = State::NormalRoutine;
                _normalRoutineState = NormalRoutineState::RED;
                _transition = NormalRoutineTransition::RED_TO_YELLOW;
                return;
            }
            switch (_normalRoutineState) {
                case NormalRoutineState::YELLOW:
                    _normalRoutineState = NormalRoutineState::BLACK;
                    break;
                case NormalRoutineState::BLACK:
                    _normalRoutineState = NormalRoutineState::YELLOW;
                    break;
                default:
                    _normalRoutineState = NormalRoutineState::BLACK;
                    break;
            }
            
            break;
        case State::BlinkingRed:
            /*
             Blink Red
             */
            switch (_normalRoutineState) {
                case NormalRoutineState::RED:
                    _normalRoutineState = NormalRoutineState::BLACK;
                    break;
                case NormalRoutineState::BLACK:
                    _normalRoutineState = NormalRoutineState::RED;
                    break;
                default:
                    _normalRoutineState = NormalRoutineState::BLACK;
                    break;
            }
            
            
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


void VehicleTrafficLight::Draw()
{
    write(_pipe[1], std::to_string(TO_INT(_normalRoutineState)).c_str(), MSGSIZE);

    if (_StatePipe != NULL){
        write(_StatePipe[1], std::to_string(TO_INT(_state)).c_str(), MSGSIZE);
    }
}
