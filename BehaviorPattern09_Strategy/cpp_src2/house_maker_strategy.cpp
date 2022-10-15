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

/**
 * @brief NULLオブジェクトとしての具象化クラス
 * 
 */
class no_house_maker : public house_maker_base {
    public:
    void make_house(std::ostream& oss) override {
        oss << "No pig, No house";

    }
};


/////////// Implementation of Context ////////////
bool house_maker_ctx::set_maker(std::unique_ptr<house_maker_base>   up_hmb_arg) {
    if( up_hmb_arg == nullptr) return false;

    up_hmb_ = std::move(up_hmb_arg);
    return true;
}

void house_maker_ctx::make_house(std::ostream& oss) {
    up_hmb_->make_house(oss);
    std::cout << std::endl;
}

house_maker_ctx::house_maker_ctx(void) {
    up_hmb_ = std::make_unique<no_house_maker>();
}

house_maker_ctx::~house_maker_ctx() {}
