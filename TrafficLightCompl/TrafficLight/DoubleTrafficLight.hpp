//
//  DoubleTrafficLight.hpp
//  TrafficLight
//
//  Created by Luca on 13/12/22.
//

#ifndef DoubleTrafficLight_hpp
#define DoubleTrafficLight_hpp

#include "utils/utils.hpp"
#include "SimpleTrafficLight.hpp"

class DoubleTrafficLight: public TrafficLight
{
public:
    void Draw(int shiftx = 0, int shifty = 0);
    void Update();
    ~DoubleTrafficLight();;
    DoubleTrafficLight(std::string PedName = "PEDESTRIAN",
                       std::string CarName = "CAR");
private:
    std::vector <SimpleTrafficLight* > TrafficLights;
    

};






#endif /* DoubleTrafficLight_hpp */
