/**
 * @file house_maker_strategy.h
 * @author PFA03027@nifty.com
 * @brief header file of Strategy pattern example
 * @version 0.1
 * @date 2022-10-15
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * Strategyパターンが提供するContextクラスのヘッダファイル
 * パターンの利用者は、ContextクラスのI/Fからアルゴリズムをlambda関数で設定することで動的に変更します。
 * StrategyパターンのConcreteクラスは、パターンの利用者がlambda関数で実装しContextクラスに指定する実装としています。
 * こうすることで、Strategyクラス、ConcreteStrategyクラスを定義せず、
 * 実装の詳細を利用者側にゆだね、アルゴリズムの動的な変更を実現しています。
 */

#ifndef HOUSE_MAKER_STRATEGY_H_
#define HOUSE_MAKER_STRATEGY_H_

#include <memory>
#include <iostream>
#include <sstream>
#include <functional>


/////////// Context class ////////////
class house_maker_ctx {
public:
    house_maker_ctx(void);
    ~house_maker_ctx();

    bool set_maker(std::function<void(std::ostream& oss)> func);
    void make_house(std::ostream& oss);

private:
    std::function<void(std::ostream& oss)> func_;
};


#endif
