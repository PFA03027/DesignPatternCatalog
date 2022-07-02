//! Abstract Factory pattern implementation for Abstract Factory trait
//! トレイトを使って、Abstract Factory patternを実装する
//! 
//! abstract factoryは具象クラスを包含する関係ではないため、Abstract Factory traitでは、具象クラス用モジュールを定義しない。
//! 
//! Rustでは、クラス継承の機能がないため、abstract productが備えるべきI/Fも、traitを使って定義する。
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 


/// rust風： 生成物house productが備えるべきI/Fを定義するtrait
/// C++風： 生成物house productの抽象クラス
pub trait AbstractHouseProduct {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self);

    /// Wolfの襲撃！　結果をprintln!()で出力するAPI
    fn wolf_attacked(&self);
}

/// rust風： 生成物garden productが備えるべきI/Fを定義するtrait
/// C++風： 生成物house productの抽象クラス
pub trait AbstractGardenProduct {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self);
}

/// 生成物house, gardenの生成を担うFactory I/Fを定義するトレイト
pub trait AbstractHousemakerFactory {
    /// rust風： AbstractHouseProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractHouseProductの具象クラスを生成するAPI
    fn make_house(&self) -> Box<dyn AbstractHouseProduct>;

    /// rust風： AbstractGardenProductのトレイトを実装したオブジェクトを生成するAPI
    /// C++風： AbstractGardenProductの具象クラスを生成するAPI
    fn make_garden(&self) -> Box<dyn AbstractGardenProduct>;
}
