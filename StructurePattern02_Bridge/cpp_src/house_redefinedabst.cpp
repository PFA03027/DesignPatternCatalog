/**
 * @file house_redefinedabst.cpp
 * @brief abstraction class header of Bridge pattern
 * @version 0.1
 * @date 2023-02-19
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Bridgeパターンの実装サンプル
 *
 * このソースファイルは、BridgeパターンのRedefinedAbstractionクラスを定義したファイル。
 *
 */

#include <iostream>

#include "house_abst.hpp"
#include "house_impl.hpp"

house_abst::house_abst( house_impl* p_hi_arg )
  : p_hi_( p_hi_arg )
{
}

house_abst::~house_abst()
{
	delete p_hi_;
}

house_impl* house_abst::get_house_impl( void )
{
	return p_hi_;
}

class three_little_pigs_house : public house_abst {
public:
	three_little_pigs_house( house_impl* p_hi_arg )
	  : house_abst( p_hi_arg )
	{
	}
	~three_little_pigs_house() override = default;

	void WhatCommentMotherPigSaid( void ) override
	{
		if ( get_house_impl()->IsVulnerableToWind() ) {
			std::cout << "I'm worried about storms" << std::endl;
		} else if ( get_house_impl()->IsVulnerableToFire() ) {
			std::cout << "I'm worried about housework" << std::endl;
		} else {
			std::cout << "strong house" << std::endl;
		}
	}
	void WolfAttackByBreath( void ) override
	{
		if ( get_house_impl()->IsVulnerableToWind() ) {
			std::cout << "The wolf has blown the house away with his breath." << std::endl;
		} else {
			std::cout << "The wolf's breath did not destroy the house." << std::endl;
		}
	}
	void WolfAttackByFire( void ) override
	{
		if ( get_house_impl()->IsVulnerableToFire() ) {
			std::cout << "The wolf has set the house on fire." << std::endl;
		} else {
			std::cout << "The wolf could not set the house on fire." << std::endl;
		}
	}
	void WolfAttackFromChimney( void ) override
	{
		if ( get_house_impl()->IsThereChimney() ) {
			std::cout << "A wolf has invaded through the chimney! But the pig scalded the wolf by boiling it." << std::endl;
		} else {
			std::cout << "There was no chimney." << std::endl;
		}
	}
};

house_abst* make_house_by_elder_pig( void )
{
	return new three_little_pigs_house( make_house_by_straw() );
}

house_abst* make_house_by_2nd_pig( void )
{
	return new three_little_pigs_house( make_house_by_wood() );
}

house_abst* make_house_by_youngest_pig( void )
{
	return new three_little_pigs_house( make_house_by_brick() );
}
