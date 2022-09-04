/**
 * @file house_abst.cpp
 * @author PFA03027@nifty.com
 * @brief composite pattern example #1
 * @version 0.1
 * @date 2022-09-04
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * Compositeパターンの基本的な実装。
 * Componentクラスの派生クラスでの個別となるI/Fが少なく、共通I/F化できる場合は、これで足りる。
 * が、大概は足りない。そのため、I/Fの実装は、個別化と共通化のトレードオフになる。
 * 
 * ベースクラスとなるComponentが、派生クラスの為に用意すべきI/Fがわからない場合(例えばフレームワークの実装で発生する状況)、
 * Vistorパターンを適用することでI/Fの分離するという方法もある。（cpp_src2のサンプルを参照）
 * 
 * ただし、木構造の構造が意味を持つ場合には、dynamic_castを使って型を認識した上での実装等、もう一歩踏み込んだ実装が必要となる。
 * この様な点も、I/Fの共通化と型安全性とのトレードオフとなる。
 */


#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

/**
 * @brief 家を構成する構造物を表すベースクラス
 * 
 * このクラスを使って、家を構成する構造を構造物の木構造で表現できるようにするクラス
 * 
 * what_have()は、全てのクラスで共通に定義することになるI/F
 */
class house_component {
public:
    using child_container = std::list<std::shared_ptr<house_component>>;

    house_component(void) {}
    virtual ~house_component() {}

    // operation for composite tree
    void add_component(std::shared_ptr<house_component> sp_component) {
        children.emplace_back(sp_component);
    }
    void remove_component(std::shared_ptr<house_component> sp_component) {
        children.remove_if(
            [&sp_component](std::shared_ptr<house_component>& sp_c) -> bool {
                 return sp_component == sp_c;
            }
        );
    }
    const child_container& get_children(void) { return children; }

    // operations example
    virtual void what_have(std::ostream& oss, int depth = 0) = 0;

private:
    child_container children;
};

/**
 * @brief 天井を表す構造物
 * 
 */
class house : public house_component {
public:
    house(void) = default;
    ~house() = default;

    void what_have(std::ostream& oss, int depth = 0) override {
        for(int i=0;i<depth;i++) { oss << "  "; }

        oss << "House" << std::endl;

        for( auto&& sp_child : get_children() ) {
            sp_child->what_have(oss, depth+1);
        }
    }
};

/**
 * @brief 天井を表す構造物
 * 
 */
class roof : public house_component {
public:
    roof(void) = default;
    ~roof() = default;

    void what_have(std::ostream& oss, int depth = 0) override {
        for(int i=0;i<depth;i++) { oss << "  "; }

        oss << "Roof" << std::endl;

        for( auto&& sp_child : get_children() ) {
            sp_child->what_have(oss, depth+1);
        }
    }
};

/**
 * @brief 部屋を表す構造物
 * 
 */
class room : public house_component {
public:
    room(void) = default;
    ~room() = default;

    void what_have(std::ostream& oss, int depth = 0) override {
        for(int i=0;i<depth;i++) { oss << "  "; }

        oss << "Room" << std::endl;

        for( auto&& sp_child : get_children() ) {
            sp_child->what_have(oss, depth+1);
        }
    }
};

/**
 * @brief ドアを表す構造物
 * 
 */
class door : public house_component {
public:
    door(void) = default;
    ~door() = default;

    void what_have(std::ostream& oss, int depth = 0) override {
        for(int i=0;i<depth;i++) { oss << "  "; }

        oss << "Door" << std::endl;

        for( auto&& sp_child : get_children() ) {
            sp_child->what_have(oss, depth+1);
        }
    }
};

/**
 * @brief 窓を表す構造物
 * 
 */
class window : public house_component {
public:
    window(void) = default;
    ~window() = default;

    void what_have(std::ostream& oss, int depth = 0) override {
        for(int i=0;i<depth;i++) { oss << "  "; }

        oss << "Window" << std::endl;

        for( auto&& sp_child : get_children() ) {
            sp_child->what_have(oss, depth+1);
        }
    }
};




int main(void) {
    house my_house;
    my_house.add_component(std::make_shared<roof>());   // 家に天井を追加
    std::shared_ptr<room>   sp_my_room = std::make_shared<room>();
    my_house.add_component(sp_my_room); // 家に部屋を追加
    sp_my_room->add_component(std::make_shared<door>());    // 部屋にドアを追加
    sp_my_room->add_component(std::make_shared<window>());  // 部屋に窓を追加

    std::ostringstream    oss;
    my_house.what_have(oss);
    std::cout << oss.str() << std::endl;
    /* 下記がoutput結果。木構造に沿った出力となる
House 
  Roof
  Room
    Door
    Window
     */
}
