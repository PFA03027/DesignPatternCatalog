/**
 * @file chain_of_responsibility2.h
 * @author PFA03027@nifty.com
 * @brief Chain of responsibility pattern
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * ハンドラクラス自身にsuccessorの呼び出しを行う形ではなく、chainを追跡する関数からハンドラクラスのハンドラを呼び出す構造としたものです。
 * handle()は、次のsuccessorへ処理を引き継ぐ場合は、trueを、処理を完了する場合はfalseを返す仕様として定義しています。
 */


#ifndef CHAIN_OF_RESPONSIBILITY2_H_
#define CHAIN_OF_RESPONSIBILITY2_H_

#include <string>

class request_handler {
public:
    request_handler(void)
    : p_successor_(nullptr) {}

    void set_successor(request_handler* p_successor_arg) {
        p_successor_ = p_successor_arg;
    }

    virtual bool handle(std::string req_str) {
        return true;
    }

    static void handle_chain(request_handler* p_top, std::string req_str);

private:
    request_handler* p_successor_;
};

inline void request_handler::handle_chain(request_handler* p_top, std::string req_str) {
    request_handler* p_cur = p_top;
    while( p_cur != nullptr ) {
        bool ret = p_cur->handle(req_str);
        if( ret == false ) {
            break;
        }
        p_cur = p_cur->p_successor_;
    }
}


#endif
