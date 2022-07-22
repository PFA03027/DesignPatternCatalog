//! Adapter class as Adapter pattern sample
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

use crate::straw_housemaker::StrawHouseMaker;
use crate::wood_housemaker::WoodHouseMaker;
use crate::stone_housemaker::StoneHouseMaker;


pub trait ReceptionDesk {
    /// 自分自身をprintln!()で出力するAPIに対するアダプタI/F
    fn order_house(&self);
}
 
impl ReceptionDesk for StrawHouseMaker {
    /// 自分自身をprintln!()で出力するAPI
    fn order_house(&self) {
        self.create_house();
    }
}

impl ReceptionDesk for WoodHouseMaker {
    /// 自分自身をprintln!()で出力するAPI
    fn order_house(&self) {
        self.generate_house();
    }
}

impl ReceptionDesk for StoneHouseMaker {
    /// 自分自身をprintln!()で出力するAPI
    fn order_house(&self) {
        self.make_house();
    }
}
