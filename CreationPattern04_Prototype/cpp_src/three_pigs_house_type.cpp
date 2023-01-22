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

#include "three_pigs_house_type.hpp"

////////////////////////////////////////////
elder_house_prototype::elder_house_prototype( void )
{
	rooms_.emplace_back( "living" );
	rooms_.emplace_back( "dining" );
	rooms_.emplace_back( "garden" );
}

elder_house_prototype::elder_house_prototype( const elder_house_prototype& orig )
  : rooms_( orig.rooms_ )
{
}

house_prototype* elder_house_prototype::clone( void )
{
	return new elder_house_prototype( *this );
}

void elder_house_prototype::let_us_see_house( void )
{
	std::cout << "Ordered House is made by straw. And it has below rooms;" << std::endl;
	for ( auto& e : rooms_ ) {
		std::cout << "\t" << e << std::endl;
	}
}

////////////////////////////////////////////
second_house_prototype::second_house_prototype( void )
{
	rooms_.emplace_back( "living" );
	rooms_.emplace_back( "dining" );
	rooms_.emplace_back( "kitchen" );
	rooms_.emplace_back( "study room" );
}

second_house_prototype::second_house_prototype( const second_house_prototype& orig )
  : rooms_( orig.rooms_ )
{
}

house_prototype* second_house_prototype::clone( void )
{
	return new second_house_prototype( *this );
}

void second_house_prototype::let_us_see_house( void )
{
	std::cout << "Ordered House is made by wood. And it has below rooms;" << std::endl;
	for ( auto& e : rooms_ ) {
		std::cout << "\t" << e << std::endl;
	}
}

////////////////////////////////////////////
youngest_house_prototype::youngest_house_prototype( void )
{
	rooms_.emplace_back( "living" );
	rooms_.emplace_back( "dining" );
	rooms_.emplace_back( "kitchen" );
	rooms_.emplace_back( "study room" );
	rooms_.emplace_back( "chimney" );
}

youngest_house_prototype::youngest_house_prototype( const youngest_house_prototype& orig )
  : rooms_( orig.rooms_ )
{
}

house_prototype* youngest_house_prototype::clone( void )
{
	return new youngest_house_prototype( *this );
}

void youngest_house_prototype::let_us_see_house( void )
{
	std::cout << "Ordered House is made by stone. And it has below rooms;" << std::endl;
	for ( auto& e : rooms_ ) {
		std::cout << "\t" << e << std::endl;
	}
}
