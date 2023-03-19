/**
 * @file three_pings_text_object.hpp
 * @author PFA03027@nifty.com
 * @brief Header file of proxy pattern
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#ifndef THREE_PIGS_TEXT_OBJECT_HPP_
#define THREE_PIGS_TEXT_OBJECT_HPP_

#include <memory>

enum class obj_id {
	kId_ElderPigHouse,
	kId_2ndPigHouse,
	kId_YoungestPigHouse
};

class text_object {
public:
	virtual const char* c_string_pointer( void ) = 0;

	virtual ~text_object();

	static std::unique_ptr<text_object> make_text_object( obj_id req_id );
};

#endif   // THREE_PIGS_TEXT_OBJECT_HPP_
