//! Factory Methodパターンで用意するProductのI/Fを定義するトレイトと、Factory Methodを使用するCreator構造体の実装
//! 
//! Rustでは、クラス継承の機能がないため、abstract productが備えるべきI/Fも、traitを使って定義する。
//! 
//! Copyright (c) 2022, PFA03027@nifty.com
//! 


/// rust風： Productが備えるべきI/Fを定義するtrait
/// C++風： Productの抽象クラス
pub trait AbstractHouseProduct {
    /// 自分自身をprintln!()で出力するAPI
    fn what_i_am(&self);

    /// Wolfの襲撃！　結果をprintln!()で出力するAPI
    fn wolf_attacked(&self);
}

/// rust風： Factory Methodを保持するCreator構造体。
/// C++風： Factory Methodを保持するCreatorクラス
pub struct HouseConstructor {
    do_make_house: fn() -> Box<dyn AbstractHouseProduct>
}

/// rust風： Factory Methodを保持するCreator構造体のI/Fの実装
/// C++風： Factory Methodを保持するCreatorクラスのI/Fの実装
impl HouseConstructor {
    /// Creator構造体のコンストラクタ
    pub fn new(fm: fn() -> Box<dyn AbstractHouseProduct>) -> HouseConstructor {
        HouseConstructor { do_make_house: fm }
    }

    /// Factory Methodを実際に使用するI/F
    pub fn make_story(&self) {
        let ahp = (self.do_make_house)();

        ahp.what_i_am();
        ahp.wolf_attacked();

        return;
    }
}
