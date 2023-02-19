/**
 * @file house_abst.hpp
 * @author PFA03027@nifty.com
 * @brief Implementor class header of Bridge pattern
 * @version 0.1
 * @date 2023-02-19
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Bridgeパターンの実装サンプル
 *
 * このヘッダファイルは、BridgeパターンのImplementorクラスを定義したヘッダファイル。
 * RedefinedAbstractionクラスの実装に対して提供されるヘッダファイル。
 * クライアントには、このヘッダファイルは公開されない。
 */

#ifndef HOUSE_IMPL_HPP_
#define HOUSE_IMPL_HPP_

// Implementorクラスの定義
class house_impl {
public:
	house_impl( void );
	virtual ~house_impl();

	virtual bool IsVulnerableToWind( void ) = 0;
	virtual bool IsVulnerableToFire( void ) = 0;
	virtual bool IsThereChimney( void )     = 0;
};

// ConcreteImplementorクラスを生成するファクトリ関数。
// このファクトリ関数は、藁製の家のインスタンスを生成する
house_impl* make_house_by_straw( void );

// RedeinedAbstructionクラスを生成するファクトリ関数。
// このファクトリ関数は、木製の家のインスタンスを生成する
house_impl* make_house_by_wood( void );

// RedeinedAbstructionクラスを生成するファクトリ関数。
// このファクトリ関数は、レンガ製の家のインスタンスを生成する
house_impl* make_house_by_brick( void );

#endif   // HOUSE_IMPL_HPP_