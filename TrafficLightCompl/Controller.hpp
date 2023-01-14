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
    Controller(int numberTrafficLights = 1,
               int amount_before_blinking_yellow = 8,
               int amount_before_blinking_red = 16,
               int amount_before_normal_again = 24);
    ~Controller();

    void Update();
    auto spawn()
    {
        return [this]
        { Update(); };
    }

#if 1//TEST
    void setTestPipe(int *newPipe)
    {
        _testPipe = newPipe;
    }
#endif

private:
    std::vector<TrafficLight*> _trafficLights;
    std::vector<std::jthread*> _trafficLightsBehaviour;
    
    int _pipes[10][2];
    int _ColorPipes[10][2];
    int _StatePipes[10][2];
    
    int _numberTrafficLights;
    // void draw();
    void drawSimulation1();
    std::jthread* drawing;
    
    std::atomic<bool> exit_thread_flag{false};
    ControllerState _state;
    std::mutex tMutex;
    NormalRoutineTransition even;
    NormalRoutineTransition odd;
    void gotoxy(int x,int y);
    void printColorVertically(char buf[MSGSIZE], int x, int y=0);
    void printColorHorizontally(char buf[MSGSIZE], int x, int y=0);
    void printPedLight(char nrsBuf[MSGSIZE], char stateBuf[MSGSIZE], int x, int y = 0);

    int _amount_before_blinking_yellow;
    int _amount_before_blinking_red;
    int _amount_before_normal_again;

#if 1//TEST
    int *_testPipe;
#endif
    };

#endif /* Controller_hpp */
