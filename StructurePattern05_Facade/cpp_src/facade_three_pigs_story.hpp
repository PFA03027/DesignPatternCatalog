/**
 * @file facade_three_pigs_story.hpp
 * @author PFA03027@nifty.com
 * @brief Header file of Facade pattern
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Facadeパターンのサンプルのヘッダファイルです。
 *
 * Bridgeパターンでは、子豚3兄弟のそれぞれの家とそれにまつわるストーリーを別々のクラスとして実装しました。
 * その結果、3つのクラスとそれぞれで呼び出すI/Fがそれぞれに定義されることとなりました。
 * Facadeパターンでは、Facadeクラスがそれらのクラス群に対するI/Fとして定義され、このような複数のクラスで
 * 構成されるような実装の詳細をFacadeクラスの後ろに隠すことで、ソフトウェアレイヤー間の結合度を下げるよう
 * なデザインパターンです。
 *
 * このサンプルでは、Bridgeパターンのメイン関数で行っていたオブジェクトの管理などをFacadeクラスの後ろに隠し、
 * クラス構成等の実装の詳細をクライアント側から切り離しています。
 *
 * [補足]
 * Facadeパターンはそのパターンの目的から、Singletonパターンを併用する場合も多いですが、このサンプルでは、
 * Singletonパターンは適用していません。
 * 代わりに、pimplイディオムで実装の詳細を隠しています。
 */

#ifndef FACADE_THREE_PIGS_STORY_HPP_
#define FACADE_THREE_PIGS_STORY_HPP_

#include <string>

class facade_three_pigs_story {
public:
	facade_three_pigs_story( void );
	~facade_three_pigs_story();

	void MotherPig_Visit_ElderPigHouse( void );
	void MotherPig_Visit_2ndPigHouse( void );
	void MotherPig_Visit_YoungestPigHouse( void );
	void Wolf_Attack_ElderPigHouse( void );
	void Wolf_Attack_2ndPigHouse( void );
	void Wolf_Attack_YoungestPigHouse( void );

private:
	class facade_three_pigs_story_impl;

	facade_three_pigs_story_impl* p_impl_;
};

#endif
