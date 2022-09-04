/**
 * @file house_abst.cpp
 * @author PFA03027@nifty.com
 * @brief composite pattern example #2
 * @version 0.1
 * @date 2022-09-04
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * Compositeパターンによって構成された構造に対し、個々のComponent個別I/Fへのアクセスを分離する目的でVisitorパターンを適用したサンプル。
 * Visitorパターンの特性として、Componentの派生クラス名を知っている必要がある。この特性の為、クラス階層が安定している場合に適用可能となる。
 * 
 * Visitorパターンを適用する上での木構造のスキャンは、Componentクラスが実装した。
 * 必要に応じて、Iteratorパターンの適用(スキャンアルゴリズムが複数必要な場合等)や、Visitorがスキャンするように実装しても良い。
 * 
 * サンプルコードとして、ベースとなるhouse_componentに名前を取得するI/Fが存在せず、各クラスで個別に取得する手段が提供された場合をサンプルとしている。
 * (もちろん名前は共通的要素なので、本来的には共通I/F化した方が良い。)
 */


#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

/**
 * 下記のように、visitorクラスのI/F定義の為、適用対象のクラス名が事前に把握できている必要がある。
 * 
 */

class house;
class roof;
class room;
class door;
class window;

/**
 * @brief Visitorクラスのベースクラス
 * 
 */
class house_visitor_base {
public:
    virtual void VisiteComponent(house *p_c) = 0;
    virtual void VisiteComponent(roof *p_c) = 0;
    virtual void VisiteComponent(room *p_c) = 0;
    virtual void VisiteComponent(door *p_c) = 0;
    virtual void VisiteComponent(window *p_c) = 0;
};

/**
 * @brief 家を構成する構造物を表すベースクラス
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

    // I/F to accept Visitor
    virtual void AcceptVisitor(house_visitor_base* p_visitor) = 0;

    // Scanner I/F for Visitor
    void ScanByVisitor(house_visitor_base* p_visitor) {
        AcceptVisitor(p_visitor);
        for( auto&& e : children) {
            e->ScanByVisitor(p_visitor);
        }
    }

private:
    child_container children;
};

/**
 * @brief 天井を表す構造物
 * 
 */
class house : public house_component {
public:
    house(void) : my_name("house") {}
    ~house() = default;

    // I/F implementation for visitor class
    void AcceptVisitor(house_visitor_base* p_visitor) override {
        p_visitor->VisiteComponent(this);
    }

    const std::string my_name;
};

/**
 * @brief 天井を表す構造物
 * 
 */
class roof : public house_component {
public:
    roof(void) = default;
    ~roof() = default;

    // I/F implementation for visitor class
    void AcceptVisitor(house_visitor_base* p_visitor) override {
        p_visitor->VisiteComponent(this);
    }

    const char* get_name(void) { return "Roof"; }
};

/**
 * @brief 部屋を表す構造物
 * 
 */
class room : public house_component {
public:
    room(void) = default;
    ~room() = default;

    // I/F implementation for visitor class
    void AcceptVisitor(house_visitor_base* p_visitor) override {
        p_visitor->VisiteComponent(this);
    }

    std::string GetRoomName(void) { return "Living room"; }
};

/**
 * @brief ドアを表す構造物
 * 
 */
class door : public house_component {
public:
    door(void) = default;
    ~door() = default;

    // I/F implementation for visitor class
    void AcceptVisitor(house_visitor_base* p_visitor) override {
        p_visitor->VisiteComponent(this);
    }

    const char* Name(void) { return "Door"; }
};

/**
 * @brief 窓を表す構造物
 * 
 */
class window : public house_component {
public:
    window(void) = default;
    ~window() = default;

    // I/F implementation for visitor class
    void AcceptVisitor(house_visitor_base* p_visitor) override {
        p_visitor->VisiteComponent(this);
    }

    const char* GetComponentName(void) { return "Window"; }
};


/**
 * @brief 構成物の名前を、それぞれのクラスで定義された方法で取得するVisitorの具象化クラス
 * 
 */
class Visitor_GetNameList : public house_visitor_base {
public:
    void VisiteComponent(house *p_c) override {
        oss << p_c->my_name << std::endl;
    }
    void VisiteComponent(roof *p_c) override {
        oss << p_c->get_name() << std::endl;
    }
    void VisiteComponent(room *p_c) override {
        oss << p_c->GetRoomName() << std::endl;
    }
    void VisiteComponent(door *p_c) override {
        oss << p_c->Name() << std::endl;
    }
    void VisiteComponent(window *p_c) override {
        oss << p_c->GetComponentName() << std::endl;
    }

    std::string str(void) { return oss.str(); }

private:
    std::ostringstream    oss;
};


int main(void) {
    house my_house;
    my_house.add_component(std::make_shared<roof>());   // 家に天井を追加
    std::shared_ptr<room>   sp_my_room = std::make_shared<room>();
    my_house.add_component(sp_my_room); // 家に部屋を追加
    sp_my_room->add_component(std::make_shared<door>());    // 部屋にドアを追加
    sp_my_room->add_component(std::make_shared<window>());  // 部屋に窓を追加

    Visitor_GetNameList v;
    my_house.ScanByVisitor(&v);
    std::cout << v.str() << std::endl;
    /* 下記がoutput結果。
house
Roof
Living room
Door
Window

     */
}
