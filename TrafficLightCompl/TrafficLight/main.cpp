//
//  main.cpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#include "SimpleTrafficLight.hpp"
#include "DoubleTrafficLight.hpp"
#include "QuadriTrafficLight.hpp"
#include <signal.h>
#define TIME 20
TrafficLight* ampel;
static volatile int keepRunning = 1;
void intHandler(int dummy) {
    keepRunning = 0;
    std::cout << "\033[2J\033[H";
    std::cout << "Thank you for running the demo\n";
    delete ampel;
    exit(0);
}

int main(int argc, const char * argv[]) {
    signal(SIGINT, intHandler);
    
    
    ampel = new SimpleTrafficLight;
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;
    double lastTimeChanged = time(0);
    Mode mode = Mode::DOUBLE;
    while (keepRunning) {
        std::cout << "\033[2J\033[H";
        
        std::cout << "/////////////////"<<std::endl;
        std::cout << "NEW MODE : "<<--mode<<std::endl;
        std::cout << "/////////////////"<<std::endl;
        mode++;
        ampel->Draw(30, 4);
        ampel->Update();
        sleep_for(milliseconds(100));
        
        
        if(difftime( time(0), lastTimeChanged) > TIME){
            
            
            lastTimeChanged = time(0);
            switch (mode) {
                case Mode::SIMPLE:
                    ampel = new SimpleTrafficLight;
                    mode = Mode::DOUBLE;
                    
                    
                    break;
                case Mode::DOUBLE:
                    ampel = new DoubleTrafficLight;
                    mode = Mode::QUADRI;
                    
                    break;
                case Mode::QUADRI:
                    ampel = new QuadriTrafficLight;
                    mode = Mode::SIMPLE;
                    
                    break;
                default:
                    break;
            }
        }
        
    }
    

//    delete ampel;
    return 0;
}


