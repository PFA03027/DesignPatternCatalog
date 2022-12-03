/**
 * @file concrete_factory_stone_housemaker.h
 * @author PFA03027@nifty.com
 * @brief  header file of stone house maker
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef ABSTRACT_FACTORY_STONE_HOUSEMAKER_H_
#define ABSTRACT_FACTORY_STONE_HOUSEMAKER_H_

#include    <cstdio>
#include    <memory>

#include    "abstract_factory_housemaker.h"

class stone_housemaker;

/**
 * @brief 生成物houseの具象クラス
 * 
 */
class stone_house : public abstract_house_product {
    public:
        ~stone_house() {}

        void what_i_am(void) override {
            printf("This is house by Stones\n");
        }

        void wolf_attacked(void) override {
            printf("Wolf is attached. But, Stone house is Not broken\n");
        }
    
    private:
        stone_house(void) {};
    
    friend stone_housemaker;
};

/**
 * @brief 生成物gardenの具象クラス
 * 
 */
class stone_garden : public abstract_garden_product {
    public:
        ~stone_garden() {}
        
        void what_i_am(void) override {
            printf("This is garden by Stones\n");
        }
    
    private:
        stone_garden(void) {};
    
    friend stone_housemaker;
};

/**
 * @brief 生成物house, gardenの生成を担うFactoryクラス
 * 
 */
class stone_housemaker : public abstract_housemaker_factory {
    public:
        ~stone_housemaker() {}

        std::unique_ptr<abstract_house_product> make_house(void) override {
            return std::unique_ptr<abstract_house_product>( new stone_house );
        }
        std::unique_ptr<abstract_garden_product> make_garden(void) override {
            return std::unique_ptr<abstract_garden_product>( new stone_garden );
        }
};

#endif  // ABSTRACT_FACTORY_STONE_HOUSEMAKER_H_
