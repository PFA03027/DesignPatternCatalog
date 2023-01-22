/**
 * @file three_pigs_makers.hpp
 * @author PFA03027@nifty.com
 * @brief Concrete class of builder
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#ifndef THREE_PIGS_MAKERS_HPP_
#define THREE_PIGS_MAKERS_HPP_

#include "house_design_order_and_build.hpp"

class elder_house_builder : public house_builder {
public:
	std::unique_ptr<house_object> build( void ) override;
};

class second_house_builder : public house_builder {
public:
	std::unique_ptr<house_object> build( void ) override;
};

class youngest_house_builder : public house_builder {
public:
	std::unique_ptr<house_object> build( void ) override;
};

#endif   // THREE_PIGS_MAKERS_HPP_
