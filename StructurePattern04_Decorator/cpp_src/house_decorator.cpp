/**
 * @file house_decorator.cpp
 * @author PFA03027@nifty.com
 * @brief Decorator pattern example #1
 * @version 0.1
 * @date 2022-09-17
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * デザインパターン本に沿ったDecoratorパターンの実装サンプル
 * 
 * 一からクラス階層をスクラッチで組み上げる場合に、適用しやすい構造です。
 * 
 * 既存のクラスに追加するような状況では、I/Fが統一されていないことが想定される。
 * その場合、I/Fを統一するためにAdapterパターンと組み合わせる必要があるかもしれない。
 * 
 */

#include <stdlib.h>

#include <string>
#include <iostream>
#include <sstream>


/**
 * @brief ベースクラス
 * 
 */
class base_component {
public:
    virtual void view(std::ostream& oss) = 0;
};

/**
 * @brief 具象化クラス その１
 * 
 */
class straw_house : public base_component {
public:
    void view(std::ostream& oss) override {
        oss << "This is straw house";
    }
};

/**
 * @brief 具象化クラス その２
 * 
 */
class wood_house : public base_component {
public:
    void view(std::ostream& oss) override {
        oss << "This is wood house";
    }
};

/**
 * @brief 具象化クラス その３
 * 
 */
class stone_house : public base_component {
public:
    void view(std::ostream& oss) override {
        oss << "This is stone house";
    }
};

/**
 * @brief デコレーターのベースクラス
 * 
 * どんな家でも装飾しちゃうぞ♪というクラスのベースクラス
 */
class house_decorator : public base_component {
public:
    house_decorator(base_component* p_ref_component_arg)
      : p_ref_component(p_ref_component_arg) {}

    void view(std::ostream& oss) override {
        p_ref_component->view(oss);
    }

private:
    base_component* p_ref_component;
};

/**
 * @brief デコレーターの具象化クラス　その１
 * 
 */
class illumination_house_decorator : public house_decorator {
public:
    illumination_house_decorator(base_component* p_ref_component_arg)
      : house_decorator(p_ref_component_arg) {}

    void view(std::ostream& oss) override {
        house_decorator::view(oss);
        oss << " with " << color_str << " illumination";
    }

    void set_color(std::string c) {
        color_str = c;
    }
private:
    std::string color_str;
};

/**
 * @brief デコレーターの具象化クラス　その２
 * 
 */
class flower_house_decorator : public house_decorator {
public:
    flower_house_decorator(base_component* p_ref_component_arg)
      : house_decorator(p_ref_component_arg) {}

    void view(std::ostream& oss) override {
        house_decorator::view(oss);
        oss << " with " << color_str << " flower";
    }

    void set_color(std::string c) {
        color_str = c;
    }
private:
    std::string color_str;
};

/**
 * @brief デコレーターによらず、ともかくview()を実行
 * 
 * @param p_ref_component_arg 
 */
void do_view(base_component* p_ref_component_arg) {
    p_ref_component_arg->view(std::cout);
    std::cout << std::endl;
}

int main(void) {
    straw_house house1;
    wood_house  house2;
    stone_house house3;

    // houseにデコレーターを適用する。
    flower_house_decorator  deco_house1(&house1);

    illumination_house_decorator  deco_house2(&house2);
    deco_house2.set_color("blue");

    illumination_house_decorator  deco_house31(&house3);
    deco_house31.set_color("red");

    // デコレーターが適用されたデコレーターに、デコレーターを再度適用する。
    flower_house_decorator  deco_house32(&deco_house31);
    deco_house32.set_color("green");

    // デコレーターの効果を確認する
    do_view(&deco_house1);
    do_view(&deco_house2);
    do_view(&deco_house32);

    return EXIT_SUCCESS;
}
