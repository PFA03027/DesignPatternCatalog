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

#ifndef HOUSE_DESIGN_PROTOTYPE_HPP_
#define HOUSE_DESIGN_PROTOTYPE_HPP_

#include <list>
#include <memory>
#include <string>

class house_prototype {
public:
	house_prototype( void ) {}
	virtual ~house_prototype() {}

	virtual house_prototype* clone( void ) = 0;

	virtual void let_us_see_house( void ) = 0;

protected:
	std::list<std::string> rooms_;
};

#endif   // HOUSE_DESIGN_ORDER_AND_BUILD_HPP_
