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

int main(void) {
    house_maker_ctx house_maker;

    house_maker.make_house(std::cout);

    // house_maker_ctx::select_maker()経由で、アルゴリズムを動的に変更する
    house_maker.set_maker(std::make_unique<straw_house_maker>());
    house_maker.make_house(std::cout);

    house_maker.set_maker(std::make_unique<wood_house_maker>());
    house_maker.make_house(std::cout);

    house_maker.set_maker(std::make_unique<stone_house_maker>());
    house_maker.make_house(std::cout);

    return EXIT_SUCCESS;
}
