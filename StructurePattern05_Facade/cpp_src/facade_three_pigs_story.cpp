/**
 * @file facade_three_pigs_story.cpp
 * @author PFA03027@nifty.com
 * @brief Header file of Facade pattern
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Facadeパターンのサンプルの実装例です。
 *
 */

#include <iostream>

#include "facade_three_pigs_story.hpp"

#include "house_abst.hpp"

class facade_three_pigs_story::facade_three_pigs_story_impl {
public:
	facade_three_pigs_story_impl( void )
	{
		p_elder_pigs_house_    = make_house_by_elder_pig();
		p_2nd_pigs_house_      = make_house_by_2nd_pig();
		p_youngest_pigs_house_ = make_house_by_youngest_pig();
	}

	~facade_three_pigs_story_impl()
	{
		delete p_elder_pigs_house_;
		delete p_2nd_pigs_house_;
		delete p_youngest_pigs_house_;
	}

	house_abst* p_elder_pigs_house_;
	house_abst* p_2nd_pigs_house_;
	house_abst* p_youngest_pigs_house_;

	void MotherPig_Visit_ElderPigHouse( void )
	{
		std::cout << "Mother Pig's comment of elder pigs house: ";
		p_elder_pigs_house_->WhatCommentMotherPigSaid();
	}
	void MotherPig_Visit_2ndPigHouse( void )
	{
		std::cout << "Mother Pig's comment of 2nd pigs house: ";
		p_2nd_pigs_house_->WhatCommentMotherPigSaid();
	}
	void MotherPig_Visit_YoungestPigHouse( void )
	{
		std::cout << "Mother Pig's comment of youngest pigs house: ";
		p_youngest_pigs_house_->WhatCommentMotherPigSaid();
	}
	void Wolf_Attack_ElderPigHouse( void )
	{
		std::cout << "Wolf attacks elder pigs house: ";
		p_elder_pigs_house_->WolfAttackByBreath();
	}
	void Wolf_Attack_2ndPigHouse( void )
	{
		std::cout << "Wolf attacks 2nd pigs house: ";
		p_2nd_pigs_house_->WolfAttackByFire();
	}
	void Wolf_Attack_YoungestPigHouse( void )
	{
		std::cout << "Wolf attacks youngest pigs house: ";
		p_youngest_pigs_house_->WolfAttackFromChimney();
	}
};

facade_three_pigs_story::facade_three_pigs_story( void )
  : p_impl_( new facade_three_pigs_story_impl )
{
}
facade_three_pigs_story::~facade_three_pigs_story()
{
	delete p_impl_;
}

void facade_three_pigs_story::MotherPig_Visit_ElderPigHouse( void )
{
	p_impl_->MotherPig_Visit_ElderPigHouse();
}
void facade_three_pigs_story::MotherPig_Visit_2ndPigHouse( void )
{
	p_impl_->MotherPig_Visit_2ndPigHouse();
}
void facade_three_pigs_story::MotherPig_Visit_YoungestPigHouse( void )
{
	p_impl_->MotherPig_Visit_YoungestPigHouse();
}
void facade_three_pigs_story::Wolf_Attack_ElderPigHouse( void )
{
	p_impl_->Wolf_Attack_ElderPigHouse();
}
void facade_three_pigs_story::Wolf_Attack_2ndPigHouse( void )
{
	p_impl_->Wolf_Attack_2ndPigHouse();
}
void facade_three_pigs_story::Wolf_Attack_YoungestPigHouse( void )
{
	p_impl_->Wolf_Attack_YoungestPigHouse();
}
