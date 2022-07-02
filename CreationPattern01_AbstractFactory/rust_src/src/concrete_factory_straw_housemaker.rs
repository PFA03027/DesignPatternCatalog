//! Abstract Factory pattern implementation for Concrete class of straw house maker
//! トレイトを使って、Abstract Factory patternを実装する
//! 
//! straw house makerの実装
//! abstract factory house makerの具象クラスの実装に相当する。
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

use crate::abstract_factory_housemaker::{AbstractHouseProduct, AbstractGardenProduct, AbstractHousemakerFactory};

/// rust風： 生成物house productの構造体定義
/// C++風： 生成物house productの具象クラスの実装
/// 
/// このサンプルでは、StrawHouseは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
struct StrawHouse {
}

/// 構造体StrawHouseの固有I/Fの定義
impl StrawHouse {
    pub fn new() -> StrawHouse {
        StrawHouse {}
    }
}

/// rust風： 構造体StrawHouseに対する、AbstractHouseProduct traitの実装
/// C++風： 生成物house productの抽象クラスのI/Fに対する実装
impl AbstractHouseProduct for StrawHouse {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self) {
        println!("This is house by Straws");
    }

    /// Wolfの襲撃！　結果をprintln!()で出力するAPI
    fn wolf_attacked(&self) {
        println!("Wolf is attached. Then, Straw house is broken");
    }
}


/// rust風： 生成物garden productの構造体定義
/// C++風： 生成物garden productの具象クラスの実装
/// 
/// このサンプルでは、StrawGardenは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
struct StrawGarden {
}

/// 構造体StrawGardenの固有I/Fの定義
impl StrawGarden {
    pub fn new() -> StrawGarden {
        StrawGarden {}
    }
}

/// rust風： 構造体StrawGardenに対する、AbstractGardenProduct traitの実装
/// C++風： 生成物garden productの抽象クラスのI/Fに対する実装
impl AbstractGardenProduct for StrawGarden {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self) {
        println!("This is garden by Straws");
    }
}


/// rust風： 生成物straw housemakerの構造体定義
/// C++風： 生成物straw housemakerの具象クラスの実装
/// 
/// このサンプルでは、StrawHouseMakerは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
pub struct StrawHouseMaker {
}

/// 構造体StrawHouseMakerの固有I/Fの定義
impl StrawHouseMaker {
    pub fn new() -> StrawHouseMaker {
        StrawHouseMaker {}
    }
}

/// rust風： 構造体StrawHouseMakerに対する、AbstractHousemakerFactory traitの実装
/// C++風： 生成物straw housemakerの抽象クラスのI/Fに対する実装
impl AbstractHousemakerFactory for StrawHouseMaker {
    /// rust風： AbstractHouseProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractHouseProductの具象クラスを生成するAPI
    fn make_house(&self) -> Box<dyn AbstractHouseProduct> {
        Box::new(StrawHouse::new())
    }

    /// rust風： AbstractGardenProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractGardenProductの具象クラスを生成するAPI
    fn make_garden(&self) -> Box<dyn AbstractGardenProduct> {
        Box::new(StrawGarden::new())
    }
}

