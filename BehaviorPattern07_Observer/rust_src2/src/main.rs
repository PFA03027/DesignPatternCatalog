//! 非同期型の構成で実現するObserver pattern
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 
//! ほぼActive Object化したObserver pattern用モジュールのサンプル実装
//! 可変参照と共有参照が共存できない課題を、メッセージを介した相互作用として構成しなおした構造となっている。
//! 結果として、SubjectAgent、BaseObserverのオブジェクトは専用スレッドが必要となってしまっている。
//! 

use std::sync::Arc;
use std::{thread, time};

pub mod observer_pattern_async_thread;

use crate::observer_pattern_async_thread::{MsgData, BaseObserver, BaseSubjectNotifier, BaseSubject, SubjectAgent};

// ObserverパターンにおけるSubjectとなる構造体
struct StoneHouse {
    state_: String,
    bsn_: Arc<BaseSubjectNotifier>
}

impl BaseSubject for StoneHouse {
    fn accept_notifyer(&mut self, nter_arg: Arc<BaseSubjectNotifier>) {
        self.bsn_ = nter_arg;
    }
    fn notify_msg(&self, msg: MsgData) {
        self.bsn_.notify_msg(msg);
    }
}

impl StoneHouse {
    fn new() -> StoneHouse {
        StoneHouse {
            state_: String::from("no_state"),
            bsn_: BaseSubjectNotifier::new_arc()
        }
    }

    fn set_state(&mut self, new_state: String) {
        // println!("set_state: {}", new_state);
        self.state_ = new_state;
        self.notify_msg(MsgData::MsgNotifyUpdate);
    }

    fn get_state(&self) -> String {
        self.state_.clone()
    }
}





fn main() {
    let mut box_sa = SubjectAgent::new_box(StoneHouse::new());  // Subjectと、Subjectに対するエージェントを生成
    let wprw_sbj = box_sa.get_weak_to_subject();            // Subjectに対するWeakポインタを取得
    let arc_nter =box_sa.get_notifier();                    // エージェントに対するnotifierを取得

    let (mut box_shobs1, snder1) = BaseObserver::new_box_sender(wprw_sbj.clone());
    let (mut box_shobs2, snder2) = BaseObserver::new_box_sender(wprw_sbj.clone());
    let (mut box_shobs3, snder3) = BaseObserver::new_box_sender(wprw_sbj.clone());

    box_sa.subscribe(snder1.clone());
    box_sa.subscribe(snder2.clone());
    box_sa.subscribe(snder3);

    let mut th_hdl_vec = vec![];

    th_hdl_vec.push(
        thread::spawn(move || {
            box_shobs1.rcv_loop(
                |st: &StoneHouse| {
                    let t = st.get_state();
                    println!("observer1: {}", t);
                }
            );
            ()
        })
    );
    th_hdl_vec.push(
        thread::spawn(move || {
            box_shobs2.rcv_loop(
                |st: &StoneHouse| {
                    let t = st.get_state();
                    println!("observer2: {}", t);
                }
            );
            ()
        })
    );
    th_hdl_vec.push(
        thread::spawn(move || {
            box_shobs3.rcv_loop(
                |st: &StoneHouse| {
                    let t = st.get_state();
                    println!("observer3: {}", t);
                }
            );
            ()
        })
    );
    th_hdl_vec.push(
        thread::spawn(move || {
            box_sa.rcv_loop();
            ()
        })
    );

    wprw_sbj.upgrade().unwrap().write().unwrap().set_state(String::from("youngest pig makes base of stone house"));
    thread::sleep(time::Duration::from_millis(100));

    snder1.send(MsgData::MsgReqTerminate).unwrap();
    wprw_sbj.upgrade().unwrap().write().unwrap().set_state(String::from("youngest pig builds stone house on base"));
    thread::sleep(time::Duration::from_millis(100));

    snder2.send(MsgData::MsgReqTerminate).unwrap();
    wprw_sbj.upgrade().unwrap().write().unwrap().set_state(String::from("youngest pig makes interior"));

    thread::sleep(time::Duration::from_millis(100));
    arc_nter.notify_msg(MsgData::MsgReqTerminate);

    for th in th_hdl_vec {
        th.join().unwrap()
    }
}
