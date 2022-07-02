
pub mod abstract_factory_housemaker;
pub mod concrete_factory_straw_housemaker;
pub mod concrete_factory_wood_housemaker;
pub mod concrete_factory_stone_housemaker;
pub mod wolf_attack_story;

use crate::concrete_factory_straw_housemaker::StrawHouseMaker;
use crate::concrete_factory_wood_housemaker::WoodHouseMaker;
use crate::concrete_factory_stone_housemaker::StoneHouseMaker;
use crate::wolf_attack_story::wolf_attack_story;







fn main() {
    println!("Hello, world!");

    let eldest_pig_housemaker = Box::new(StrawHouseMaker::new());
    let second_pig_housemaker = Box::new(WoodHouseMaker::new());
    let youngest_pig_housemaker = Box::new(StoneHouseMaker::new());

    wolf_attack_story(eldest_pig_housemaker);
    wolf_attack_story(second_pig_housemaker);
    wolf_attack_story(youngest_pig_housemaker);
}
