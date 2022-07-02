/**
 * @file abstract_factory_housemaker.h
 * @author PFA03027@nifty.com
 * @brief  header file of abstract factory
 * @version 0.1
 * @date 2022-06-26
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * @note
 * abstract house maker factoryクラスからだけ、productが生成できるように制約するため、
 * 生成物クラスのコンストラクタをprotected関数とする実装としてみた。
 * このような制約を課す必要があるかどうかは、実際のソフト要件次第。
 */

#ifndef ABSTRACT_FACTORY_HOUSEMAKER_H_
#define ABSTRACT_FACTORY_HOUSEMAKER_H_

#include    <memory>

class abstract_housemaker_factory;

/**
 * @brief 生成物houseの仮想基本クラス
 * 
 */
class abstract_house_product {
    public:
        virtual ~abstract_house_product() {}
        virtual void what_i_am(void) = 0;
        virtual void wolf_attacked(void) = 0;
    
    protected:
        abstract_house_product(void) {};
    
    friend abstract_housemaker_factory;
};

/**
 * @brief 生成物gardenの仮想基本クラス
 * 
 */
class abstract_garden_product {
    public:
        virtual ~abstract_garden_product() {}
        virtual void what_i_am(void) = 0;
    
    protected:
        abstract_garden_product(void) {};
    
    friend abstract_housemaker_factory;
};

/**
 * @brief 生成物house, gardenの生成を担うFactoryクラス
 * 
 */
class abstract_housemaker_factory {
    public:
        virtual ~abstract_housemaker_factory() {}
        virtual std::unique_ptr<abstract_house_product> make_house(void) = 0;
        virtual std::unique_ptr<abstract_garden_product> make_garden(void) = 0;
};

#endif  // ABSTRACT_FACTORY_HOUSEMAKER_H_
