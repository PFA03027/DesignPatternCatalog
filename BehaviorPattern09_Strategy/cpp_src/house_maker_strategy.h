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
 * パターンの利用者は、ContextクラスのI/Fからアルゴリズムを動的に変更できます。
 * StrategyパターンのAbstractクラスとConcreteクラスはcppで実装され、パターンの利用者からは隠蔽する実装としています。
 * こうすることで、実装の詳細を隠蔽し、かつアルゴリズムの動的な変更を実現します。
 * 
 * 実装の詳細をパターンの利用者側が指定したケースのサンプルは、cpp_src2を参照してください。
 */

#ifndef HOUSE_MAKER_STRATEGY_H_
#define HOUSE_MAKER_STRATEGY_H_

#include <memory>
#include <iostream>
#include <sstream>

class house_maker_base;

class house_maker_ctx {
public:
    enum Alg_t {
        Eldest_Pig,
        Second_Pig,
        Youngest_Pig,
    };

    house_maker_ctx(Alg_t at);
    ~house_maker_ctx();

    void select_maker(Alg_t at);
    void make_house(std::ostream& oss);

private:
    std::unique_ptr<house_maker_base>   up_hmb_;
};


#endif
