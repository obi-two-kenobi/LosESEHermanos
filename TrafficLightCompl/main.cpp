//
//  main.cpp
//  TrafficLightThreads
//
//  Created by Luca on 10/01/23.
//

#include <iostream>

#include "include.h"
#include "Controller.hpp"
int main(int argc, const char * argv[]) {
    const int amount_before_blinking_yellow = 8;
    const int amount_before_blinking_red = 16;
    const int amount_before_normal_again = 24;

    Controller conM(4, amount_before_blinking_yellow, amount_before_blinking_red, amount_before_normal_again);
    conM.Update();
    
                                    
                                                            
    return 0;
}
