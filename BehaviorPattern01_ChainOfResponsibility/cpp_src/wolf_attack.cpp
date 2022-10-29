/**
 * @file wolf_attack.cpp
 * @author PFA03027@nifty.com
 * @brief chain of responsibilityの利用サンプル
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "chain_of_responsibility.h"


class straw_house_of_elder_pig : public request_handler {
public:
    straw_house_of_elder_pig(void) : request_handler() {}

    void handle( std::string req_str) override {
        std::cout << req_str << ": blow off straw house!" << std::endl;

        request_handler::handle(req_str);
    }
};

class wood_house_of_2nd_pig : public request_handler {
public:
    wood_house_of_2nd_pig(void) : request_handler() {}

    void handle( std::string req_str) override {
        std::cout << req_str << ": fire wood house!" << std::endl;

        request_handler::handle(req_str);
    }
};

class stone_house_of_youngest_pig : public request_handler {
public:
    stone_house_of_youngest_pig(void) : request_handler() {}

    void handle( std::string req_str) override {
        std::cout << req_str << ": Not break stone house! So, fail " << req_str << std::endl;
    }
};


int main(void) {
    straw_house_of_elder_pig    house_of_elder;
    wood_house_of_2nd_pig       house_of_2nd;
    stone_house_of_youngest_pig house_of_youngest;

    // request handlerクラスをつなげる。
    house_of_elder.set_successor(&house_of_2nd);
    house_of_2nd.set_successor(&house_of_youngest);

    // Chainの先頭にRequestを発行する。
    house_of_elder.handle("Wolf Attack! ");

    return EXIT_SUCCESS;
}
