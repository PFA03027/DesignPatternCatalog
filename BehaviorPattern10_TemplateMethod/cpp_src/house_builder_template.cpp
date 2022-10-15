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

#include "house_maker_template.h"

/**
 * @brief Template Methodのpatternの具象クラス
 * 
 */
class straw_house_maker : public house_maker_base {
protected:
    std::string get_maker_name(void) override {
        return "Eldest pig";
    }
    std::string get_material(void) override {
        return "straw";
    }
};

/**
 * @brief Template Methodのpatternの具象クラス
 * 
 */
class wood_house_maker : public house_maker_base {
protected:
    std::string get_maker_name(void) override {
        return "2nd pig";
    }
    std::string get_material(void) override {
        return "wood";
    }
};

/**
 * @brief Template Methodのpatternの具象クラス
 * 
 */
class stone_house_maker : public house_maker_base {
protected:
    std::string get_maker_name(void) override {
        return "Youngest pig";
    }
    std::string get_material(void) override {
        return "stone";
    }
};

/**
 * @brief Template Methodのpatternの具象クラス
 * 
 */
class wolf_attack : public house_maker_base {
protected:
    std::string get_maker_name(void) override {
        return "Wolf";
    }
    std::string get_material(void) override {
        return "stone";
    }
    std::string get_verb(void) override {
        return " try break ";
    }
    std::string hook_tail(void) override {
        return ", but fail";
    }
};


/**
 * @brief make_house()を呼び出す
 * 
 * @param p_hm_arg 
 */
void do_make_house(house_maker_base* p_hm_arg) {
    p_hm_arg->make_house(std::cout);
    std::cout << std::endl;
}

int main(void) {
    straw_house_maker house_maker1;
    wood_house_maker  house_maker2;
    stone_house_maker house_maker3;
    wolf_attack       wolf_breaker;

    // ベースクラスで定義されたアルゴリズム(ここではhouse_maker_base::make_house())を動かす
    do_make_house(&house_maker1);
    do_make_house(&house_maker2);
    do_make_house(&house_maker3);
    do_make_house(&wolf_breaker);

    return EXIT_SUCCESS;
}
