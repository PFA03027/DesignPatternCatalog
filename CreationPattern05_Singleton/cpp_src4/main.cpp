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

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>

#include "single_house_maker4.hpp"

void access_singleton( void )
{
	std::cout << "Access start a singleton" << std::endl;
	house_maker::get_instance().print_i_am();
	house_maker::get_instance().print_i_am();   // 複数回呼び出しても2個目のインスタンスが生成されないことを確認する。
}

int main( void )
{
	std::thread t1( access_singleton );
	std::thread t2( access_singleton );

	std::this_thread::sleep_for( std::chrono::seconds( 2 ) );
	std::cout << "finish waiting for a paramter of singleton creation" << std::endl;
	house_maker::inject_paramter( getenv( "SELECT_HOUSEMAKER" ) );

	t1.join();
	t2.join();
	return EXIT_SUCCESS;
}
