//! Abstract Factory pattern implementation for Concrete class of wood house maker
//! トレイトを使って、Abstract Factory patternを実装する
//! 
//! wood house makerの実装
//! abstract factory house makerの具象クラスの実装に相当する。
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

use crate::abstract_factory_housemaker::{AbstractHouseProduct, AbstractGardenProduct, AbstractHousemakerFactory};

/// rust風： 生成物house productの構造体定義
/// C++風： 生成物house productの具象クラスの実装
/// 
/// このサンプルでは、WoodHouseは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
struct WoodHouse {
}

/// 構造体WoodHouseの固有I/Fの定義
impl WoodHouse {
    pub fn new() -> WoodHouse {
        WoodHouse {}
    }
}

/// rust風： 構造体WoodHouseに対する、AbstractHouseProduct traitの実装
/// C++風： 生成物house productの抽象クラスのI/Fに対する実装
impl AbstractHouseProduct for WoodHouse {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self) {
        println!("This is house by Woods");
    }

    /// Wolfの襲撃！　結果をprintln!()で出力するAPI
    fn wolf_attacked(&self) {
        println!("Wolf is attached. Then, Wood house is broken");
    }
}


/// rust風： 生成物garden productの構造体定義
/// C++風： 生成物garden productの具象クラスの実装
/// 
/// このサンプルでは、WoodGardenは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
struct WoodGarden {
}

/// 構造体WoodGardenの固有I/Fの定義
impl WoodGarden {
    pub fn new() -> WoodGarden {
        WoodGarden {}
    }
}

/// rust風： 構造体WoodGardenに対する、AbstractGardenProduct traitの実装
/// C++風： 生成物garden productの抽象クラスのI/Fに対する実装
impl AbstractGardenProduct for WoodGarden {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self) {
        println!("This is garden by Woods");
    }
}


/// rust風： 生成物wood housemakerの構造体定義
/// C++風： 生成物wood housemakerの具象クラスの実装
/// 
/// このサンプルでは、WoodHouseMakerは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
pub struct WoodHouseMaker {
}

/// 構造体WoodHouseMakerの固有I/Fの定義
impl WoodHouseMaker {
    pub fn new() -> WoodHouseMaker {
        WoodHouseMaker {}
    }
}

/// rust風： 構造体WoodHouseMakerに対する、AbstractHousemakerFactory traitの実装
/// C++風： 生成物wood housemakerの抽象クラスのI/Fに対する実装
impl AbstractHousemakerFactory for WoodHouseMaker {
    /// rust風： AbstractHouseProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractHouseProductの具象クラスを生成するAPI
    fn make_house(&self) -> Box<dyn AbstractHouseProduct> {
        Box::new(WoodHouse::new())
    }

    /// rust風： AbstractGardenProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractGardenProductの具象クラスを生成するAPI
    fn make_garden(&self) -> Box<dyn AbstractGardenProduct> {
        Box::new(WoodGarden::new())
    }
}

