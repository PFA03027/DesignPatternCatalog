/**
 * @file house_maker_strategy.h
 * @author PFA03027@nifty.com
 * @brief header file of Strategy pattern example
 * @version 0.1
 * @date 2022-10-15
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * Strategyパターンが提供するContextクラスと、Abstractクラスのヘッダファイル
 * パターンの利用者は、ContextクラスのI/Fからアルゴリズムを設定することで動的に変更します。
 * StrategyパターンのConcreteクラスは、パターンの利用者が実装しContextクラスに指定する実装としています。
 * こうすることで、実装の詳細を利用者側にゆだね、アルゴリズムの動的な変更を実現しています。
 * 
 * このサンプルのように、Strategyクラスが必要とするI/Fが１つの場合、ベースクラスを使用せずlambda関数を使用する方法もあります。
 * cpp_src3を参照してください。
 */

#ifndef HOUSE_MAKER_STRATEGY_H_
#define HOUSE_MAKER_STRATEGY_H_

#include <memory>
#include <iostream>
#include <sstream>

/////////// Strategy class ////////////
/**
 * @brief StrategyパターンのAbstractクラス
 * 
 */
class house_maker_base {
public:
    virtual void make_house(std::ostream& oss) = 0;

    virtual ~house_maker_base() {}
};


/////////// Context class ////////////
class house_maker_ctx {
public:
    house_maker_ctx(void);
    ~house_maker_ctx();

    bool set_maker(std::unique_ptr<house_maker_base>   up_hmb_arg);
    void make_house(std::ostream& oss);

private:
    std::unique_ptr<house_maker_base>   up_hmb_;
};


#endif
