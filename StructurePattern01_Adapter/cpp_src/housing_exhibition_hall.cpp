/**
 * @file housing_exhibition_hall.cpp
 * @author PFA03027@nifty.com
 * @brief Client of Adapter as Adapter pattern sample
 * @version 0.1
 * @date 2022-07-22
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * 各houseメーカークラスは、異なる受付I/Fを持っています。これを統一したI/Fに変換するため、Adapterパターンを適用したサンプルです。
 */

#include <cstdlib>
#include <vector>
#include <memory>

#include "reception_desk_adapter.h"

void customer_request_order(const std::vector<std::unique_ptr<reception_desk>>& rc)
{
    rc[0]->order_house();
    rc[1]->order_house();
    rc[2]->order_house();
}

int main(void)
{
    std::vector<std::unique_ptr<reception_desk>> reception_counter;

    reception_counter.push_back(std::unique_ptr<reception_desk>(new reception_desk_straw_housemaker(new straw_housemaker)));
    reception_counter.push_back(std::unique_ptr<reception_desk>(new reception_desk_wood_housemaker( new wood_housemaker)));
    reception_counter.push_back(std::unique_ptr<reception_desk>(new reception_desk_stone_housemaker(new stone_housemaker)));

    customer_request_order(reception_counter);

    return EXIT_SUCCESS;
}


