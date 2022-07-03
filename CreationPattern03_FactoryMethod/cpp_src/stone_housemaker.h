/**
 * @file stone_housemaker.h
 * @author PFA03027@nifty.com
 * @brief  header file of stone house maker
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef STONE_HOUSEMAKER_H_
#define STONE_HOUSEMAKER_H_

#include    <memory>

#include    "construct_custom_home.h"

class stone_housemaker;

/**
 * @brief Productクラスの具象クラス
 * 
 */
class stone_house : public abstract_house_product {
    public:
        stone_house(void) {};
        ~stone_house() {}

        void what_i_am(void) override {
            printf("This is house by Stones\n");
        }

        void wolf_attacked(void) override {
            printf("Wolf is attached. But, Stone house is Not broken\n");
        }
};

/**
 * @brief Factory MethodパターンのConcrete Creatorクラス
 */
class stone_housemaker : public house_constructor {
    protected:
        std::unique_ptr<abstract_house_product> DoMakeHouse(void) override {
            return std::unique_ptr<abstract_house_product>(new stone_house());
        }
};

#endif  // STONE_HOUSEMAKER_H_
