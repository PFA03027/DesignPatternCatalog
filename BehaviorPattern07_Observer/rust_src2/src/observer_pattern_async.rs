//! 非同期型の構成で実現するObserver pattern
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 
//! ほぼActive Object化したObserver pattern用モジュールのサンプル実装
//! 可変参照と共有参照が共存できない課題を、メッセージを介した相互作用として構成しなおした構造となっている。
//! 結果として、SubjectAgent、BaseObserverのオブジェクトは専用スレッドが必要となってしまっている。
//! 
//! 型TがObserverが監視したいオブジェクトの型。
//! Obaserverは、型Tのオブジェクト(=Subject)をWeakポインタで参照。
//! 外部（ここではmain関数）からのSubjectを変更した際に、SubjectからSubjectAgentに更新が発生したことを通知することで、SubjectAgentから
//! Obaserverに、更新通知が届けられる。この通知を受けて、rcv_loop()で指定されたコールバックが呼び出される。
//! 
//! Observerパターンのように相互に参照・作用するような構造を持つデザインパターンは、
//! rustでは可変参照と共有参照が共存できないことを回避するために実装がなかなか大変になってしまうことがよくわかりました。
//! 
//! また、実際のところは、MVCパターンに近く、MとVがファイルで実装され、これらのモジュールを使用する関数がCに相当する役割を持つ形となっている。
//! 

use std::sync::mpsc::{Sender, Receiver};
use std::sync::{Arc, Weak, RwLock, Mutex, Condvar};
use std::collections::VecDeque;

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
        let (s, r) = std::sync::mpsc::channel();
        (Box::new(Self {
            wp_subject_: wp_s_arg,
            rcver_: r
        }),
        s)
    }

    /// Subject側からメッセージを受信するためのチャンネル用を生成し紐づける
    /// 戻り値：　生成されたチャンネルのSender
    pub fn bind_new_channel(&mut self) -> Sender<MsgData> {
        let (s, r) = std::sync::mpsc::channel();
        self.rcver_ = r;
        s
    }

    pub fn rcv_loop<F>(&mut self, call_back: F) where F: Fn(&T) {
        loop {
            let rcv_msg = self.rcver_.recv().unwrap();
            match rcv_msg {
                MsgData::MsgNotifyUpdate => {
                    let lg = self.wp_subject_.upgrade();
                    match lg {
                        None => {},
                        Some(r) => {
                            let s = r.read().unwrap();
                            call_back(&*s)
                        }
                    }
                },
                MsgData::MsgReqTerminate => {
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
    pub fn notify_msg(&self, msg: MsgData) {
        let mut mq = self.msg_que_.lock().unwrap();
        mq.push_back(msg);
        // We notify the condvar that the value has changed.
        self.cv_.notify_all();
    }
    pub fn wait(&self) -> MsgData {
        // Wait for the thread to start up.
        let mut mq = self.msg_que_.lock().unwrap();
        while mq.len() == 0 {
            mq = self.cv_.wait(mq).unwrap();
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

    pub fn rcv_loop(&mut self) {
        loop {
            let rcv_msg = self.base_notfier_.wait();
            match rcv_msg {
                MsgData::MsgNotifyUpdate => {
                    self.notify_update_to_observers(MsgData::MsgNotifyUpdate)
                },
                MsgData::MsgReqTerminate => {
                    self.notify_update_to_observers(MsgData::MsgReqTerminate);
                    break
                },
                _ => {}
            }
        }
    }

    /// Observerへの更新通知を送信する
    fn notify_update_to_observers(&mut self, msg: MsgData) {
        let nv: Vec<_> = self.observers_.iter().filter_map(
            |e| if e.send(msg).is_err() {
                None
            } else {
                Some(e) // 送信の成功したSenderだけを残す
            } ).cloned().collect();    // cloned()を避けたいけれども、いい方法が思いつかない。
        self.observers_ = nv;
    }
}

