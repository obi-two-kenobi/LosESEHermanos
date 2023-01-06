//
//  main.cpp
//  ImplementationTrafficLight
//
//  Created by Luca on 06/01/23.
//

#include <iostream>
#include "SimpleTrafficLight.hpp"
int main(int argc, const char * argv[]) {
    std::cout << "Simple Traffic Light!\n";
    SimpleTrafficLight ampel = SimpleTrafficLight();
    
    while (1) {
        ampel.Update();
    }
    return 0;
}
