//
//  Controller.cpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#include "Controller.hpp"

Controller::Controller(int numberTrafficLights,
                       int amount_before_blinking_yellow,
                       int amount_before_blinking_red,
                       int amount_before_normal_again)
    : _amount_before_blinking_yellow(amount_before_blinking_yellow),
      _amount_before_blinking_red(amount_before_blinking_red),
      _amount_before_normal_again(amount_before_normal_again)
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
        if (pipe(_StatePipes[i]) < 0)
               exit(1);
        
#if TEST
        int delay = 0;
#else
        int delay = i * 100;
#endif
        if(i%2==0)
            _trafficLights.push_back(new VehicleTrafficLight(std::to_string(i), delay));
        else
            _trafficLights.push_back(new VehicleTrafficLight(NormalRoutineState::GREEN, NormalRoutineTransition::GREEN_TO_YELLOW, std::to_string(i), delay));
        _trafficLights[i]->setPipe(_pipes[i]);
        _trafficLights[i]->setColorPipe(_ColorPipes[i]);
        _trafficLights[i]->setStatePipe(_StatePipes[i]);
        _trafficLightsBehaviour.push_back(new std::jthread(_trafficLights[i]->spawn()));
        //write(_pipes[i][1], std::string("msg"+std::to_string(i)).c_str(), MSGSIZE);
        //close(_pipes[i][1]);
    }
   
    drawing = new std::jthread([this]{return this->drawSimulation1();});
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //for(int i=0; i<_numberTrafficLights; i++)
      //  write(_pipes[i][1], "10", 2);
}

void Controller::Update()
{
    int count = 0;
    int blinking_red_to_normal_flag = 0; // bit 0: for even lights; bit 1: for odd lights

    // odd starts with RED; even starts with GREEN
    //
    // However, 1st transition doesn't take effect, as their _state just changed from INIT to NORMAL_ROUTINE
    // hence 2nd, i.e. the 1st effective transition is:
    // odd: RED_TO_YELLOW; even: GREEN_TO_YELLOW
    even = NormalRoutineTransition::YELLOW_TO_RED;
    odd = NormalRoutineTransition::YELLOW_TO_GREEN;
    
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
                case ControllerState::BLINKING_RED_TO_NORMAL:
                    // loop odd & even until they are RED_TO_YELLOW, then set corrosponding bit of blinking_red_to_normal_flag to 1
                    if (i % 2 == 0)
                    {
                        // even
                        if (even == NormalRoutineTransition::RED_TO_YELLOW | (blinking_red_to_normal_flag & 0x1) == 0x1)
                        {
                            write(_ColorPipes[i][1], std::to_string(TO_INT(even)).c_str(), 2);
                            blinking_red_to_normal_flag |= 0x1;
                        } else {
                            write(_ColorPipes[i][1], std::to_string(TO_INT(Transition::NONE)).c_str(), 2);
                        }
                    }
                    else
                    {
                        // odd
                        if (odd == NormalRoutineTransition::RED_TO_YELLOW | (blinking_red_to_normal_flag & 0x2) == 0x2)
                        {
                            write(_ColorPipes[i][1], std::to_string(TO_INT(odd)).c_str(), 2);
                            blinking_red_to_normal_flag |= 0x2;
                        } else {
                            write(_ColorPipes[i][1], std::to_string(TO_INT(Transition::NONE)).c_str(), 2);
                        }
                    }
                    break;
                case ControllerState::NORMAL_ROUTINE:
                    write(_ColorPipes[i][1], std::to_string(TO_INT((i%2==0)?even:odd)).c_str(), 2);
                    break;
                case ControllerState::CHOSEN_ROUTINE:
                    break;
            }
        count++;
        if (count == _amount_before_blinking_yellow) {
            _state=ControllerState::BLINKING_YELLOW;
        }else if(count == _amount_before_blinking_red)
        {
            _state=ControllerState::BLINKING_RED;
        }else if (count == _amount_before_normal_again){
            _state = ControllerState::BLINKING_RED_TO_NORMAL;

            blinking_red_to_normal_flag = 0;
            even = NormalRoutineTransition::YELLOW_TO_RED;
            odd = NormalRoutineTransition::YELLOW_TO_GREEN;
            for (int i = 0; i < _numberTrafficLights; i++)
            {
                write(_ColorPipes[i][1], std::to_string(TO_INT(Transition::EMERGENCY_VEHICLE_PASSED)).c_str(), 2);
            }
        }
        else if (_state == ControllerState::BLINKING_RED_TO_NORMAL && blinking_red_to_normal_flag == 0x3)
        {
            _state = ControllerState::NORMAL_ROUTINE;

            count = 0;
        }
        tMutex.lock();
        even++;
        odd++;
        tMutex.unlock();
