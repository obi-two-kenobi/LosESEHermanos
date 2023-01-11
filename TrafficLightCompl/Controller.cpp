//
//  Controller.cpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#include "Controller.hpp"


Controller::Controller(int numberTrafficLights)
{
    
    if (numberTrafficLights> 10) {
        std::cerr << "ERROR: Too many trafficLights\n";
        exit(1);
    }
    
    if (numberTrafficLights % 2 !=0) {
        std::cerr << "Warning: Number of Vehicle traffic lights should be even, I am adding one\n";
        numberTrafficLights+=1;
    }
    _numberTrafficLights = numberTrafficLights;
    
    for(int i=0; i<_numberTrafficLights; i++)
    {
        //Setting up the pipes for communication with the trafficlights
        if (pipe(_pipes[i]) < 0)
               exit(1);
        if (pipe(_ColorPipes[i]) < 0)
               exit(1);
        
        if(i%2==0)
            _trafficLights.push_back(new VehicleTrafficLight(std::to_string(i), i*100));
        else
            _trafficLights.push_back(new VehicleTrafficLight(NormalRoutineState::GREEN, NormalRoutineTransition::GREEN_TO_YELLOW, std::to_string(i), i*100));
        _trafficLights[i]->setPipe(_pipes[i]);
        _trafficLights[i]->setColorPipe(_ColorPipes[i]);
        _trafficLightsBehaviour.push_back(new std::thread(_trafficLights[i]->spawn()));
        //write(_pipes[i][1], std::string("msg"+std::to_string(i)).c_str(), MSGSIZE);
        //close(_pipes[i][1]);
    }
   
    drawing = new std::thread([this]{return this->drawSimulation1();});
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //for(int i=0; i<_numberTrafficLights; i++)
      //  write(_pipes[i][1], "10", 2);
}

void Controller::Update()
{
    int amount_before_blinking_yellow = 500;
    int amount_before_blinking_red = 100;
    int amount_before_normal_again = 200;
    int count = 0;
    even = NormalRoutineTransition::GREEN_TO_YELLOW;
    odd = NormalRoutineTransition::RED_TO_YELLOW;
    
    _state = ControllerState::NORMAL_ROUTINE;
    while (1) {
        for(int i=0; i<_numberTrafficLights; i++)
            switch (_state) {
                case ControllerState::INIT:
                    break;
                case ControllerState::BLINKING_YELLOW:
                    write(_ColorPipes[i][1], std::to_string(TO_INT(Transition::BLINKING_YELLOW)).c_str(), 2);
                    break;
                case ControllerState::BLINKING_RED:
                    write(_ColorPipes[i][1], std::to_string(TO_INT(Transition::EMERGENCY_VEHICLE)).c_str(), 2);
                    break;
                case ControllerState::NORMAL_ROUTINE:
                    write(_ColorPipes[i][1], std::to_string(TO_INT((i%2==0)?even:odd)).c_str(), 2);
                    
                    break;
                case ControllerState::CHOSEN_ROUTINE:
                    break;
            }
        count++;
        if (count == amount_before_blinking_yellow) {
            _state=ControllerState::BLINKING_YELLOW;
        }else if(count == amount_before_blinking_red)
        {
            _state=ControllerState::BLINKING_RED;
        }else if (count == amount_before_normal_again){
            _state=ControllerState::NORMAL_ROUTINE;
            for (int i = 0;i<_numberTrafficLights;i++) {
                write(_ColorPipes[i][1], std::to_string(TO_INT(Transition::EMERGENCY_VEHICLE_PASSED)).c_str(), 2);
            }
            
            count = 0;
        }else{}
        tMutex.lock();
        even++;
        odd++;
        tMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       
        //std::cout << even;
    }

}



