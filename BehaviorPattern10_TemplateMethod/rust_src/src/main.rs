//! Copyright (c) 2022, PFA03027@nifty.com

pub mod house_maker_template;

use crate::house_maker_template::HouseMakerBase;

struct StrawHouseMaker {}
impl StrawHouseMaker {
    fn new() -> Self {
        StrawHouseMaker{}
    }
}
impl HouseMakerBase for StrawHouseMaker {
    fn get_maker_name(&self) -> String {
        String::from("Eldest pig")
    }
    fn get_material(&self) -> String {
        String::from("straw")
    }
}
    
struct WoodHouseMaker {}
impl WoodHouseMaker {
    fn new() -> Self {
        WoodHouseMaker{}
    }
}
impl HouseMakerBase for WoodHouseMaker {
    fn get_maker_name(&self) -> String {
        String::from("Second pig")
    }
    fn get_material(&self) -> String {
        String::from("wood")
    }
}
    
struct StoneHouseMaker {}
impl StoneHouseMaker {
    fn new() -> Self {
        StoneHouseMaker{}
    }
}
impl HouseMakerBase for StoneHouseMaker {
    fn get_maker_name(&self) -> String {
        String::from("Youngest pig")
    }
    fn get_material(&self) -> String {
        String::from("stone")
    }
}
    
struct WolfAttack {}
impl WolfAttack {
    fn new() -> Self {
        WolfAttack{}
    }
}
impl HouseMakerBase for WolfAttack {
    fn get_maker_name(&self) -> String {
        String::from("Wolf")
    }
    fn get_material(&self) -> String {
        String::from("stone")
    }
    fn get_verb(&self) -> String {
        String::from(" try break ")
    }
    fn hook_tail(&self) -> String {
        String::from(", but fail")
    }
}
    
fn main() {
    let house_maker1: StrawHouseMaker = StrawHouseMaker::new();
    let house_maker2: WoodHouseMaker = WoodHouseMaker::new();
    let house_maker3: StoneHouseMaker = StoneHouseMaker::new();
    let wolf_attack: WolfAttack = WolfAttack::new();

    house_maker1.make_house();
    house_maker2.make_house();
    house_maker3.make_house();
    wolf_attack.make_house();
}