#if (!TEST)
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#endif

        //std::cout << even;
    }

}



void Controller::drawSimulation1()
{
    ssize_t nbytes;
    char nrsBuf[10][MSGSIZE], stateBuf[10][MSGSIZE];
    while (!exit_thread_flag) {
#if !(DEBUG) && !(TEST)
        std::cout << "\033[2J\033[H";
#endif
        //std::cout << ANSI_BLACK<<"Thank you for running the demo\n";
        
        for (int i=0; i<_numberTrafficLights; i++) {
            nbytes = -1;
            if ((nbytes = read(_pipes[i][0], nrsBuf[i], MSGSIZE)) > 0)
                nbytes = -1;
            nbytes = -1;
            if ((nbytes = read(_StatePipes[i][0], stateBuf[i], MSGSIZE)) > 0)
                nbytes = -1;
        }
        
#if !(DEBUG) && !(TEST)
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
        "                        ->         -     |    |    |     ------------------------------------ \n"
        "------------------------------------|    |    |    |     -       <-                           \n"
        "                                    |    |    |    |     ------------------------------------ \n"
        "                                    |    |    |    |     -       <-|                          \n"
        "                                    |    |    |    |     ------------------------------------ \n"
        "                                    |    |    |    |     -       ->                           \n"
        "                                    |    |    |    |     ------------------------------------ \n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |    |    |\n"
        "                                    |    |    |  ^ |  ^ |\n"
        "                                    |    |    |  | |  | |\n"
        "                                    |    |    |    |    |\n";
        
        printColorVertically(nrsBuf[0], 40,6);
        printColorVertically(nrsBuf[0], 44,6);
        printPedLight(nrsBuf[0], stateBuf[0], 35, 5);
        printPedLight(nrsBuf[0], stateBuf[0], 58, 5);
        printColorHorizontally(nrsBuf[1], 32, 13);
        printColorHorizontally(nrsBuf[1], 32, 15);
        printPedLight(nrsBuf[1], stateBuf[1], 29, 7);
        printPedLight(nrsBuf[1], stateBuf[1], 29, 16);
        printColorHorizontally(nrsBuf[3], 61, 16);
        printColorHorizontally(nrsBuf[3], 61, 18);
        printPedLight(nrsBuf[3], stateBuf[3], 64, 12);
        printPedLight(nrsBuf[3], stateBuf[3], 64, 21);
        printColorVertically(nrsBuf[2], 50,20); //50
        printColorVertically(nrsBuf[2], 54,20); //54
        printPedLight(nrsBuf[2], stateBuf[2], 35, 23);
        printPedLight(nrsBuf[2], stateBuf[2], 58, 23);
        
        gotoxy(0, 22);
#endif

#if DEBUG
        std::cout << std::endl;
#endif

#if TEST
        write(_testPipe[1], nrsBuf, sizeof(char) * 10 * MSGSIZE);
        write(_testPipe[1], stateBuf, sizeof(char) * 10 * MSGSIZE);
#else
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
#endif
    }
}




// void Controller::draw()
// {
//     ssize_t nbytes;
//     char inbuf[10][MSGSIZE];
//     while (!exit_thread_flag) {
//         std::cout << "\033[2J\033[H";
//         //std::cout << ANSI_BLACK<<"Thank you for running the demo\n";
        
//         for (int i=0; i<_numberTrafficLights; i++) {
//             nbytes = -1;
//             if ((nbytes = read(_pipes[i][0], inbuf[i], MSGSIZE)) > 0)
//                 nbytes = -1;
//         }
//         int c=1;
//         for (int i=0; i<_numberTrafficLights; i+=2){
//             printColorVertically(inbuf[i], c);
//             c+=2;
//         }
//         c+=10;
// //            printf("%s\n", inbuf[i]);
//         for (int i=1; i<_numberTrafficLights; i+=2){
//             printColorVertically(inbuf[i],c);
//             c+=2;
//         }
// //            printf("%s\n", inbuf[i]);
        
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
// }

void Controller::gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

