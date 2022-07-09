
pub mod construct_custom_home;
pub mod straw_housemaker;
pub mod wood_housemaker;
pub mod stone_housemaker;

use crate::straw_housemaker::StrawHouse;
use crate::wood_housemaker::WoodHouse;
use crate::stone_housemaker::StoneHouse;
use crate::construct_custom_home::HouseConstructor;



fn main() {
    let cch1 = HouseConstructor::new(|| { Box::new(StrawHouse::new()) });
    cch1.make_story();
    let cch2 = HouseConstructor::new(|| { Box::new(WoodHouse::new()) });
    cch2.make_story();
    let cch3 = HouseConstructor::new(|| { Box::new(StoneHouse::new()) });
    cch3.make_story();
}
