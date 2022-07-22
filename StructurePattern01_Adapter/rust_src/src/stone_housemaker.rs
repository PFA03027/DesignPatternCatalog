//! Adaptee class as Adapter pattern sample
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

pub struct StoneHouseMaker {
}

/// 構造体StoneHouseの固有I/Fの定義
impl StoneHouseMaker {
    pub fn new() -> StoneHouseMaker {
        StoneHouseMaker {}
    }

    /// 自分自身をprintln!()で出力するAPI
    pub fn make_house(&self) {
        println!("make a stone house");
    }
}

