/**
 * @file house_abst.cpp
 * @author PFA03027@nifty.com
 * @brief composite pattern example #2
 * @version 0.1
 * @date 2022-09-04
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * Compositeパターンによって構成された構造に対し、個々のComponent個別I/Fへのアクセスを分離する目的でVisitorパターンを適用。
 * 
 * VisitorのI/Fは、ダブルディスパッチによる静的なcastではなくdynamic_castを使用して呼び出すべきI/Fを特定する実装としたサンプル。
 * これは、Visitorクラスのベースすクラスが、Componentクラスの派生クラスを知らなくてよい実装となる。
 * 代わりに、Visitorの実装を行う派生クラス側でdynamic_castによる動的なディスパッチを行う。
 * 
 * 結果として、Componentクラスの具象化クラスがシンプルとなっていることがわかる。
 * 
 * サンプルコードとして、ベースとなるhouse_componentに名前を取得するI/Fが存在せず、各クラスで個別に取得する手段が提供された場合をサンプルとしている。
 * (もちろん名前は共通的要素なので、本来的には共通I/F化した方が良い。)
 */


#include <memory>
#include <list>
#include <string>
#include <iostream>
#include <sstream>

class house_component;

/**
 * @brief Visitorクラスのベースクラス
 * 
 */
class house_visitor_base {
public:
    virtual void VisiteComponent(house_component *p_c) = 0;
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

    // Scanner I/F for Visitor
    void ScanByVisitor(house_visitor_base* p_visitor) {
        p_visitor->VisiteComponent(this);
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

    const char* GetComponentName(void) { return "Window"; }
};


/**
 * @brief 構成物の名前を、それぞれのクラスで定義された方法で取得するVisitorの具象化クラス
 * 
 * dynamic_castを用いて具象化クラスを特定する方式による実装
 */
class Visitor_GetNameList : public house_visitor_base {
public:
    void VisiteComponent(house *p_c) {
        oss << p_c->my_name << std::endl;
    }
    void VisiteComponent(roof *p_c) {
        oss << p_c->get_name() << std::endl;
    }
    void VisiteComponent(room *p_c) {
        oss << p_c->GetRoomName() << std::endl;
    }
    void VisiteComponent(door *p_c) {
        oss << p_c->Name() << std::endl;
    }
    void VisiteComponent(window *p_c) {
        oss << p_c->GetComponentName() << std::endl;
    }

    void VisiteComponent(house_component *p_c) override {
        if(auto p_sc = dynamic_cast<house*>(p_c); p_sc != nullptr) {
            VisiteComponent(p_sc);
        } else if(auto p_sc = dynamic_cast<roof*>(p_c); p_sc != nullptr) {
            VisiteComponent(p_sc);
        } else if(auto p_sc = dynamic_cast<room*>(p_c); p_sc != nullptr) {
            VisiteComponent(p_sc);
        } else if(auto p_sc = dynamic_cast<door*>(p_c); p_sc != nullptr) {
            VisiteComponent(p_sc);
        } else if(auto p_sc = dynamic_cast<window*>(p_c); p_sc != nullptr) {
            VisiteComponent(p_sc);
        } else {
            // nothing to do
        }

        return;
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
