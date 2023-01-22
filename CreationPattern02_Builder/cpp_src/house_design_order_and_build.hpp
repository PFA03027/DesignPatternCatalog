/**
 * @file house_design_order_and_build.hpp
 * @author PFA03027@nifty.com
 * @brief Interface of builder
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#ifndef HOUSE_DESIGN_ORDER_AND_BUILD_HPP_
#define HOUSE_DESIGN_ORDER_AND_BUILD_HPP_

#include <list>
#include <memory>
#include <string>

class house_object {
public:
	virtual ~house_object() {}
	virtual void let_us_see_house( void ) = 0;
};

class house_builder {
public:
	house_builder( void ) {}
	virtual ~house_builder() {}

	house_builder& order_room( std::string room_name_arg )
	{
		rooms_.emplace_back( room_name_arg );
		return *this;
	}

	virtual std::unique_ptr<house_object> build( void ) = 0;

protected:
	std::list<std::string> rooms_;
};

#endif   // HOUSE_DESIGN_ORDER_AND_BUILD_HPP_
