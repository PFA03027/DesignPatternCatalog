/**
 * @file wolf_attack_story.cpp
 * @author PFA03027@nifty.com
 * @brief implementation of wolf attack story
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */


#include "wolf_attack_story.h"

/**
 * @brief 家を立てた後に、オオカミが攻撃してくるというお話
 * 
 * @param p_hf 
 */
void wolf_attack_story(abstract_housemaker_factory* p_hf )
{
    std::unique_ptr<abstract_house_product> up_house_obj = p_hf->make_house();
    std::unique_ptr<abstract_garden_product> up_garden_obj = p_hf->make_garden();

    up_house_obj->what_i_am();
    up_garden_obj->what_i_am();

    up_house_obj->wolf_attacked();

    return;
}


