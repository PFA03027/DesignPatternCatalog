/**
 * @file three_pings_text_object.cpp
 * @author PFA03027@nifty.com
 * @brief Implementation of proxy pattern
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 * 生成するオブジェクトの選択(make_text_object関数)は、恣意的行う実装としていますが、
 * 現実の実装では、条件や状況、設計によって決めていくことになると思います。
 *
 */

#include <fstream>
#include <iostream>
#include <string>

#include "three_pings_text_object.hpp"

// Realなクラス
class PigHouse_text_obj : public text_object {
public:
	PigHouse_text_obj( const char* p_description )
	  : my_description_( p_description )
	{
	}
	~PigHouse_text_obj() = default;

	const char* c_string_pointer( void ) override
	{
		return my_description_.c_str();
	}

private:
	std::string my_description_;
};

// 遅延初期化を行うProxyクラス
class SecondPigsHouse_text_obj : public text_object {
public:
	SecondPigsHouse_text_obj( const char* p_description_fname )
	  : p_realobj_( nullptr )
	  , my_description_fname( p_description_fname )
	{
	}
	~SecondPigsHouse_text_obj()
	{
		delete p_realobj_;
	}

	const char* c_string_pointer( void ) override
	{
		if ( p_realobj_ == nullptr ) {
			// 文字列の呼び出しがあってから、Realオブジェクトの生成を行う。
			std::ifstream input_file( my_description_fname );
			if ( !input_file.is_open() ) {
				return "ERR";
			}
			std::string read_str;
			getline( input_file, read_str );
			p_realobj_ = new PigHouse_text_obj( read_str.c_str() );
		}
		return p_realobj_->c_string_pointer();
	}

private:
	PigHouse_text_obj* p_realobj_;

	std::string my_description_fname;
};

// YoungestPigHous_text_objクラスで変換を行う対象となる、I/Fの異なるクラス
class Original_YoungestPigHous_obj {
public:
	Original_YoungestPigHous_obj( void )
	  : my_descript_( "Youngest Pig house is stone house" )
	{
	}

	std::string get_description( void )
	{
		return my_descript_;
	}

private:
	std::string my_descript_;
};
// I/Fの異なるクラスに対するI/F変換を行うAdapterとしての機能するProxy
class YoungestPigHous_text_obj : public text_object {
public:
	YoungestPigHous_text_obj( void )
	  : p_adaptee_( new Original_YoungestPigHous_obj )
	  , description_buff_()
	{
	}
	~YoungestPigHous_text_obj()
	{
		delete p_adaptee_;
	}

	const char* c_string_pointer( void ) override
	{
		description_buff_ = p_adaptee_->get_description();
		return description_buff_.c_str();
	}

private:
	Original_YoungestPigHous_obj* p_adaptee_;
	std::string                   description_buff_;
};

std::unique_ptr<text_object> text_object::make_text_object( obj_id req_id )
{
	std::unique_ptr<text_object> up_ans = nullptr;
	switch ( req_id ) {
		case obj_id::kId_ElderPigHouse: {
			up_ans = std::unique_ptr<PigHouse_text_obj>( new PigHouse_text_obj( "Elder pig house is straw huose." ) );
		} break;
		case obj_id::kId_2ndPigHouse: {
			up_ans = std::unique_ptr<SecondPigsHouse_text_obj>( new SecondPigsHouse_text_obj( "second_pigs_house_description.txt" ) );
		} break;
		case obj_id::kId_YoungestPigHouse: {
			up_ans = std::unique_ptr<YoungestPigHous_text_obj>( new YoungestPigHous_text_obj() );
		} break;
	}

	return up_ans;
}

text_object::~text_object()
{
}
