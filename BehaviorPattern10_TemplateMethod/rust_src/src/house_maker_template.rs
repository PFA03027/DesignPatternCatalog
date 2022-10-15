//! Copyright (c) 2022, PFA03027@nifty.com

pub trait HouseMakerBase {
    fn make_house(&self) {
        print!("{}", self.get_maker_name());
        print!("{}", self.get_verb());
        print!("{}", self.get_material());
        print!(" house");
        println!("{}", self.hook_tail());
    }

    fn get_maker_name(&self) -> String;
    fn get_material(&self) -> String;

    fn get_verb(&self) -> String {
        String::from(" makes ")
    }
    fn hook_tail(&self) -> String {
        String::from("")
    }
}

