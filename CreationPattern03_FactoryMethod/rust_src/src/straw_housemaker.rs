//! Abstract Factory pattern implementation for Concrete class of straw house maker
//! トレイトを使って、Abstract Factory patternを実装する
//! 
//! straw house makerの実装
//! abstract factory house makerの具象クラスの実装に相当する。
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 

use crate::construct_custom_home::AbstractHouseProduct;

/// rust風： 生成物house productの構造体定義
/// C++風： 生成物house productの具象クラスの実装
/// 
/// このサンプルでは、StrawHouseは内部状態を持たないため、メンバ変数は定義せず、構造体定義のみとなっている。
pub struct StrawHouse {
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

