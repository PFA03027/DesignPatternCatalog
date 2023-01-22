/**
 * @file single_house_maker3.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * 生成するSingletonの型を実行時に決定する必要がある場合、cpp_srcのget_instance()に対して、少し工夫が必要です。
 * このサンプルは、その決定を環境変数で行う例です。
 *
 * 環境変数SELECT_HOUSEMAKERの値が"elder"の場合、straw_house_makerのインスタンスがSingletonとして生成されます。
 * 環境変数SELECT_HOUSEMAKERの値が"second"の場合、wood_house_makerのインスタンスがSingletonとして生成されます。
 * 環境変数SELECT_HOUSEMAKERの値が"youngest"の場合、stone_house_makerのインスタンスがSingletonとして生成されます。
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

#include "single_house_maker3.hpp"

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
		const char* env_val = getenv( "SELECT_HOUSEMAKER" );
		if ( env_val == nullptr ) {
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
