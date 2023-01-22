//! Singleton pattern
//! Copyright (c) 2023, PFA03027@nifty.com
//!
//! once_cellによる実装例です。
//! ほとんど、下記のReferenceの写経です。。。
//!
//! Reference
//! https://stackoverflow.com/questions/27791532/how-do-i-create-a-global-mutable-singleton
//!

use once_cell::sync::Lazy; // 1.17.0
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

static SINGLETON_HOUSE_MAKER: Lazy<Mutex<HouseMaker>> = Lazy::new(|| Mutex::new(HouseMaker::new()));

fn do_a_call() {
    SINGLETON_HOUSE_MAKER.lock().unwrap().print_i_am();
}

fn main() {
    do_a_call();
    do_a_call();
    do_a_call();
}
