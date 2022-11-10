/**
 * @file main.cpp
 * @author PFA03027@nifty.com
 * @brief state pattern client implementation
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "three_pigs_story.h"

int main(void) {
    three_pigs_story    ty;

    ty.request_next();
    ty.request_next();
    ty.request_next();
    ty.request_next();
    ty.request_next();

    return EXIT_SUCCESS;
}