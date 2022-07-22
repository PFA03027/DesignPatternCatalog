/**
 * @file wood_housemaker.h
 * @author PFA03027@nifty.com
 * @brief Adaptee class as Adapter pattern sample
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef WOOD_HOUSEMAKER_H_
#define WOOD_HOUSEMAKER_H_

#include <iostream>

class wood_housemaker {
    public:
        ~wood_housemaker() {}

        void generate_house(void) {
            std::cout << "Generate a wood house" << std::endl;
        }
};


#endif



