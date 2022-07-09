/**
 * @file construct_custom_home.h
 * @author PFA03027@nifty.com
 * @brief  header file of construct custom home
 * @version 0.1
 * @date 2022-07-03
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */


#ifndef CONSTRUCT_CUSTOM_HOME_H_
#define CONSTRUCT_CUSTOM_HOME_H_

#include    <functional>
#include    <memory>

/**
 * @brief Factory MethodパターンのProductクラス
 * 
 */
class abstract_house_product {
    public:
        virtual ~abstract_house_product() {}
        virtual void what_i_am(void) = 0;
        virtual void wolf_attacked(void) = 0;
    
    protected:
        abstract_house_product(void) {};
};

/**
 * @brief Factory MethodパターンのCreatorクラス
 * 
 * Productクラスの派生クラスを生成するFactory Method部分をクロージャで実現する。
 * この場合、サブクラス化を必要としない。
 */
class house_constructor {
    public:
        house_constructor(
            std::function<std::unique_ptr<abstract_house_product>(void)>    functor_do_make_house_arg
            )
        : functor_do_make_house_(functor_do_make_house_arg)
        , up_ahp_(nullptr) {}
        virtual ~house_constructor(void) {}

        /**
         * @brief 家をつくり、作った家にオオカミが襲撃する物語を作る。
         * 
         * Factory Methodを使用する関数。
         * この関数自身は、どんな家が建てられるか知らない(クラスが不明)が、実行する物語を実装している。
         */
        void make_story(void) {
            up_ahp_ = functor_do_make_house_();

            up_ahp_->what_i_am();
            up_ahp_->wolf_attacked();

            return;
        }
    
    private:
        std::function<std::unique_ptr<abstract_house_product>(void)>    functor_do_make_house_;
        std::unique_ptr<abstract_house_product> up_ahp_;
};

#endif
