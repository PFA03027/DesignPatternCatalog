/**
 * @file reception_desk_adapter.h
 * @author PFA03027@nifty.com
 * @brief adapter class header
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#ifndef RECEPTION_DESK_ADAPTER_H_
#define RECEPTION_DESK_ADAPTER_H_

#include <iostream>

#include "stone_housemaker.h"
#include "wood_housemaker.h"
#include "straw_housemaker.h"

/**
 * @brief クライアントが使用するドメイン特化のI/Fを定義するI/Fクラス
 * 
 */
class reception_desk {
public:
    virtual ~reception_desk() = default;

    virtual void order_house(void) = 0;
};

/**
 * @brief stone house makerクラスに対するAdapterクラス
 * 
 */
class reception_desk_stone_housemaker : public reception_desk {
public:
    reception_desk_stone_housemaker(stone_housemaker* p_hm)
      : p_impl(p_hm) // コンポジット方式のAdapterの場合、Adapteeクラスのコンストラクタに関する情報を意識しないことが可能
      {}
    ~reception_desk_stone_housemaker()
    {
        delete p_impl;
    }

    void order_house(void) override
    {
        if( p_impl == nullptr ) { // コンポジット方式のAdapterの場合、p_implチェックが必須。
            std::cout << "This desk has no house maker" << std::endl;
            return;
        }
        p_impl->make_house();   // Adaptee固有のI/Fを使用する
    }

private:
    stone_housemaker*   p_impl;
};

/**
 * @brief wood house makerクラスに対するAdapterクラス
 * 
 */
class reception_desk_wood_housemaker : public reception_desk {
public:
    reception_desk_wood_housemaker(wood_housemaker* p_hm)
      : p_impl(p_hm) // コンポジット方式のAdapterの場合、Adapteeクラスのコンストラクタに関する情報を意識しないことが可能
      {}
    ~reception_desk_wood_housemaker()
    {
        delete p_impl;
    }

    void order_house(void) override
    {
        if( p_impl == nullptr ) { // コンポジット方式のAdapterの場合、p_implチェックが必須。
            std::cout << "This desk has no house maker" << std::endl;
            return;
        }
        p_impl->generate_house();   // Adaptee固有のI/Fを使用する
    }

private:
    wood_housemaker*   p_impl;
};

/**
 * @brief straw house makerクラスに対するAdapterクラス
 * 
 */
class reception_desk_straw_housemaker : public reception_desk {
public:
    reception_desk_straw_housemaker(straw_housemaker* p_hm)
      : p_impl(p_hm) // コンポジット方式のAdapterの場合、Adapteeクラスのコンストラクタに関する情報を意識しないことが可能
      {}
    ~reception_desk_straw_housemaker()
    {
        delete p_impl;
    }

    void order_house(void) override
    {
        if( p_impl == nullptr ) { // コンポジット方式のAdapterの場合、p_implチェックが必須。
            std::cout << "This desk has no house maker" << std::endl;
            return;
        }
        p_impl->create_house();   // Adaptee固有のI/Fを使用する
    }

private:
    straw_housemaker*   p_impl;
};

#endif