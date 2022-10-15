/**
 * @file house_maker_strategy.cpp
 * @author PFA03027@nifty.com
 * @brief header file of Strategy pattern example
 * @version 0.1
 * @date 2022-10-15
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#include <stdexcept>

#include "house_maker_strategy.h"


/////////// Implementation of Context ////////////
bool house_maker_ctx::set_maker(std::function<void(std::ostream& oss)> func) {
    func_ = func;
    return true;
}

void house_maker_ctx::make_house(std::ostream& oss) {
    func_(oss);
    std::cout << std::endl;
}

house_maker_ctx::house_maker_ctx(void) {
    func_ = [](std::ostream& oss) {
        oss << "No pig, No house";
    };
}

house_maker_ctx::~house_maker_ctx() {}
