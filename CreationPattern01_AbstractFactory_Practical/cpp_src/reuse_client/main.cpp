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

#include "abstract_factory_housemaker.h"
#include "wolf_attack_story.h"



int main(void)
{
    auto up_hm = abstract_housemaker_factory::generate_factory();

    wolf_attack_story(std::move(up_hm));

    return EXIT_SUCCESS;
}