/**
 * @file single_house_maker3.cpp
 * @author PFA03027@nifty.com
 * @brief builder pattern sample implementation
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

#include "three_pigs_house_type.hpp"

void do_house_order_and_build( house_prototype& prototype )
{
	auto p_house = prototype.clone();
	p_house->let_us_see_house();
	delete p_house;
}

int main( void )
{
	elder_house_prototype    eb;
	second_house_prototype   sb;
	youngest_house_prototype yb;

	do_house_order_and_build( eb );
	do_house_order_and_build( sb );
	do_house_order_and_build( yb );

	return EXIT_SUCCESS;
}
