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

#include    <memory>

#include    "construct_custom_home.h"

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
            printf("Wolf is attached. Then, Straw house is broken\n");
        }
};

#endif  // STRAW_HOUSEMAKER_H_
