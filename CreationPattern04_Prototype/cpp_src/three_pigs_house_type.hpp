/**
 * @file three_pigs_makers.hpp
 * @author PFA03027@nifty.com
 * @brief Concrete class of builder
 * @version 0.1
 * @date 2023-01-22
 *
 * @copyright Copyright (c) 2023, PFA03027@nifty.com
 *
 */

#ifndef THREE_PIGS_HOUSE_TYPE_HPP_
#define THREE_PIGS_HOUSE_TYPE_HPP_

#include "house_design_prototype.hpp"

class elder_house_prototype : public house_prototype {
public:
	elder_house_prototype( void );

	house_prototype* clone( void ) override;

	void let_us_see_house( void ) override;

private:
	elder_house_prototype( const elder_house_prototype& orig );

	std::list<std::string> rooms_;
};

class second_house_prototype : public house_prototype {
public:
	second_house_prototype( void );

	house_prototype* clone( void ) override;

	void let_us_see_house( void ) override;

private:
	second_house_prototype( const second_house_prototype& orig );

	std::list<std::string> rooms_;
};

class youngest_house_prototype : public house_prototype {
public:
	youngest_house_prototype( void );

	house_prototype* clone( void ) override;

	void let_us_see_house( void ) override;

private:
	youngest_house_prototype( const youngest_house_prototype& orig );

	std::list<std::string> rooms_;
};

#endif   // THREE_PIGS_HOUSE_TYPE_HPP_
