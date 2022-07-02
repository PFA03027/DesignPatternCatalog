/**
 * @file concrete_factory_straw_housemaker.h
 * @author PFA03027@nifty.com
 * @brief  header file of straw house maker
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */


#ifndef ABSTRACT_FACTORY_STRAW_HOUSEMAKER_H_
#define ABSTRACT_FACTORY_STRAW_HOUSEMAKER_H_

#include    <memory>

#include    "abstract_factory_housemaker.h"

class straw_housemaker;

/**
 * @brief 生成物houseの具象クラス
 * 
 */
class straw_house : public abstract_house_product {
    public:
        ~straw_house() {}

        void what_i_am(void) override {
            printf("This is house by Straws\n");
        }

        void wolf_attacked(void) override {
            printf("Wolf is attached. Then, Straw house is broken\n");
        }
    
    private:
        straw_house(void) {};
    
    friend straw_housemaker;
};

/**
 * @brief 生成物gardenの具象クラス
 * 
 */
class straw_garden : public abstract_garden_product {
    public:
        ~straw_garden() {}
        
        void what_i_am(void) override {
            printf("This is garden by Straws\n");
        }
    
    private:
        straw_garden(void) {};
    
    friend straw_housemaker;
};

/**
 * @brief 生成物house, gardenの生成を担うFactoryクラス
 * 
 */
class straw_housemaker : public abstract_housemaker_factory {
    public:
        ~straw_housemaker() {}

        std::unique_ptr<abstract_house_product> make_house(void) override {
            return std::unique_ptr<abstract_house_product>( new straw_house );
        }
        std::unique_ptr<abstract_garden_product> make_garden(void) override {
            return std::unique_ptr<abstract_garden_product>( new straw_garden );
        }
};

#endif  // ABSTRACT_FACTORY_STRAW_HOUSEMAKER_H_