void Controller::printColorVertically(char buf[MSGSIZE], int x, int y)
{
    gotoxy(x, y + 1);
    NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(buf)));

    switch (nrState)
    {
    case NormalRoutineState::RED:
        std::cout << ANSI_RED << "●"
                  << "\n";
        gotoxy(x, y + 2);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        gotoxy(x, y + 3);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        break;

    case NormalRoutineState::YELLOW:
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        gotoxy(x, y + 2);
        std::cout << ANSI_YELLOW << "●"
                  << "\n";
        gotoxy(x, y + 3);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        break;

    case NormalRoutineState::GREEN:
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        gotoxy(x, y + 2);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        gotoxy(x, y + 3);
        std::cout << ANSI_GREEN << "●"
                  << "\n"
                  << ANSI_BLACK;
        break;

    case NormalRoutineState::YELLOWRED:
        std::cout << ANSI_RED << "●"
                  << "\n";
        gotoxy(x, y + 2);
        std::cout << ANSI_YELLOW << "●"
                  << "\n";
        gotoxy(x, y + 3);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        break;

    case NormalRoutineState::BLACK:
    case NormalRoutineState::ERROR:
    default:
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        gotoxy(x, y + 2);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
        gotoxy(x, y + 3);
        std::cout << ANSI_BLACK << "●"
                  << "\n";
    }
}

void Controller::printColorHorizontally(char buf[MSGSIZE], int x, int y)
{
    gotoxy(x, y);

    NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(buf)));

    switch (nrState)
    {
    case NormalRoutineState::RED:
        std::cout << ANSI_RED << "●";
        gotoxy(x + 1, y);
        std::cout << ANSI_BLACK << "●";
        gotoxy(x + 2, y);
        std::cout << ANSI_BLACK << "●";
        break;

    case NormalRoutineState::YELLOW:
        std::cout << ANSI_BLACK << "●";
        gotoxy(x + 1, y);
        std::cout << ANSI_YELLOW << "●";
        gotoxy(x + 2, y);
        std::cout << ANSI_BLACK << "●";
        break;

    case NormalRoutineState::GREEN:
        std::cout << ANSI_BLACK << "●";
        gotoxy(x + 1, y);
        std::cout << ANSI_BLACK << "●";
        gotoxy(x + 2, y);
        std::cout << ANSI_GREEN << "●" << ANSI_BLACK;
        break;

    case NormalRoutineState::YELLOWRED:
        std::cout << ANSI_RED << "●";
        gotoxy(x + 1, y);
        std::cout << ANSI_YELLOW << "●";
        gotoxy(x + 2, y);
        std::cout << ANSI_BLACK << "●";
        break;

    case NormalRoutineState::BLACK:
    case NormalRoutineState::ERROR:
    default:
        std::cout << ANSI_BLACK << "●";
        gotoxy(x + 1, y);
        std::cout << ANSI_BLACK << "●";
        gotoxy(x + 2, y);
        std::cout << ANSI_BLACK << "●";
    }
}

void Controller::printPedLight(char nrsBuf[MSGSIZE], char stateBuf[MSGSIZE], int x, int y)
{
    auto printGreen = [](Controller *con, int x, int y)
    {
        std::cout << ANSI_BLACK << "웃"
                  << "\n";
        con->gotoxy(x, y + 2);
        std::cout << BG_GREEN << "웃" << ANSI_BLACK
                  << "\n";
    };

    auto printRed = [](Controller *con, int x, int y)
    {
        std::cout << BG_RED << "웃"
                  << "\n";
        con->gotoxy(x, y + 2);
        std::cout << ANSI_BLACK << "웃"
                  << "\n";
    };

    auto printOff = [](Controller *con, int x, int y)
    {
        std::cout << ANSI_BLACK << "웃"
                  << "\n";
        con->gotoxy(x, y + 2);
        std::cout << ANSI_BLACK << "웃"
                  << "\n";
    };

    gotoxy(x, y + 1);

    NormalRoutineState nrState = static_cast<NormalRoutineState>(std::stoi(std::string(nrsBuf)));
    State state = static_cast<State>(std::stoi(std::string(stateBuf)));

    switch (state)
    {
    case State::NormalRoutine:
        // GREEN ped. light when car light is RED; RED otherwises
        switch (nrState)
        {
        case NormalRoutineState::RED:
            printGreen(this, x, y);
            break;
        default:
            printRed(this, x, y);
        }
        break;
    case State::BlinkingRed:
        printRed(this, x, y);
        break;
    case State::Idle:
    case State::SafeMode:
    case State::BlinkingYellow:
    default:
        printOff(this, x, y);
        break;
    }
}

Controller::~Controller()
{
    for (auto thread_ : _trafficLightsBehaviour)
    {
        thread_->join();
    }
    for (int i = 0; i < _numberTrafficLights; i++)
    {
        write(_pipes[i][1], std::string("msg" + std::to_string(i)).c_str(), MSGSIZE);
        // close(_pipes[i][1]);
    }

#if TEST
    {
        close(_testPipe[1]);
    }
#endif
}
