//! 非同期型の構成で実現するObserver pattern
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 
//! rust_src2を非同期タスクで書き直したものです。executorは、async_stdを想定しています。
//! ただし、Condvarのためにunstableを使用したり、トレイトのasyncが未対応のために、直接I/Fを呼び出したりしています。
//! まだまだ、実用的に使うのは難しいかもしれないと感じました。
//! 

use std::sync::Arc;
use std::time;
use async_std::task;
use futures::future::join_all;

pub mod observer_pattern_async_task;

use crate::observer_pattern_async_task::{MsgData, BaseObserver, BaseSubjectNotifier, BaseSubject, SubjectAgent};

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
        let _ret = self.bsn_.notify_msg(msg);
    }
}

impl StoneHouse {
    fn new() -> StoneHouse {
        StoneHouse {
            state_: String::from("no_state"),
            bsn_: BaseSubjectNotifier::new_arc()
        }
    }

    async fn set_state(&mut self, new_state: String) {
        // println!("set_state: {}", new_state);
        self.state_ = new_state;
        let _ret = self.bsn_.notify_msg(MsgData::MsgNotifyUpdate).await;
    }

    fn get_state(&self) -> String {
        self.state_.clone()
    }
}



fn main() {
    let mut box_sa = SubjectAgent::new_box(StoneHouse::new());  // Subjectと、Subjectに対するエージェントを生成
    let wprw_sbj = box_sa.get_weak_to_subject();            // Subjectに対するWeakポインタを取得
    let arc_nter =box_sa.get_notifier();                    // エージェントに対するnotifierを取得

    // observerの作成
    let (mut box_shobs1, snder1) = BaseObserver::new_box_sender(wprw_sbj.clone());
    let (mut box_shobs2, snder2) = BaseObserver::new_box_sender(wprw_sbj.clone());
    let (mut box_shobs3, snder3) = BaseObserver::new_box_sender(wprw_sbj.clone());

    // subjectとobserverの相互作用の構築
    box_sa.subscribe(snder1.clone());
    box_sa.subscribe(snder2.clone());
    box_sa.subscribe(snder3);

    // observer、subject agiant、更新処理の非同期タスクの作成
    let mut tsk_hdl_vec = vec![];

    tsk_hdl_vec.push( task::spawn(async move {
        box_shobs1.rcv_loop(
            |st: &StoneHouse| {
                let t = st.get_state();
                println!("observer1: {}", t);
            }
        ).await;
    }));
    tsk_hdl_vec.push( task::spawn(async move {
        box_shobs2.rcv_loop(
            |st: &StoneHouse| {
                let t = st.get_state();
                println!("observer2: {}", t);
            }
        ).await;
    }));
    tsk_hdl_vec.push( task::spawn(async move {
        box_shobs3.rcv_loop(
            |st: &StoneHouse| {
                let t = st.get_state();
                println!("observer3: {}", t);
            }
        ).await;
    }));
    tsk_hdl_vec.push( task::spawn(async move {
        box_sa.rcv_loop().await;
    }));

    tsk_hdl_vec.push( task::spawn(async move {
        {
            let wp_sbj = wprw_sbj.upgrade().unwrap();
            let mut guarded_sbj = wp_sbj.write().await;
            guarded_sbj.set_state(String::from("youngest pig makes base of stone house")).await;
        }   // RwLockのwriteロックを解放する
        task::sleep(time::Duration::from_millis(100)).await;

        let ret = snder1.send(MsgData::MsgReqTerminate).await;
        ret.unwrap();
        {
            let wp_sbj = wprw_sbj.upgrade().unwrap();
            let mut guarded_sbj = wp_sbj.write().await;
            guarded_sbj.set_state(String::from("youngest pig builds stone house on base")).await;
        }   // RwLockのwriteロックを解放する
        task::sleep(time::Duration::from_millis(100)).await;

        let ret = snder2.send(MsgData::MsgReqTerminate).await;
        ret.unwrap();
        {
            let wp_sbj = wprw_sbj.upgrade().unwrap();
            let mut guarded_sbj = wp_sbj.write().await;
            guarded_sbj.set_state(String::from("youngest pig makes interior")).await;
        }   // RwLockのwriteロックを解放する
        task::sleep(time::Duration::from_millis(100)).await;

        let _ret = arc_nter.notify_msg(MsgData::MsgReqTerminate).await;
    }));

    let all_ft = join_all(tsk_hdl_vec);    // 複数の非同期タスクのFutureをまとめる。
    task::block_on(all_ft);                 // 非同期タスクの実行開始！
}
