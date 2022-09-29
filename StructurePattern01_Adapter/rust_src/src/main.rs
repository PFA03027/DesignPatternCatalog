//! Adapter pattern
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

pub mod reception_desk_adapter;
pub mod straw_housemaker;
pub mod wood_housemaker;
pub mod stone_housemaker;


use crate::straw_housemaker::StrawHouseMaker;
use crate::wood_housemaker::WoodHouseMaker;
use crate::stone_housemaker::StoneHouseMaker;
use crate::reception_desk_adapter::ReceptionDesk;

fn customer_request_order(rc: &Vec<Box<dyn ReceptionDesk>>) {
    rc[0].order_house();
    rc[1].order_house();
    rc[2].order_house();
}

fn main() {
    let mut maker_array: Vec<Box<dyn ReceptionDesk>> = Vec::new();
    maker_array.push(Box::new(StrawHouseMaker::new()));
    maker_array.push(Box::new(WoodHouseMaker::new()));
    maker_array.push(Box::new(StoneHouseMaker::new()));

    customer_request_order(&maker_array);
}
