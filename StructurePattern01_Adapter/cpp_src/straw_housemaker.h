/**
 * @file straw_housemaker.h
 * @author PFA03027@nifty.com
 * @brief Adaptee class as Adapter pattern sample
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef STRAW_HOUSEMAKER_H_
#define STRAW_HOUSEMAKER_H_

#include <iostream>

class straw_housemaker {
    public:
        ~straw_housemaker() {}

        void create_house(void) {
            std::cout << "create a straw house" << std::endl;
        }
};


#endif



