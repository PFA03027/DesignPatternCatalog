//! Observer pattern trait
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 
//! 子のコレクションをトラバースするためのI/Fを、Iteratorトレイトを使って実現しているため、
//! トレイトを実装する構造体が、子の保持に使用するコレクションには非依存となっている。
//! 

use std::rc::Weak;
use std::cell::RefCell;
use std::iter::Iterator;

pub trait BaseObserver {
    fn update(&mut self);
}

pub trait BaseSubject {

    fn   subscribe_observer(&mut self, wp_obsvr: Weak<RefCell<dyn BaseObserver>>);
    fn as_base_subject_observer_list(&self) -> Box<dyn Iterator<Item = &Weak<RefCell<dyn BaseObserver>>> + '_>;

    fn notify_update(&self) {
        for e in self.as_base_subject_observer_list() {
            let lg = e.upgrade();
            match lg {
                None => {},
                Some(rc_ob) => {
                    let mut bo_tr = rc_ob.borrow_mut();
                    bo_tr.update();
                }
            }
        }
    }
}

