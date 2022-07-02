/// このモジュールは、AbstractHousemakerFactoryトレイトのみに依存する。
/// よって、実際の構造体定義を知る必要はないため、useによる参照を含まない。
/// 
/// これにより、具象クラスが変更されても、このモジュールは再利用可能となり、Abstract Factoryパターンの意図が実現されたことととなる。
/// 

use crate::abstract_factory_housemaker::AbstractHousemakerFactory;

/// 家を立てた後に、オオカミが攻撃してくるというお話
pub fn wolf_attack_story(hm: Box<dyn AbstractHousemakerFactory>) {
    let built_house = hm.make_house();
    let built_garden = hm.make_garden();

    built_house.what_i_am();
    built_garden.what_i_am();
    built_house.wolf_attacked();
}
