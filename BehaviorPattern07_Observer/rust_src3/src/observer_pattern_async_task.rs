//! 非同期型タスクの構成で実現するObserver pattern
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 
//! rust_src2を非同期タスクで書き直したものです。executorは、async_stdを想定しています。
//! 

// use async_std::prelude::*;

// use async_std::channel;
use async_std::channel::{Sender, Receiver};
use std::sync::{Arc, Weak};
use std::collections::VecDeque;
use async_std::sync::{Mutex, Condvar, RwLock};
use futures::stream::{self, StreamExt};

/// Observer pattern制御用メッセージ
#[derive(Clone, Copy, PartialEq, Debug)]
pub enum MsgData {
    MsgNotifyUpdate,
    MsgReqTerminate,
    MsgInvalid
}

/// 型TのSubjectへのWeakポインタを持つObserver
pub struct BaseObserver<T> {
    wp_subject_: Weak<RwLock<T>>,   // 監視対象の型TのSubjectのインスタンスへのWeakポインタ
    rcver_: Receiver<MsgData>
}

impl<T> BaseObserver<T> {
    pub fn new_box_sender(wp_s_arg: Weak<RwLock<T>>) -> (Box<Self>, Sender<MsgData>) {
        let (s, r) = async_std::channel::unbounded();
        (Box::new(Self {
            wp_subject_: wp_s_arg,
            rcver_: r
        }),
        s)
    }

    /// Subject側からメッセージを受信するためのチャンネル用を生成し紐づける
    /// 戻り値：　生成されたチャンネルのSender
    pub fn bind_new_channel(&mut self) -> Sender<MsgData> {
        let (s, r) = async_std::channel::unbounded();
        self.rcver_ = r;
        s
    }

    pub async fn rcv_loop<F>(&mut self, call_back: F) where F: Fn(&T) {
        loop {
            let rcv_msg = self.rcver_.recv().await;
            // println!("BaseObserver::rcv_loop: {:?}", rcv_msg);
            match rcv_msg.unwrap() {
                MsgData::MsgNotifyUpdate => {
                    // println!("BaseObserver::rcv_loop: MsgData::MsgNotifyUpdate" );
                    let lg = self.wp_subject_.upgrade();
                    match lg {
                        None => {
                            // println!("BaseObserver::rcv_loop: wp_subject_.upgrade() None" );
                        },
                        Some(r) => {
                            // println!("BaseObserver::rcv_loop: wp_subject_.upgrade() T" );
                            let s = r.read().await;
                            // println!("BaseObserver::rcv_loop: wp_subject_.upgrade() T2" );
                            call_back(&*s)
                        }
                    }
                },
                MsgData::MsgReqTerminate => {
                    // println!("BaseObserver::rcv_loop: MsgData::MsgReqTerminate" );
                    break
                },
                _ => {}
            }
        }
    }
}

// SubjectとSubjectAgentを連携させる通知機能
pub struct BaseSubjectNotifier {
    msg_que_: Mutex<VecDeque<MsgData>>,
    cv_: Condvar
}
impl BaseSubjectNotifier {
    pub fn new_arc() -> Arc<Self> {
        Arc::new(
            Self {
                msg_que_: Mutex::new(VecDeque::new()),
               cv_: Condvar::new()
            }
        )
    }
    pub async fn notify_msg(&self, msg: MsgData) {
        // println!("BaseSubjectNotifier::notify_msg: {:?}", msg);
        let mut mq = self.msg_que_.lock().await;
        mq.push_back(msg);
        // We notify the condvar that the value has changed.
        self.cv_.notify_all();
    }
    pub async fn wait(&self) -> MsgData {
        // Wait for the thread to start up.
        let mut mq = self.msg_que_.lock().await;
        while mq.len() == 0 {
            mq = self.cv_.wait(mq).await;
        }
        mq.pop_front().unwrap()
    }
}

// Subjectで実装が必要となるトレイト
pub trait BaseSubject {
    fn accept_notifyer(&mut self, nter_arg: Arc<BaseSubjectNotifier>);
    fn notify_msg(&self, msg: MsgData);
}


/// 型TのSubjectを所有するエージェント?
pub struct SubjectAgent<T> where T: BaseSubject {
    arc_subject_: Arc<RwLock<T>>,
    observers_: Vec<Sender<MsgData>>,
    base_notfier_: Arc<BaseSubjectNotifier>
}

impl<T> SubjectAgent<T> where T: BaseSubject {
    pub fn new_box(mut t: T) -> Box<Self> {
        let arc_bsn = BaseSubjectNotifier::new_arc();
        t.accept_notifyer(arc_bsn.clone());
        Box::new(
            Self {
                arc_subject_: Arc::new(RwLock::new(t)),
                observers_: vec![],
                base_notfier_: arc_bsn,
            }
        )
    }

    /// Observerへのチャンネルを登録する
    pub fn subscribe(&mut self, mc_snder: Sender<MsgData>) {
        self.observers_.push(mc_snder);
    }

    pub fn get_weak_to_subject(&self) -> Weak<RwLock<T>> {
        Arc::downgrade(&self.arc_subject_)
    }

    pub fn get_notifier(&self) -> Arc<BaseSubjectNotifier> {
        self.base_notfier_.clone()
    }

    pub async fn rcv_loop(&mut self) {
        loop {
            // println!("SubjectAgent::rcv_loop: in");
            let rcv_msg = self.base_notfier_.wait().await;
            // println!("SubjectAgent::rcv_loop: rcv {:?}", rcv_msg);
            match rcv_msg {
                MsgData::MsgNotifyUpdate => {
                    self.notify_update_to_observers(MsgData::MsgNotifyUpdate).await;
                },
                MsgData::MsgReqTerminate => {
                    self.notify_update_to_observers(MsgData::MsgReqTerminate).await;
                    break;
                },
                _ => {}
            }
        }
    }

    /// Observerへの更新通知を送信する
    async fn notify_update_to_observers(&mut self, msg: MsgData) {
        let obs_stream = stream::iter(&self.observers_);

        obs_stream.for_each(|e| async {
            let ret = e.send(msg).await;
            if ret.is_err() {
                // println!("SubjectAgent::notify_update_to_observers: is_err true {:?}", msg);
            } else {
                // println!("SubjectAgent::notify_update_to_observers: is_err false {:?} {:?}", msg, ret);
            }
            ()
        }).await;
        // obs_stream.await;

        // let nv: Vec<_> = self.observers_.iter().filter_map(
        //     |e| async {
        //         let ret = e.send(msg).await;
        //         if ret.is_err() {
        //             println!("SubjectAgent::notify_update_to_observers: is_err true {:?}", msg);
        //             None
        //         } else {
        //             println!("SubjectAgent::notify_update_to_observers: is_err false {:?}", msg);
        //             Some(e) // 送信の成功したSenderだけを残す
        //         }
        //     } ).cloned().collect();    // cloned()を避けたいけれども、いい方法が思いつかない。
        // self.observers_ = nv;
    }
}

