//! Singleton pattern
//! Copyright (c) 2023, PFA03027@nifty.com
//!
//! lazy_staticによる実装例です。
//! ほとんど、下記のReferenceの写経です。。。
//!
//! Reference
//! https://stackoverflow.com/questions/27791532/how-do-i-create-a-global-mutable-singleton
//!

use lazy_static::lazy_static; // 1.4.0
use std::sync::Mutex;

pub struct HouseMaker {}

/// 構造体StoneHouseの固有I/Fの定義
impl HouseMaker {
    pub fn new() -> HouseMaker {
        HouseMaker {}
    }

    /// 自分自身をprintln!()で出力するAPI
    /// 書き換え可能なAPIを呼び出せることを示すために、あえてmut selfとする。
    pub fn print_i_am(&mut self) {
        println!("My house maker ID is 0x");
    }
}

lazy_static! {
    static ref SINGLETON_HOUSE_MAKER: Mutex<HouseMaker> = Mutex::new(HouseMaker::new());
}

fn do_a_call() {
    SINGLETON_HOUSE_MAKER.lock().unwrap().print_i_am();
}

fn main() {
    do_a_call();
    do_a_call();
    do_a_call();
}
