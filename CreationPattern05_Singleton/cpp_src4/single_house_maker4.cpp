/**
 * @file single_house_maker3.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * cpp_src3は、生成するSingletonの型が実行時に静的な情報で決定できる場合に適用できるサンプルでした。
 * 静的に決定できない場合、つまり決定に使用する情報が外部のプロセスから提供される情報に依存する等、
 * ある程度処理を実行してから決定可能になる場合はどうすればよいでしょうか？
 * シングルスレッドであれば簡単です。Singletonにアクセスしなければよいだけです。
 * マルチスレッドの場合は、ちょっと工夫が必要です。
 *
 * また、どうやって決定に使用する情報をSingletonの生成前に渡せばよいでしょうか？
 * get_instance()の引数で呼び出し毎に渡すわけにもいきません。
 *
 * 実現方法はいろいろあると思いますが、
 * このサンプルは、「決定可能になるまで他スレッドを待たせることができる」という制約をつけて、
 * future/promiseを使用してSingletonの生成を待機させる方法で実現してみました。
 * Singletonの生成に必要な情報は、inject_paramter()でSingleton側へ知らせるという実装です。
 */

#include <cstdlib>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

#include "single_house_maker4.hpp"

std::promise<std::string> house_maker::singleton_param_promise_;
std::future<std::string>  house_maker::singleton_param_future_ = singleton_param_promise_.get_future();

house_maker::house_maker( void )
{
}

house_maker::~house_maker()
{
	// デストラクタがClose戦略を担う。
	std::cout << "e.g., close file discriptor" << std::endl;
}

class straw_house_maker : public house_maker {
public:
	straw_house_maker( void )
	{
	}
	void print_i_am( void ) override
	{
		std::lock_guard<std::mutex> lk( mtx_ );
		std::cout << "This singleton house maker is straw_house_maker, 0x" << this << std::endl;
	}
};

class wood_house_maker : public house_maker {
public:
	wood_house_maker( void )
	{
	}
	void print_i_am( void ) override
	{
		std::lock_guard<std::mutex> lk( mtx_ );
		std::cout << "This singleton house maker is wood_house_maker, 0x" << this << std::endl;
	}
};

class stone_house_maker : public house_maker {
public:
	stone_house_maker( void )
	{
	}
	void print_i_am( void ) override
	{
		std::lock_guard<std::mutex> lk( mtx_ );
		std::cout << "This singleton house maker is stone_house_maker, 0x" << this << std::endl;
	}
};

house_maker& house_maker::get_instance( void )
{
	auto singleton_factory = []() {
		std::string env_val = singleton_param_future_.get();
		if ( env_val == std::string( "" ) ) {
			throw std::runtime_error( std::string( "not set SELECT_HOUSEMAKER" ) );
		}

		std::unique_ptr<house_maker> up_ans = nullptr;
		if ( std::string( "elder" ) == std::string( env_val ) ) {
			up_ans = std::make_unique<straw_house_maker>();
		} else if ( std::string( "second" ) == std::string( env_val ) ) {
			up_ans = std::make_unique<wood_house_maker>();
		} else if ( std::string( "youngest" ) == std::string( env_val ) ) {
			up_ans = std::make_unique<stone_house_maker>();
		} else {
			throw std::runtime_error( std::string( env_val ) );
		}
		return up_ans;
	};
	static std::unique_ptr<house_maker> up_singleton = singleton_factory();
	return *up_singleton;
}

void house_maker::inject_paramter( const char* p_param_arg )
{
	std::string param = std::string( ( p_param_arg == nullptr ) ? "" : p_param_arg );
	singleton_param_promise_.set_value( std::move( param ) );
}
