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
            printf("Wolf is attached. Then, Wood house is broken\n");
        }
};

#endif  // WOOD_HOUSEMAKER_H_
