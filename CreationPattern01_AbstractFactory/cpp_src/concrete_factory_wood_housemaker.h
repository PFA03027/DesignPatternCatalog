/**
 * @file concrete_factory_wood_housemaker.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef ABSTRACT_FACTORY_WOOD_HOUSEMAKER_H_
#define ABSTRACT_FACTORY_WOOD_HOUSEMAKER_H_

#include    <cstdio>
#include    <cstdlib>

#include    <memory>

#include    "abstract_factory_housemaker.h"

class wood_housemaker;

/**
 * @brief 生成物houseの具象クラス
 * 
 */
class wood_house : public abstract_house_product {
    public:
        ~wood_house() {}

        void what_i_am(void) override {
            printf("This is house by Woods\n");
        }

        void wolf_attacked(void) override {
            printf("Wolf is attached. Then, Wood house is broken\n");
        }
    
    private:
        wood_house(void) {};
    
    friend wood_housemaker;
};

/**
 * @brief 生成物gardenの具象クラス
 * 
 */
class wood_garden : public abstract_garden_product {
    public:
        ~wood_garden() {}
        
        void what_i_am(void) override {
            printf("This is garden by Woods\n");
        }
    
    private:
        wood_garden(void) {};
    
    friend wood_housemaker;
};

/**
 * @brief 生成物house, gardenの生成を担うFactoryクラス
 * 
 */
class wood_housemaker : public abstract_housemaker_factory {
    public:
        ~wood_housemaker() {}

        std::unique_ptr<abstract_house_product> make_house(void) override {
            return std::unique_ptr<abstract_house_product>( new wood_house );
        }
        std::unique_ptr<abstract_garden_product> make_garden(void) override {
            return std::unique_ptr<abstract_garden_product>( new wood_garden );
        }
};

#endif  // ABSTRACT_FACTORY_WOOD_HOUSEMAKER_H_
