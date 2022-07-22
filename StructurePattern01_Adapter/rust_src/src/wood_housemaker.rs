//! Adaptee class as Adapter pattern sample
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

pub struct WoodHouseMaker {
}

/// 構造体WoodHouseの固有I/Fの定義
impl WoodHouseMaker {
    pub fn new() -> WoodHouseMaker {
        WoodHouseMaker {}
    }

    /// 自分自身をprintln!()で出力するAPI
    pub fn generate_house(&self) {
        println!("generate a wood house");
    }
}

