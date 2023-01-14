//
//  TrafficLight.hpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#ifndef TrafficLight_hpp
#define TrafficLight_hpp


#include "include.h"

class TrafficLight
{
public:
    virtual ~TrafficLight()
    {
        close(_pipe[1]);
    }
    
    virtual void Update()=0;
    virtual void Feedback() = 0;
    virtual void Delay(unsigned int milliseconds)=0;
    virtual bool IsWorkintTime();
    virtual bool IsBlinkingYellowTime();
    virtual NormalRoutineState NormalRoutine(NormalRoutineTransition transition, NormalRoutineState _state);
    
    virtual void Draw()=0;
    
    void gotoxy(int x,int y)
    {
        printf("%c[%d;%df",0x1B,y,x);
    }
    
    auto spawn() {
        
//        return [this] {
//            ssize_t nbytes;
//            char inbuf[MSGSIZE];
//            while ((nbytes = read(_pipe[0], inbuf, MSGSIZE)) > 0)
//                   printf("%s\n", inbuf);
//            close(_pipe[0]);
//        };

        //   return  [this] { while(1) this->Update(); } ;
        return [this](std::stop_token stop_token)
        { while(!stop_token.stop_requested()) this->Update(); };
    }

    void setPipe(int* newPipe)
    {
        _pipe = newPipe;
    }
    
    int* getPipe()
    {
        return _pipe;
    }
    
    void setColorPipe(int* newPipe)
    {
        _ColorPipe = newPipe;
    }
    
    int* getColorPipe()
    {
        return _ColorPipe;
    }
    
    void setStatePipe(int* newPipe)
    {
        _StatePipe = newPipe;
    }
    
    int* getStatePipe()
    {
        return _StatePipe;
    }

protected:
    int* _pipe;
    int* _ColorPipe;
    int* _StatePipe = NULL;
private:
    
    
    
};


#endif /* TrafficLight_hpp */
