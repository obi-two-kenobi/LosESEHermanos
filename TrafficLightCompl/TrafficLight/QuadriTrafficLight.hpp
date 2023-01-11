//
//  QuadriTrafficLight.hpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#ifndef QuadriTrafficLight_hpp
#define QuadriTrafficLight_hpp

#include "utils/utils.hpp"
#include "SimpleTrafficLight.hpp"



class QuadriTrafficLight : public TrafficLight
{
public:
    void Draw(int shiftx = 0, int shifty = 0);
    void Update();
    ~QuadriTrafficLight();
    QuadriTrafficLight();
private:
    std::vector <SimpleTrafficLight* > TrafficLights;
    

};




#endif /* QuadriTrafficLight_hpp */
