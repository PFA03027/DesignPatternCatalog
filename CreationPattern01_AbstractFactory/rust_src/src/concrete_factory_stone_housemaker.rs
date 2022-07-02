//! Abstract Factory pattern implementation for Concrete class of stone house maker
//! トレイトを使って、Abstract Factory patternを実装する
//! 
//! stone house makerの実装
//! abstract factory house makerの具象クラスの実装に相当する。
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

use crate::abstract_factory_housemaker::{AbstractHouseProduct, AbstractGardenProduct, AbstractHousemakerFactory};

/// rust風： 生成物house productの構造体定義
/// C++風： 生成物house productの具象クラスの実装
/// 
/// このサンプルでは、StoneHouseは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
struct StoneHouse {
}

/// 構造体StoneHouseの固有I/Fの定義
impl StoneHouse {
    pub fn new() -> StoneHouse {
        StoneHouse {}
    }
}

/// rust風： 構造体StoneHouseに対する、AbstractHouseProduct traitの実装
/// C++風： 生成物house productの抽象クラスのI/Fに対する実装
impl AbstractHouseProduct for StoneHouse {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self) {
        println!("This is house by Stones");
    }

    /// Wolfの襲撃！　結果をprintln!()で出力するAPI
    fn wolf_attacked(&self) {
        println!("Wolf is attached. But, Stone house is NOT broken");
    }
}


/// rust風： 生成物garden productの構造体定義
/// C++風： 生成物garden productの具象クラスの実装
/// 
/// このサンプルでは、StoneGardenは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
struct StoneGarden {
}

/// 構造体StoneGardenの固有I/Fの定義
impl StoneGarden {
    pub fn new() -> StoneGarden {
        StoneGarden {}
    }
}

/// rust風： 構造体StoneGardenに対する、AbstractGardenProduct traitの実装
/// C++風： 生成物garden productの抽象クラスのI/Fに対する実装
impl AbstractGardenProduct for StoneGarden {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self) {
        println!("This is garden by Stones");
    }
}


/// rust風： 生成物stone housemakerの構造体定義
/// C++風： 生成物stone housemakerの具象クラスの実装
/// 
/// このサンプルでは、StoneHouseMakerは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
pub struct StoneHouseMaker {
}

/// 構造体StoneHouseMakerの固有I/Fの定義
impl StoneHouseMaker {
    pub fn new() -> StoneHouseMaker {
        StoneHouseMaker {}
    }
}

/// rust風： 構造体StoneHouseMakerに対する、AbstractHousemakerFactory traitの実装
/// C++風： 生成物stone housemakerの抽象クラスのI/Fに対する実装
impl AbstractHousemakerFactory for StoneHouseMaker {
    /// rust風： AbstractHouseProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractHouseProductの具象クラスを生成するAPI
    fn make_house(&self) -> Box<dyn AbstractHouseProduct> {
        Box::new(StoneHouse::new())
    }

    /// rust風： AbstractGardenProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractGardenProductの具象クラスを生成するAPI
    fn make_garden(&self) -> Box<dyn AbstractGardenProduct> {
        Box::new(StoneGarden::new())
    }
}

