/**
 * @file single_house_maker.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Singletonを実現する方法として、get_instance()内の静的変数で実現する方法での実装です。
 * C++11以降であれば、ブロックスコープを持つstatic変数初期化のスレッドセーフ化(gcc 4.8から有効)がC++11で導入されますので、
 * マルチスレッド環境であっても、get_instance()は安全です。
 * これだけではhouse_makerクラス自身がスレッドセーフになるわけではありませんので、house_makerのインスタンス自身もmutexで排他制御する必要があります。
 *
 * また、この方法の実装は、Singletonのインスタンスの破棄がプロセスの終了時に行われるという特徴があります。
 * 一方で、プロセスの終了が保証されない、あるいは終了しないようなシステム(*1)では、
 * Close戦略をどう実装するか、また、いつ実施するか？　というのが課題になります。
 *
 * 単純にClose戦略を実行するI/Fをメンバ関数に導入してしまうと、誰でもClose戦略を実行できてしまいます。
 * そのため、すべての利用者は、利用前に、Open戦略実施済みかどうかのチェックが必要になり、かなり面倒です。
 * これに対しては、Close戦略を実行するI/Fはprotected or privateにアクセス制限を行ったうえで、
 * 実行タイミングを設計で保証するというアプローチが必要になります。
 *
 * このサンプルは、上記の戦略で実装したサンプルです。
 *
 * 別の実装戦略として、cpp_src2ではshared_ptrを使用したサンプルを用意しました。
 *
 * (*1) プロセス内で起動停止のサイクルが必要となるシステムの場合で、停止処理ですべてのリソースを解放しなければならない要件が定義される場合、
 * プロセス停止によるデストラクタ処理が期待できないため、リソース解放を意識した実装が必須です。
 * また、デストラクタ処理が、ほかのソフトウェアコンポーネントに依存している場合、依存先のソフトウェアコンポーネントが
 * すでに破棄されていて、プロセス終了時のデストラクタ処理では正常なリソース解放が保証できない場合も考えられます。
 * (main関数終了後にクラッシュするという、かなり面倒なバグになります)
 *
 * ご参考
 * https://yamasa.hatenablog.jp/entry/20100128/1264693781
 */

#include <cstdlib>
#include <iostream>
#include <mutex>
#include <sstream>

class house_maker {
public:
	static house_maker& get_instance( void );

	void print_i_am( void )
	{
		std::lock_guard<std::mutex> lk( mtx_ );
		std::cout << "My house maker ID is 0x" << this << std::endl;
	}

private:
	house_maker( void )
	{
	}
	~house_maker()
	{
	}
	house_maker( const house_maker& )            = delete;
	house_maker( house_maker&& )                 = delete;
	house_maker& operator=( const house_maker& ) = delete;
	house_maker& operator=( house_maker&& )      = delete;

	// Close戦略を担うメンバ関数。
	void release_resource( void )
	{
		std::cout << "e.g., close file discriptor" << std::endl;
		return;
	}

	mutable std::mutex mtx_;   // house_makerクラスのインスタンスを保護するためのmutex

	// Close戦略を担うメンバ関数の呼び出しを許可するフレンド関数の登録
	// フレンド関数は実装されていなくてもリンクエラーにはならない。
	friend void release_house_maker_resource( void );
};

house_maker& house_maker::get_instance( void )
{
	static house_maker singleton;
	return singleton;
}

/////////////////////////////////////////////////
void release_house_maker_resource( void )
{
	house_maker::get_instance().release_resource();
}

int main( void )
{
	house_maker::get_instance().print_i_am();
	house_maker::get_instance().print_i_am();
	release_house_maker_resource();
	return EXIT_SUCCESS;
}
