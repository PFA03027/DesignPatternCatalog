/**
 * @file main.cpp
 * @author PFA03027@nifty.com
 * @brief abstraction class header of Bridge pattern
 * @version 0.1
 * @date 2023-02-19
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Bridgeパターンの実装サンプル
 *
 * このソースファイルは、Bridgeパターンのクライアント側の実装
 *
 */

#include <iostream>

#include "house_abst.hpp"

int main( void )
{
	house_abst* p_elder_pigs_house    = make_house_by_elder_pig();
	house_abst* p_2nd_pigs_house      = make_house_by_2nd_pig();
	house_abst* p_youngest_pigs_house = make_house_by_youngest_pig();

	std::cout << "Mother Pig's comment of elder pigs house: ";
	p_elder_pigs_house->WhatCommentMotherPigSaid();

	std::cout << "Mother Pig's comment of 2nd pigs house: ";
	p_2nd_pigs_house->WhatCommentMotherPigSaid();

	std::cout << "Mother Pig's comment of youngest pigs house: ";
	p_youngest_pigs_house->WhatCommentMotherPigSaid();

	std::cout << "Wolf attacks elder pigs house: ";
	p_elder_pigs_house->WolfAttackByBreath();

	std::cout << "Wolf attacks 2nd pigs house: ";
	p_2nd_pigs_house->WolfAttackByFire();

	std::cout << "Wolf attacks youngest pigs house: ";
	p_youngest_pigs_house->WolfAttackFromChimney();

	return EXIT_SUCCESS;
}