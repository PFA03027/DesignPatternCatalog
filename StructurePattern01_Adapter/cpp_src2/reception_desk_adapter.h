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
class reception_desk_stone_housemaker : public reception_desk, private stone_housemaker {
public:
    // AdapteeクラスのコンストラクタI/Fの変更に自動的に追従できるように、Adapterクラスのコンストラクタをテンプレート型してみました。
    template<typename... Args>
    reception_desk_stone_housemaker(Args... args)
      : stone_housemaker(std::forward<Args>(args)...)
      {}
    ~reception_desk_stone_housemaker()
    {
    }

    void order_house(void) override
    {
        make_house();   // Adaptee固有のI/Fを使用する
    }

};

/**
 * @brief wood house makerクラスに対するAdapterクラス
 * 
 */
class reception_desk_wood_housemaker : public reception_desk, private wood_housemaker {
public:
    // AdapteeクラスのコンストラクタI/Fの変更に自動的に追従できるように、Adapterクラスのコンストラクタをテンプレート型してみました。
    template<typename... Args>
    reception_desk_wood_housemaker(Args... args)
      : wood_housemaker(std::forward<Args>(args)...)
      {}
    ~reception_desk_wood_housemaker()
    {
    }

    void order_house(void) override
    {
        generate_house();   // Adaptee固有のI/Fを使用する
    }

};

/**
 * @brief straw house makerクラスに対するAdapterクラス
 * 
 */
class reception_desk_straw_housemaker : public reception_desk, private straw_housemaker {
public:
    // AdapteeクラスのコンストラクタI/Fの変更に自動的に追従できるように、Adapterクラスのコンストラクタをテンプレート型してみました。
    template<typename... Args>
    reception_desk_straw_housemaker(Args... args)
      : straw_housemaker(std::forward<Args>(args)...)
      {}
    ~reception_desk_straw_housemaker()
    {
    }

    void order_house(void) override
    {
        create_house();   // Adaptee固有のI/Fを使用する
    }

};

#endif