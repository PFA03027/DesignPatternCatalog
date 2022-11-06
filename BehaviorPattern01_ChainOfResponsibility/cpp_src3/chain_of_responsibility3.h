/**
 * @file chain_of_responsibility3.h
 * @author PFA03027@nifty.com
 * @brief Chain of responsibility pattern
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * ハンドラクラス自身にsuccessorの呼び出しを行う形ではなく、chainを追跡する関数からハンドラクラスのハンドラを呼び出す構造としたものです。
 * handle()は、次のsuccessorへ処理を引き継ぐ場合は、trueを、処理を完了する場合はfalseを返す仕様として定義しています。
 * 
 * また、cpp_src/cpp_src2とは異なり、chain構造をstd::listで構築した実装になります。
 */


#ifndef CHAIN_OF_RESPONSIBILITY3_H_
#define CHAIN_OF_RESPONSIBILITY3_H_

#include <string>
#include <list>

class request_handler {
public:
    request_handler(void) {}

    virtual bool handle(std::string req_str) {
        return true;
    }

    static void handle_chain(std::list<request_handler*>& list, std::string req_str);
};

inline void request_handler::handle_chain(std::list<request_handler*>& list, std::string req_str) {
    for( auto&& p_rh : list ) {
        bool ret = p_rh->handle(req_str);
        if( ret == false ) {
            break;
        }
    }
}


#endif
