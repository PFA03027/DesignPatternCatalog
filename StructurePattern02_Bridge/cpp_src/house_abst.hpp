/**
 * @file house_abst.hpp
 * @author PFA03027@nifty.com
 * @brief abstraction class header of Bridge pattern
 * @version 0.1
 * @date 2023-02-19
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Bridgeパターンの実装サンプル
 *
 * このヘッダファイルは、BridgeパターンのAbstractクラスを定義したヘッダファイル。
 * クライアント側に公開されるのは、このAbstractクラスを定義したヘッダファイルのみ。
 * クライアントはこのヘッダファイルだけを読み込み、利用する。
 */

#ifndef HOUSE_ABST_HPP_
#define HOUSE_ABST_HPP_

// Implementorクラスの前方宣言
class house_impl;

// Abstructionクラスの定義
class house_abst {
public:
	house_abst( house_impl* p_hi_arg );
	virtual ~house_abst();

	virtual void WhatCommentMotherPigSaid( void ) = 0;
	virtual void WolfAttackByBreath( void )       = 0;
	virtual void WolfAttackByFire( void )         = 0;
	virtual void WolfAttackFromChimney( void )    = 0;

protected:
	house_impl* get_house_impl( void );

private:
	house_impl* p_hi_;
};

// RedeinedAbstructionクラスを生成するファクトリ関数。
// このファクトリ関数は、3匹の子豚の長男が作った藁の家のクラスのインスタンスを生成するファクトリ関数
house_abst* make_house_by_elder_pig( void );

// RedeinedAbstructionクラスを生成するファクトリ関数。
// このファクトリ関数は、3匹の子豚の次男が作った木の家のクラスのインスタンスを生成するファクトリ関数
house_abst* make_house_by_2nd_pig( void );

// RedeinedAbstructionクラスを生成するファクトリ関数。
// このファクトリ関数は、3匹の子豚の末の子豚が作ったレンガの家のクラスのインスタンスを生成するファクトリ関数
house_abst* make_house_by_youngest_pig( void );

#endif   // HOUSE_ABST_HPP_