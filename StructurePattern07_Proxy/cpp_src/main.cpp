/**
 * @file main.cpp
 * @author PFA03027@nifty.com
 * @brief Main function implementation
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#include <iostream>

#include "three_pings_text_object.hpp"

int main( void )
{
	auto up_obj = text_object::make_text_object( obj_id::kId_ElderPigHouse );
	std::cout << up_obj->c_string_pointer() << std::endl;

	up_obj = text_object::make_text_object( obj_id::kId_2ndPigHouse );
	std::cout << up_obj->c_string_pointer() << std::endl;

	up_obj = text_object::make_text_object( obj_id::kId_YoungestPigHouse );
	std::cout << up_obj->c_string_pointer() << std::endl;

	return EXIT_SUCCESS;
}