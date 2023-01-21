/**
 * @file single_house_maker.cpp
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
 *
 * また、shared_ptrから生ポインタを引っぺがすような無茶をしない限りは、Singletonのライフタイムはshared_ptrで管理されますので、たいてい安全です。
 *
 * 実装としては、Double Checked Lockの構造です。
 * が、shared_ptrはダングリングポインタにはならないので、get_instance()の呼び出し回数を減らせられます。
 * そのため、関数全体をmutexでロックする実装でも、パフォーマンスへの影響は少なくできるでしょう。
 */

#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

class house_maker {
public:
	static std::shared_ptr<house_maker> get_instance( void );

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

/////////////////////////////////////////////////

int main( void )
{
	auto sp_singleton = house_maker::get_instance();
	sp_singleton->print_i_am();
	return EXIT_SUCCESS;   // 関数を抜けると、singletonの利用者がなくなるので、解放処理が実行される。
}
