/**
 * @file chain_of_responsibility.h
 * @author PFA03027@nifty.com
 * @brief Chain of responsibility pattern
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * Chain of responsibilityパターンのベースとなるハンドラクラスです。
 * サンプルなので、successorの所有権は持たせていません。
 * この辺りは、実際の実装コードの設計次第ですね。
 * 
 * また、successorの実現に、std::list<T>のT型にハンドラ機能を付ける実装方法も考えられますね。
 * 
 */


#ifndef CHAIN_OF_RESPONSIBILITY_H_
#define CHAIN_OF_RESPONSIBILITY_H_

#include <string>

class request_handler {
public:
    request_handler(void)
    : p_successor_(nullptr) {}

    void set_successor(request_handler* p_successor_arg) {
        p_successor_ = p_successor_arg;
    }

    virtual void handle( std::string req_str) {
        if( p_successor_ != nullptr ) {
            p_successor_->handle( req_str );
        }
    }
private:
    request_handler* p_successor_;
};



#endif
