/**
 * @file wood_housemaker.h
 * @author PFA03027@nifty.com
 * @brief  header file of wood house maker
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef WOOD_HOUSEMAKER_H_
#define WOOD_HOUSEMAKER_H_

#include    <memory>

#include    "construct_custom_home.h"

class wood_housemaker;

/**
 * @brief Productクラスの具象クラス
 * 
 */
class wood_house : public abstract_house_product {
    public:
        wood_house(void) {};
        ~wood_house() {}

        void what_i_am(void) override {
            printf("This is house by Woods\n");
        }

        void wolf_attacked(void) override {
            printf("Wolf is attached. But, Wood house is Not broken\n");
        }
};

/**
 * @brief Factory MethodパターンのConcrete Creatorクラス
 */
class wood_housemaker : public house_constructor {
    protected:
        std::unique_ptr<abstract_house_product> DoMakeHouse(void) override {
            return std::unique_ptr<abstract_house_product>(new wood_house());
        }
};

#endif  // WOOD_HOUSEMAKER_H_
