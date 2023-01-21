/**
 * @file single_house_maker.cpp
 * @author PFA03027@nifty.com
 * @brief singleton pattern sample implementation
 * @version 0.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * Double Checked Lockの手法でSingletonを実装したサンプルコードです。
 * C++11以前にも使われていた手法ですが、メモリモデルをきちんと考慮しないと正しく動作しません。
 *
 * このサンプルでは、メモリモデルの対処にatomic変数を使用しました。
 * atomic型の導入前は、Double Checked Lockの手法は多分使えません。あきらめて全体をロックするしかないと思います。
 *
 * この実装のメリットは、get_instance()以外の静的メンバ関数もSingletonのインスタンス変数にアクセスできる点です。
 * ただし、よくよく注意して静的メンバ関数の実装をする必要があります。
 * 特に、Singletonのインスタンス変数を破棄するようなI/Fを用意する場合は、たとえインスタンスを保持する変数をmutexで囲ったとしても、
 * ダングリングポインタの発生は不可避です。
 * そのため、house_maker2はダメな実装例となります。
 *
 * また、C++11以前の場合、atomic変数がありません。なので、使いどころはほとんどなかったりします。
 */

#include <atomic>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <sstream>

//////////////// house_maker /////////////////
class house_maker {
public:
	static house_maker& get_instance( void );

	void print_i_am( void )
	{
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

	static std::mutex                mtx_singleton_;
	static std::atomic<house_maker*> ap_singleton_;
};

std::mutex                house_maker::mtx_singleton_;
std::atomic<house_maker*> house_maker::ap_singleton_( nullptr );

house_maker& house_maker::get_instance( void )
{
	// ap_singleton_が一度有効になったら、無効にはならないという前提で使用可能なDouble checked Lockの手法のでの実装
	house_maker* p_ans = ap_singleton_.load( std::memory_order_acquire );
	if ( p_ans == nullptr ) {
		std::lock_guard<std::mutex> lk( mtx_singleton_ );
		p_ans = ap_singleton_.load( std::memory_order_relaxed );
		// https://yamasa.hatenablog.jp/entry/20100128/1264693781
		// 真ん中のloadには「メモリバリアなし」を意味する memory_order_relaxed が指定されています。
		// その理由は、std::mutex による排他制御が暗黙的なメモリバリアとして働いているために、
		// このload自体にはメモリバリアが不要となるからです。
		if ( p_ans == nullptr ) {
			p_ans = new house_maker();
			ap_singleton_.store( p_ans, std::memory_order_release );
		}
	}

	return *p_ans;
}

//////////////// house_maker2 /////////////////
class house_maker2 {
public:
	static house_maker2& get_instance( void );
	static void          release_instance( void );

	void print_i_am( void )
	{
		std::cout << "My house maker ID is 0x" << this << std::endl;
	}

private:
	house_maker2( void )
	{
	}
	~house_maker2()
	{
	}
	house_maker2( const house_maker2& )            = delete;
	house_maker2( house_maker2&& )                 = delete;
	house_maker2& operator=( const house_maker2& ) = delete;
	house_maker2& operator=( house_maker2&& )      = delete;

	static std::mutex    mtx_singleton_;
	static house_maker2* p_singleton_;
};

std::mutex    house_maker2::mtx_singleton_;
house_maker2* house_maker2::p_singleton_ = nullptr;

house_maker2& house_maker2::get_instance( void )
{
	// p_singleton_のアクセスをmutexのロックで囲う。実装
	// p_singleton_の破棄は可能だが、アクセス毎にlockが行われるため重い。
	// 加えて、関数から戻った後の参照がダングリングポインタになっている可能性もあるため、危険。
	std::lock_guard<std::mutex> lk( mtx_singleton_ );
	if ( p_singleton_ == nullptr ) {
		p_singleton_ = new house_maker2();
	}

	return *p_singleton_;
}

void house_maker2::release_instance( void )
{
	std::lock_guard<std::mutex> lk( mtx_singleton_ );
	delete p_singleton_;
	p_singleton_ = nullptr;
}

/////////////////////////////////////////////
int main( void )
{
	house_maker::get_instance().print_i_am();
	return EXIT_SUCCESS;
}
