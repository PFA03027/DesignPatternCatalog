//! Copyright (c) 2022, PFA03027@nifty.com


pub mod house_maker_strategy;

use crate::house_maker_strategy::{AlgT, HouseMakerCtx};


fn main() {
    let mut house_maker: HouseMakerCtx = HouseMakerCtx::new();

    house_maker.make_house();

    house_maker.select_maker(&AlgT::EldestPig);
    house_maker.make_house();

    house_maker.select_maker(&AlgT::SecondPig);
    house_maker.make_house();

    house_maker.select_maker(&AlgT::YoungestPig);
    house_maker.make_house();
}
