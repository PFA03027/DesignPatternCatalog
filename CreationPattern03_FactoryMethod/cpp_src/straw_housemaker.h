/**
 * @file straw_housemaker.h
 * @author PFA03027@nifty.com
 * @brief  header file of straw house maker
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef STRAW_HOUSEMAKER_H_
#define STRAW_HOUSEMAKER_H_

#include    <cstdio>
#include    <cstdlib>

#include    <memory>

#include    "construct_custom_home.h"

class straw_housemaker;

/**
 * @brief Productクラスの具象クラス
 * 
 */
class straw_house : public abstract_house_product {
    public:
        straw_house(void) {};
        ~straw_house() {}

        void what_i_am(void) override {
            printf("This is house by Straws\n");
        }

        void wolf_attacked(void) override {
            printf("Wolf is attached. But, Straw house is Not broken\n");
        }
};

/**
 * @brief Factory MethodパターンのConcrete Creatorクラス
 */
class straw_housemaker : public house_constructor {
    protected:
        std::unique_ptr<abstract_house_product> DoMakeHouse(void) override {
            return std::unique_ptr<abstract_house_product>(new straw_house());
        }
};

#endif  // STRAW_HOUSEMAKER_H_
