/**
 * @file house_builder_strategy.cpp
 * @author PFA03027@nifty.com
 * @brief Strategy pattern example
 * @version 0.1
 * @date 2022-10-15
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */
#include <stdlib.h>

#include <string>
#include <iostream>
#include <sstream>

#include "house_maker_strategy.h"


int main(void) {
    house_maker_ctx house_maker(house_maker_ctx::Eldest_Pig);

    house_maker.make_house(std::cout);

    // house_maker_ctx::select_maker()経由で、アルゴリズムを動的に変更する
    house_maker.select_maker(house_maker_ctx::Second_Pig);
    house_maker.make_house(std::cout);

    house_maker.select_maker(house_maker_ctx::Youngest_Pig);
    house_maker.make_house(std::cout);

    return EXIT_SUCCESS;
}
