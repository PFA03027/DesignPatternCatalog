/**
 * @file main.cpp
 * @author PFA03027@nifty.com
 * @brief abstraction class header of Bridge pattern
 * @version 0.1
 * @date 2023-02-19
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Facadeパターンの実装サンプル
 *
 * このソースファイルは、Facadeパターンのクライアント側の実装。
 * クライアント側は、facadeクラスの後ろ側に存在する実装の詳細を知りません。
 *
 */

#include <iostream>

#include "facade_three_pigs_story.hpp"

int main( void )
{
	facade_three_pigs_story facade_tps;

	facade_tps.MotherPig_Visit_ElderPigHouse();
	facade_tps.MotherPig_Visit_2ndPigHouse();
	facade_tps.MotherPig_Visit_YoungestPigHouse();
	facade_tps.Wolf_Attack_ElderPigHouse();
	facade_tps.Wolf_Attack_2ndPigHouse();
	facade_tps.Wolf_Attack_YoungestPigHouse();

	return EXIT_SUCCESS;
}