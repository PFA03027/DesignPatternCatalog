/**
 * @file wolf_attack_story.h
 * @author PFA03027@nifty.com
 * @brief header file of wolf attack story
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */


#ifndef WOLF_ATTACK_STORY_H_
#define WOLF_ATTACK_STORY_H_

#include "abstract_factory_housemaker.h"

/**
 * @brief 家を立てた後に、オオカミが攻撃してくるというお話
 * 
 * @param p_hf 
 */
void wolf_attack_story(std::unique_ptr<abstract_housemaker_factory> up_hf);



#endif  // WOLF_ATTACK_STORY_H_
