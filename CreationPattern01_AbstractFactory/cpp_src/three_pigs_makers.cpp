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

#include <cstdlib>

#include "concrete_factory_stone_housemaker.h"
#include "concrete_factory_straw_housemaker.h"
#include "concrete_factory_wood_housemaker.h"
#include "wolf_attack_story.h"



int main(void)
{
    straw_housemaker    eldest_pig_housemaker;
    wood_housemaker     second_pig_housemaker;
    stone_housemaker    youngest_pig_housemaker;

    wolf_attack_story(&eldest_pig_housemaker);
    wolf_attack_story(&second_pig_housemaker);
    wolf_attack_story(&youngest_pig_housemaker);

    return EXIT_SUCCESS;
}