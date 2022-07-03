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



int main(void)
{
    straw_housemaker    eldest_pig_housemaker;
    wood_housemaker     second_pig_housemaker;
    stone_housemaker    youngest_pig_housemaker;

    eldest_pig_housemaker.make_story();
    second_pig_housemaker.make_story();
    youngest_pig_housemaker.make_story();

    return EXIT_SUCCESS;
}
