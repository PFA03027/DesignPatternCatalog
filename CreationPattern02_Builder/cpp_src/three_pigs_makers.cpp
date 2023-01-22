/**
 * @file three_pigs_makers.cpp
 * @author PFA03027@nifty.com
 * @brief Implementation of concrete class of builder
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "three_pigs_makers.hpp"

class pigs_house : public house_object {
public:
	pigs_house( const std::string& material_arg, std::list<std::string>&& rooms_arg )
	  : material_( material_arg )
	  , rooms_( std::move( rooms_arg ) )
	{
	}

	void let_us_see_house( void ) override
	{
		std::cout << "Ordered House is made by " << material_ << ". And it has below rooms;" << std::endl;
		for ( auto& e : rooms_ ) {
			std::cout << "\t" << e << std::endl;
		}
	}

private:
	std::string            material_;
	std::list<std::string> rooms_;
};

std::unique_ptr<house_object> elder_house_builder::build( void )
{
	return std::make_unique<pigs_house>( "straw", std::move( rooms_ ) );
}

std::unique_ptr<house_object> second_house_builder::build( void )
{
	return std::make_unique<pigs_house>( "wood", std::move( rooms_ ) );
}

std::unique_ptr<house_object> youngest_house_builder::build( void )
{
	return std::make_unique<pigs_house>( "stone", std::move( rooms_ ) );
}
