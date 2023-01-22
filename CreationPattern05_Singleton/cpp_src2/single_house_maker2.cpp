/**
 * @file single_house_maker2.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Singletonを実現する方法として、shared_ptrを用いたFactory関数で実現する手法で実装したサンプルです。
 * Singletonの利用者がすべていなくなるとSingletonクラスのデストラクタが実行され、リソースの開放が行われます。
 * 一方で、無用なSingletonのインスタンス生成/破棄を回避するために、何回も使用する場合はshared_ptrを保持しておく必要があります。
 * このサンプルでは、この点に対し利用者がSingletonのライフタイムを意識した実装もできるように、あえてrelease_instance()を用意しました。
 * 実行時のSingletonのインスタンスは、shared_ptrでグローバルに共有されていますので最後にrelease_instance()したスレッドが
 * 最終的な解放処理を行うことになります。
 * この性質により、Singletonインスタンスを異なるソフトウェアから非同期に扱う場合でも、ある程度安全にライフタイムの管理が可能になります。
 * （間接的な循環参照が発生した場合は、どうにもなりませんが。）
 *
 * また、shared_ptrから生ポインタを引っぺがすような無茶をしない限りは、Singletonのライフタイムはshared_ptrで管理されますので、たいてい安全です。
 *
 * 実装としては、Double Checked Lockの構造です。
 * が、shared_ptrはダングリングポインタにはならないので、get_instance()の呼び出し回数を減らせられます。
 * そのため、関数全体をmutexでロックする実装でも、パフォーマンスへの影響は少なくできるでしょう。
 *
 * 遅延初期化の方法を使用した場合、だれが最初の初期化を行うのか？ という点が実行時に決定されるため非決定的になります。
 * (このサンプルの場合は、だれが最後の解放処理を行うのかという点も非決定的になります)
 * これがデバッグ上問題になる場合があります。
 * 解決策のテクニックとしては、遅延初期化が実行されたときのコールスタックを、ログに残す、インスタンスに保存する等を行い、初期化の実行者を特定することができます。
 * この方法はget_instance()のI/Fを変更することなく実現できる点が魅力です。
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

class house_maker {
public:
	static std::shared_ptr<house_maker> get_instance( void );
	static void                         release_instance( std::shared_ptr<house_maker>&& sp_inst_arg );   // moveを強制するI/Fとすることでshared_ptrのリークを防ぐ

	void print_i_am( void )
	{
		std::lock_guard<std::mutex> lk( mtx_ );
		std::cout << "My house maker ID is 0x" << this << std::endl;
	}

	// shared_ptrがデストラクタを呼び出せるように、デストラクタはpublic関数とする。
	~house_maker()
	{
		// デストラクタがClose戦略を担う。
		std::cout << "e.g., close file discriptor" << std::endl;
	}

private:
	house_maker( void )
	{
	}
	house_maker( const house_maker& )            = delete;
	house_maker( house_maker&& )                 = delete;
	house_maker& operator=( const house_maker& ) = delete;
	house_maker& operator=( house_maker&& )      = delete;

	mutable std::mutex mtx_;   // house_makerクラスのインスタンスを保護するためのmutex

	static std::mutex                 mtx_singleton_;
	static std::weak_ptr<house_maker> wp_singleton_;
};

std::mutex                 house_maker::mtx_singleton_;
std::weak_ptr<house_maker> house_maker::wp_singleton_;

std::shared_ptr<house_maker> house_maker::get_instance( void )
{
	std::shared_ptr<house_maker> sp_ans = wp_singleton_.lock();
	if ( sp_ans == nullptr ) {
		std::lock_guard<std::mutex> lk( mtx_singleton_ );
		sp_ans = wp_singleton_.lock();
		if ( sp_ans == nullptr ) {
			sp_ans        = std::shared_ptr<house_maker>( new house_maker );   // コンストラクタはprivateであるため、std::make_shared<>()は使えない。
			wp_singleton_ = sp_ans;
		}
	}
	return sp_ans;
}

void house_maker::release_instance( std::shared_ptr<house_maker>&& sp_inst_arg )
{
	sp_inst_arg.reset();
	return;
}

/////////////////////////////////////////////////

int main( void )
{
	auto sp_singleton = house_maker::get_instance();
	sp_singleton->print_i_am();
	auto sp_singleton2 = house_maker::get_instance();
	sp_singleton2->print_i_am();
	house_maker::release_instance( std::move( sp_singleton ) );
	house_maker::release_instance( std::move( sp_singleton2 ) );

	std::cout << "end of process" << std::endl;
	return EXIT_SUCCESS;   // 関数を抜けると、singletonの利用者がなくなるので、解放処理が実行される。
}
