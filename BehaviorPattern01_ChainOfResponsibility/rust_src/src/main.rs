//! Chain of Responsibility pattern trait
//! 
//! Copyright (c) 2022, PFA03027@nifty.com





pub mod chain_of_responsibility;

use crate::chain_of_responsibility::{RequestHandler, handle_chain};


struct StrawHouseOfElderPig {}
impl StrawHouseOfElderPig {
    fn new() -> Self {
        StrawHouseOfElderPig {}
    }
}

impl RequestHandler for StrawHouseOfElderPig {
    fn handle(&mut self, req_str: &String) -> bool {
        println!("{} : blow off straw house!", req_str);
        true
    }
}

struct WoodHouseOf2ndPig {}
impl WoodHouseOf2ndPig {
    fn new() -> Self {
        WoodHouseOf2ndPig {}
    }
}

impl RequestHandler for WoodHouseOf2ndPig {
    fn handle(&mut self, req_str: &String) -> bool {
        println!("{} : fire wood house!", req_str);
        true
    }
}

    
struct StoneHouseOfYoungestPig {}
impl StoneHouseOfYoungestPig {
    fn new() -> Self {
        StoneHouseOfYoungestPig {}
    }
}

impl RequestHandler for StoneHouseOfYoungestPig {
    fn handle(&mut self, req_str: &String) -> bool {
        println!("{} : Not break stone house! So, fail {}", req_str, req_str);
        false
    }
}


fn main() {
    let mut pigs_houses: Vec<Box<dyn RequestHandler>> = vec![];

    pigs_houses.push(Box::new(StrawHouseOfElderPig::new()));
    pigs_houses.push(Box::new(WoodHouseOf2ndPig::new()));
    pigs_houses.push(Box::new(StoneHouseOfYoungestPig::new()));

    handle_chain(&mut pigs_houses, &String::from("Wolf Attack! "));
}
