/**
 * @file single_house_maker3.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * single_house_maker4.cpp を参照ください
 */

#ifndef SINGLE_HOUSE_MAKER3_HPP_
#define SINGLE_HOUSE_MAKER3_HPP_

#include <cstdlib>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>

class house_maker {
public:
	static house_maker& get_instance( void );
	static void         inject_paramter( const char* );

	virtual void print_i_am( void ) = 0;

	virtual ~house_maker();

protected:
	// 派生クラスがコンストラクタ、デストラクタを呼び出せるように、protected関数とする。
	house_maker( void );

	mutable std::mutex mtx_;   // house_makerクラスのインスタンスを保護するためのmutex

private:
	house_maker( const house_maker& )            = delete;
	house_maker( house_maker&& )                 = delete;
	house_maker& operator=( const house_maker& ) = delete;
	house_maker& operator=( house_maker&& )      = delete;

	static std::promise<std::string> singleton_param_promise_;
	static std::future<std::string>  singleton_param_future_;
};

#endif
