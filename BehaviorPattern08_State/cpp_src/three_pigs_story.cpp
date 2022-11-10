/**
 * @file three_pigs_story.cpp
 * @author PFA03027@nifty.com
 * @brief state pattern implementation file base on three little pigs story
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#include "three_pigs_story.h"

class elder_pig_turn_state : public state {
public:
    bool handle(void) override {
        std::cout << "The wolf blew up the straw house." << std::endl;
        return true;
    }
};

class second_pig_turn_state : public state {
public:
    bool handle(void) override {
        std::cout << "The wolf burned the wooden house." << std::endl;
        return true;
    };
};

class youngest_pig_turn_state : public state {
public:
    bool handle(void) override {
        std::cout << "A wolf could neither blow up nor burn a stone house." << std::endl;
        return true;
    };
};

class end_story_state : public state {
public:
    bool handle(void) override {
        std::cout << "end of story" << std::endl;
        return false;
    };
};




three_pigs_story::three_pigs_story(void) {
    cur_state_idx_ = 0;
    states_.emplace_back(std::make_unique<elder_pig_turn_state>());
    states_.emplace_back(std::make_unique<second_pig_turn_state>());
    states_.emplace_back(std::make_unique<youngest_pig_turn_state>());
    states_.emplace_back(std::make_unique<end_story_state>());
}

three_pigs_story::~three_pigs_story() {
}

void three_pigs_story::request_next(void) {
    bool next_flag = states_[cur_state_idx_]->handle();
    if( next_flag ) {
        cur_state_idx_++;
    }
}
