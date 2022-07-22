/**
 * @file stone_housemaker.h
 * @author PFA03027@nifty.com
 * @brief Adaptee class as Adapter pattern sample
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef STONE_HOUSEMAKER_H_
#define STONE_HOUSEMAKER_H_

#include <iostream>

class stone_housemaker {
    public:
        ~stone_housemaker() {}

        void make_house(void) {
            std::cout << "Make a stone house" << std::endl;
        }
};


#endif