void Controller::drawSimulation1()
{
    ssize_t nbytes;
    char inbuf[10][MSGSIZE];
    while (!exit_thread_flag) {
        std::cout << "\033[2J\033[H";
        //std::cout << ANSI_BLACK<<"Thank you for running the demo\n";
        
        for (int i=0; i<_numberTrafficLights; i++) {
            nbytes = -1;
            if ((nbytes = read(_pipes[i][0], inbuf[i], MSGSIZE)) > 0)
                nbytes = -1;
        }
        
        std::cout<<
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |  | |  | |    |    |\n"
        "                                    |  V |  V |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "------------------------------------     |    |    |    |\n"
        "                        <-         -     |    |    |    |\n"
        "------------------------------------     |    |    |    |\n"
        "                       |->         -     |    |    |    |\n"
        "------------------------------------     |    |    |    |\n"
        "                        ->         -     |    |    |     ------------------------------------  \n"
        "------------------------------------|    |    |    |     -       <-                           \n"
        "                                    |    |    |    |     ------------------------------------  \n"
        "                                    |    |    |    |     -       <-|                          \n"
        "                                    |    |    |    |     ------------------------------------- \n"
        "                                    |    |    |    |     -       ->                                  \n"
        "                                    |    |    |    |     ------------------------------------- \n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |  ^ |  ^ |\n"
        "                                    |    |    |  | |  | |\n"
        "                                    |    |    |    |    |\n";
        
        printColorVertically(inbuf[0], 40,6);
        printColorVertically(inbuf[0], 44,6);
        printColorHorizontally(inbuf[1], 32, 13);
        printColorHorizontally(inbuf[1], 32, 15);
        printColorHorizontally(inbuf[3], 61, 16);
        printColorHorizontally(inbuf[3], 61, 18);
        printColorVertically(inbuf[2], 50,20); //50
        printColorVertically(inbuf[2], 54,20); //54
        
        gotoxy(0, 22);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}




void Controller::draw()
{
    ssize_t nbytes;
    char inbuf[10][MSGSIZE];
    while (!exit_thread_flag) {
        std::cout << "\033[2J\033[H";
        //std::cout << ANSI_BLACK<<"Thank you for running the demo\n";
        
        for (int i=0; i<_numberTrafficLights; i++) {
            nbytes = -1;
            if ((nbytes = read(_pipes[i][0], inbuf[i], MSGSIZE)) > 0)
                nbytes = -1;
        }
        int c=1;
        for (int i=0; i<_numberTrafficLights; i+=2){
            printColorVertically(inbuf[i], c);
            c+=2;
        }
        c+=10;
//            printf("%s\n", inbuf[i]);
        for (int i=1; i<_numberTrafficLights; i+=2){
            printColorVertically(inbuf[i],c);
            c+=2;
        }
//            printf("%s\n", inbuf[i]);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Controller::gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

 void Controller::printColorVertically(char buf[MSGSIZE], int x, int y)
{
    gotoxy(x, y+1);
    if (memcmp(buf, ANSI_RED, 6) == 0) {
        std::cout<<ANSI_RED<<"\u25A0";
        gotoxy(x, y+2);
        std::cout<<ANSI_BLACK<<"\u25A0";
        gotoxy(x, y+3);
        std::cout<<ANSI_BLACK<<"\u25A0"<<"\n";
    }else if (memcmp(buf, ANSI_YELLOW, 6) == 0)
    {
        
        tMutex.lock();
        if( even == NormalRoutineTransition::YELLOW_TO_GREEN )
            std::cout<<ANSI_RED<<"\u25A0";
        else
            std::cout<<ANSI_BLACK<<"\u25A0";
        tMutex.unlock();
        gotoxy(x, y+2);
        std::cout<<ANSI_YELLOW<<"\u25A0"<<"\n";
        gotoxy(x, y+3);
        std::cout<<ANSI_BLACK<<"\u25A0"<<"\n";
    }else if(memcmp(buf, ANSI_GREEN, 6) == 0)
    {
            std::cout<<ANSI_BLACK<<"\u25A0 "<<"\n";
            gotoxy(x, y+2);
            std::cout<<ANSI_BLACK<<"\u25A0 "<<"\n";
            gotoxy(x, y+3);
            std::cout<<ANSI_GREEN<<"\u25A0 "<<"\n";
        std::cout<<ANSI_BLACK;
    }else
    {
        std::cout<<ANSI_BLACK<<"\u25A0"<<"\n";
        gotoxy(x, y+2);
        std::cout<<ANSI_BLACK<<"\u25A0"<<"\n";
        gotoxy(x, y+3);
        std::cout<<ANSI_BLACK<<"\u25A0"<<"\n";
    }
    
}
void Controller::printColorHorizontally(char buf[MSGSIZE], int x, int y)
{
    gotoxy(x, y);
    
    if (memcmp(buf, ANSI_RED, 6) == 0) {
        std::cout<<ANSI_RED<<"\u25A0";
        gotoxy(x+1, y);
        std::cout<<ANSI_BLACK<<"\u25A0";
        gotoxy(x+2, y);
        std::cout<<ANSI_BLACK<<"\u25A0";
    }else if (memcmp(buf, ANSI_YELLOW, 6) == 0)
    {
        tMutex.lock();
        if(odd == NormalRoutineTransition::YELLOW_TO_GREEN )
            std::cout<<ANSI_RED<<"\u25A0";
        else
            std::cout<<ANSI_BLACK<<"\u25A0";
        tMutex.unlock();
        gotoxy(x+1, y);
        std::cout<<ANSI_YELLOW<<"\u25A0";
        gotoxy(x+2, y);
        std::cout<<ANSI_BLACK<<"\u25A0";
    }
    else if(memcmp(buf, ANSI_GREEN, 6) == 0)
    {
            std::cout<<ANSI_BLACK<<"\u25A0";
            gotoxy(x+1, y);
            std::cout<<ANSI_BLACK<<"\u25A0";
            gotoxy(x+2, y);
            std::cout<<ANSI_GREEN<<"\u25A0";
        std::cout<<ANSI_BLACK;
    }else
    {
        std::cout<<ANSI_BLACK<<"\u25A0";
        gotoxy(x+1, y);
        std::cout<<ANSI_BLACK<<"\u25A0";
        gotoxy(x+2, y);
        std::cout<<ANSI_BLACK<<"\u25A0";
    }
}


Controller::~Controller()
{
    for (auto thread_ : _trafficLightsBehaviour) {
        thread_->join();
    }
    for (int i=0; i<_numberTrafficLights; i++) {
        write(_pipes[i][1], std::string("msg"+std::to_string(i)).c_str(), MSGSIZE);
        //close(_pipes[i][1]);
    }
    
}



