/**
 * @file single_house_maker3.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * single_house_maker3.cpp を参照ください
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

#include "single_house_maker3.hpp"

int main( void )
{
	house_maker::get_instance().print_i_am();
	house_maker::get_instance().print_i_am();   // 複数回呼び出しても2個目のインスタンスが生成されないことを確認する。
	return EXIT_SUCCESS;
}
