//!
//! Observerパターンは、SubjectとObserverが相互に参照され、かつ両者とも可変であるという構造上の、本質的な難しさがあります。
//! そのため、Weak<>による無効オブジェクトの参照回避と、RefCell<>による動的な借用制御が必要になります。
//! 
//! 上記を踏まえて、まずは素直な実装をした場合のObserverパターンの実装例と使用例です。
//! これは、ObserverパターンのキーポイントとなるSubjectの変化を通知する方法を関数呼び出しで実現する実装となっています。
//! 
//! しかしながら、set_stateを使って、Subject側＝StoneHouseを変更した場合、StoneHouse自身ではなく、setを呼び出した側が
//! 能動的にnotify_updateを呼び出す実装となっています。
//! これは、SubjectのsetのためのRefCellの可変参照有効中に、共有参照がObserver側から呼び出されないようにするため、
//! 明確な分離が必要となったためです。
//! 一応この構成でも動作していますが、setの呼び出しに伴いStoneHouse自身がnotify_updateを呼び出せないのは、実用上問題になります。
//! 
//! notify_updateをsetの中から呼び出せないのは、Observer側のupdate関数を直接呼び出しているためです。
//! そこで、notify_updateをチャンネル経由のメッセージで通知する構成が次のサンプルになります。
//! このアプローチは比較的規模が大きくなるので、小さいプログラムには向かないかもしれません。
//! 
//! その他にも、unsafeブロックを使用したり、マクロを使用してsetとnotify_updateを同時に実施できるようにする等のアプローチもあると思います。
//! 

use std::rc::{Rc, Weak};
use std::cell::RefCell;
use std::iter::Iterator;

pub mod observer_pattern;

use crate::observer_pattern::{BaseObserver, BaseSubject};

// subjectの具象化構造体に相当
struct StoneHouse {
    state_: String,
    bsol_: Vec<Weak<RefCell<dyn BaseObserver>>>
}

impl StoneHouse {
    fn new() -> StoneHouse {
        StoneHouse { state_: String::from("no_state"), bsol_: vec![] }
    }

    fn set_state(&mut self, new_state: String) {
        self.state_ = new_state;
    }

    fn get_state(&self) -> String {
        let ans = self.state_.clone();
        ans
    }
}

// subjectの具象化構造体にsubjectのトレイトを実装
impl BaseSubject for StoneHouse {
    fn   subscribe_observer(&mut self, wp_obsvr: Weak<RefCell<dyn BaseObserver>>) {
        self.bsol_.push(wp_obsvr);
    }
    fn as_base_subject_observer_list(&self) -> Box<dyn Iterator<Item = &Weak<RefCell<dyn BaseObserver>>> + '_> {
        let it = (&self.bsol_).into_iter();
        Box::new(it)
    }
}

// Observerの具象化構造体に相当
struct StoneHouseObserver {
    wp_subject_: Weak<RefCell<StoneHouse>>,
    id_: i32
}

impl StoneHouseObserver {
    fn new(wp_sh_arg: Weak<RefCell<StoneHouse>>, id: i32) -> StoneHouseObserver {
        StoneHouseObserver { wp_subject_: wp_sh_arg, id_: id }
    }
}

// Observerの具象化構造体にObserverのトレイトを実装
impl BaseObserver for StoneHouseObserver {
    fn update(&mut self) {
        let lg = self.wp_subject_.upgrade();
        match lg {
            None => {},
            Some(r) => {
                let s = r.borrow();
                let t = s.get_state();
                println!("observer{}: {}", self.id_, t);
            }
        }
    }
}


fn main() {
    let rc_sh = Rc::new(RefCell::new(StoneHouse::new()));

    let rc_shobs = Rc::new(RefCell::new(StoneHouseObserver::new(Rc::downgrade(&rc_sh), 1)));
    let rc_to_bo1: Rc<RefCell<dyn BaseObserver>> = rc_shobs.clone();
    {
        let rc_shobs = Rc::new(RefCell::new(StoneHouseObserver::new(Rc::downgrade(&rc_sh), 2)));
        let rc_to_bo2: Rc<RefCell<dyn BaseObserver>> = rc_shobs.clone();
        {
            let rc_shobs = Rc::new(RefCell::new(StoneHouseObserver::new(Rc::downgrade(&rc_sh), 3)));
            let rc_to_bo3: Rc<RefCell<dyn BaseObserver>> = rc_shobs.clone();

            rc_sh.borrow_mut().subscribe_observer(Rc::downgrade(&rc_to_bo1));
            rc_sh.borrow_mut().subscribe_observer(Rc::downgrade(&rc_to_bo2));
            rc_sh.borrow_mut().subscribe_observer(Rc::downgrade(&rc_to_bo3));

            rc_sh.borrow_mut().set_state(String::from("youngest pig makes base of stone house"));
            rc_sh.borrow().notify_update();
        }

        println!("");
        rc_sh.borrow_mut().set_state(String::from("youngest pig builds stone house on base"));
        rc_sh.borrow().notify_update();
    }

    println!("");
    rc_sh.borrow_mut().set_state(String::from("youngest pig makes interior"));
    rc_sh.borrow().notify_update();
}
