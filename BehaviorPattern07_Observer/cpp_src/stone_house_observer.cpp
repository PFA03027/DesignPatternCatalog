/**
 * @file stone_house_observer.cpp
 * @author PFA03027@nifty.com
 * @brief example of observer pattern
 * @version 0.1
 * @date 2022-09-23
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 */

#include <memory>
#include <string>
#include <iostream>
#include <sstream>

#include "observer_pattern.h"

/**
 * @brief subjectクラスの具象化クラス
 * 
 * MVCモデルで言うところのM
 */
class stone_house : public base_subject {
public:
    stone_house(void) : state_("no_state") {}

    void SetState(const std::string& new_state) {
        state_ = new_state;
        notify_update();
    }

    std::string GetState(void) const {
        return state_;
    }

private:
    std::string state_;
};

/**
 * @brief observerクラスの具象化クラス
 * 
 * MVCモデルで言うところのV
 */
class stone_house_observer : public base_observer {
public:
    stone_house_observer(std::weak_ptr<stone_house> wp_sh_arg, int id_arg) : wp_sh_(wp_sh_arg), id_(id_arg) {}

    void update(const base_subject*) override {
        if (std::shared_ptr<stone_house> r = wp_sh_.lock()) {
            std::cout << "observer" << id_ << ": " << r->GetState() << std::endl;
        } else {
            // shared_ptrオブジェクトの寿命が切れているため、observerリストから削除する
            std::cout << "observer" << id_ << ": no subject" << std::endl;
        }
    }

private:
    std::weak_ptr<stone_house> wp_sh_;
    int id_;
};


int main(void) {
    auto sp_sbj_sh = std::make_shared<stone_house>();
    auto sp_obsvr_sho1 = std::make_shared<stone_house_observer>(sp_sbj_sh, 1);
    auto sp_obsvr_sho2 = std::make_shared<stone_house_observer>(sp_sbj_sh, 2);
    auto sp_obsvr_sho3 = std::make_shared<stone_house_observer>(sp_sbj_sh, 3);

    // start subscribe
    sp_sbj_sh->subscribe_observer(sp_obsvr_sho1);
    sp_sbj_sh->subscribe_observer(sp_obsvr_sho2);
    sp_sbj_sh->subscribe_observer(sp_obsvr_sho3);

    // start to make update call back.
    sp_sbj_sh->SetState("youngest pig makes base of stone house");

    sp_sbj_sh->unsubscribe_observer(sp_obsvr_sho1); // unsubscribe a observer

    std::cout << std::endl;
    sp_sbj_sh->SetState("youngest pig builds stone house on base");

    sp_obsvr_sho2.reset();  // a observer drop out

    std::cout << std::endl;
    sp_sbj_sh->SetState("youngest pig makes interior");

    return 0;
}