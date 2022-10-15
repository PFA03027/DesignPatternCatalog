/**
 * @file house_maker_template.h
 * @author PFA03027@nifty.com
 * @brief Template Method pattern example
 * @version 0.1
 * @date 2022-10-15
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */


#ifndef HOUSE_MAKER_TEMPLATE_H_
#define HOUSE_MAKER_TEMPLATE_H_

#include <iostream>
#include <sstream>

/**
 * @brief Template Methodのpatternのベースクラス
 * 
 */
class house_maker_base {
public:
    void make_house(std::ostream& oss) {
        oss << get_maker_name() << get_verb() << get_material() << " house" << hook_tail();
    }

    virtual ~house_maker_base() {}

protected:
    virtual std::string get_maker_name(void) = 0;
    virtual std::string get_material(void) = 0;

    virtual std::string get_verb(void) {
        return " makes ";
    }
    virtual std::string hook_tail(void) {
        return "";
    }
};


#endif
