//! Adaptee class as Adapter pattern sample
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

pub struct StrawHouseMaker {
}

/// 構造体StrawHouseの固有I/Fの定義
impl StrawHouseMaker {
    pub fn new() -> StrawHouseMaker {
        StrawHouseMaker {}
    }

    /// 自分自身をprintln!()で出力するAPI
    pub fn create_house(&self) {
        println!("create a straw house");
    }
}

