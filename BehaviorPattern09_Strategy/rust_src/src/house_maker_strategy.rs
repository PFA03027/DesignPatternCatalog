//! Strategy pattern trait
//! 
//! Copyright (c) 2022, PFA03027@nifty.com


#[derive(Clone, Copy, PartialEq, Debug)]
pub enum AlgT {
    EldestPig,
    SecondPig,
    YoungestPig
}

/////////// Trait as Strategy class /////////
trait HouseMakerTrait {
    fn make_house(&mut self);
}

/////////// Struct as ConcreteStrategy class /////////
struct NoHouseMaker {}
impl NoHouseMaker {
    fn new() -> Self {
        NoHouseMaker {}
    }
}

impl HouseMakerTrait for NoHouseMaker {
    fn make_house(&mut self) {
        println!("no pig, no house");
    }
}

struct StrawHouseMaker {}
impl StrawHouseMaker {
    fn new() -> Self {
        StrawHouseMaker {}
    }
}

impl HouseMakerTrait for StrawHouseMaker {
    fn make_house(&mut self) {
        println!("This is straw house");
    }
}

struct WoodHouseMaker {}
impl WoodHouseMaker {
    fn new() -> Self {
        WoodHouseMaker {}
    }
}

impl HouseMakerTrait for WoodHouseMaker {
    fn make_house(&mut self) {
        println!("This is wood house");
    }
}

struct StoneHouseMaker {}
impl StoneHouseMaker {
    fn new() -> Self {
        StoneHouseMaker {}
    }
}

impl HouseMakerTrait for StoneHouseMaker {
    fn make_house(&mut self) {
        println!("This is stone house");
    }
}

/////////// Struct as Context class /////////
pub struct HouseMakerCtx {
    box_hmb_: Box<dyn HouseMakerTrait>
}

impl HouseMakerCtx {
    pub fn new() -> Self {
        HouseMakerCtx {
            box_hmb_: Box::new(NoHouseMaker::new())
        }
    }

    pub fn select_maker(&mut self, at: &AlgT) {
        match at {
            AlgT::EldestPig => {
                self.box_hmb_ = Box::new(StrawHouseMaker::new())
            },
            AlgT::SecondPig => {
                self.box_hmb_ = Box::new(WoodHouseMaker::new())
            },
            AlgT::YoungestPig => {
                self.box_hmb_ = Box::new(StoneHouseMaker::new())
            }
        }
    }

    pub fn make_house(&mut self) {
        self.box_hmb_.make_house();
    }
}
