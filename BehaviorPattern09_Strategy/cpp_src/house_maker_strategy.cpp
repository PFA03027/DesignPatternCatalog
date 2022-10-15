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

/////////// Implementation of Strategy class ////////////
/**
 * @brief StrategyパターンのAbstractクラス
 * 
 */
class house_maker_base {
public:
    virtual void make_house(std::ostream& oss) = 0;

    virtual ~house_maker_base() {}
};

/////////// Implementation of Concrete Strategy class ////////////
/**
 * @brief Strategyパターンの、Abastractクラスhouse_maker_baseに対する具象化クラス
 * 
 */
class straw_house_maker : public house_maker_base {
    public:
    void make_house(std::ostream& oss) override {
        oss << "This is straw house";

    }
};

/**
 * @brief Strategyパターンの、Abastractクラスhouse_maker_baseに対する具象化クラス
 * 
 */
class wood_house_maker : public house_maker_base {
    public:
    void make_house(std::ostream& oss) override {
        oss << "This is wood house";

    }
};

/**
 * @brief Strategyパターンの、Abastractクラスhouse_maker_baseに対する具象化クラス
 * 
 */
class stone_house_maker : public house_maker_base {
    public:
    void make_house(std::ostream& oss) override {
        oss << "This is stone house";

    }
};


/////////// Implementation of Context ////////////
void house_maker_ctx::select_maker(Alg_t at) {
    switch(at) {
        case Eldest_Pig: {
            up_hmb_ = std::make_unique<straw_house_maker>();
        } break;
        case Second_Pig: {
            up_hmb_ = std::make_unique<wood_house_maker>();
        } break;
        case Youngest_Pig: {
            up_hmb_ = std::make_unique<stone_house_maker>();
        } break;

        default: {
            throw std::range_error("Unknown enum value of house_maker_ctx::Alg_t");
        };
    }
}

void house_maker_ctx::make_house(std::ostream& oss) {
    up_hmb_->make_house(oss);
    std::cout << std::endl;
}

house_maker_ctx::house_maker_ctx(Alg_t at) {
    select_maker(at);
}

house_maker_ctx::~house_maker_ctx() {}
