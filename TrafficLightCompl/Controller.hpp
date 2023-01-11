//
//  Controller.hpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "include.h"
#include "TrafficLight.hpp"
#include "VehicleTrafficLight.hpp"

class Controller
{
public:
    Controller(int numberTrafficLights = 1);
    ~Controller();
    
    void Update();

    
private:
    std::vector<TrafficLight*> _trafficLights;
    std::vector<std::thread*> _trafficLightsBehaviour;
    
    int _pipes[10][2];
    int _ColorPipes[10][2];
    
    int _numberTrafficLights;
    void draw();
    void drawSimulation1();
    std::thread* drawing;
    
    std::atomic<bool> exit_thread_flag{false};
    ControllerState _state;
    std::mutex tMutex;
    NormalRoutineTransition even;
    NormalRoutineTransition odd;
    void gotoxy(int x,int y);
    void printColorVertically(char buf[MSGSIZE], int x, int y=0);
    void printColorHorizontally(char buf[MSGSIZE], int x, int y=0);

};

#endif /* Controller_hpp */
