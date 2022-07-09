/**
 * @file three_pigs_makers.cpp
 * @author PFA03027@nifty.com
 * @brief  main
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#include "stone_housemaker.h"
#include "straw_housemaker.h"
#include "wood_housemaker.h"

#include    "construct_custom_home.h"


int main(void)
{
    house_constructor    eldest_pig_housemaker([]() -> std::unique_ptr<abstract_house_product> {
        return std::unique_ptr<abstract_house_product>(new straw_house());
    });
    house_constructor     second_pig_housemaker([]() -> std::unique_ptr<abstract_house_product> {
        return std::unique_ptr<abstract_house_product>(new wood_house());
    });
    house_constructor    youngest_pig_housemaker([]() -> std::unique_ptr<abstract_house_product> {
        return std::unique_ptr<abstract_house_product>(new stone_house());
    });

    eldest_pig_housemaker.make_story();
    second_pig_housemaker.make_story();
    youngest_pig_housemaker.make_story();

    return EXIT_SUCCESS;
}
