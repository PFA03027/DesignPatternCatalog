
trait HouseComponent {
    //! Decoratorが対象とするトレイト

    fn view(&self) -> String;
}

// 藁の家
struct StrawHouse {}

impl StrawHouse {
    fn new() -> StrawHouse {
        StrawHouse{}
    }
}

impl HouseComponent for StrawHouse {
    fn view(&self) -> String {
        String::from("StrawHouse")
    }
}

// 木の家
struct WoodHouse {}

impl WoodHouse {
    fn new() -> WoodHouse {
        WoodHouse{}
    }
}

impl HouseComponent for WoodHouse {
    fn view(&self) -> String {
        String::from("WoodHouse")
    }
}

// 石の家
struct StoneHouse {}

impl StoneHouse {
    fn new() -> StoneHouse {
        StoneHouse{}
    }
}

impl HouseComponent for StoneHouse {
    fn view(&self) -> String {
        String::from("StoneHouse")
    }
}

// 電飾デコレータ
// デコレータI/F用のトレイトを挟む方法もあるが、lifetimeの面倒さを考えると、
// 素直にトレイトオブジェクトへの参照を保持する方が実装が楽になると思われる。
struct IlluminationHouseDecorator<'a> {
    hc: &'a dyn HouseComponent,
}

impl IlluminationHouseDecorator<'_> {
    fn new(hc_arg: &dyn HouseComponent) -> IlluminationHouseDecorator<'_> {
        IlluminationHouseDecorator{ hc: hc_arg }
    }
}

impl HouseComponent for IlluminationHouseDecorator<'_> {
    fn view(&self) -> String {
        let mut v = self.hc.view();
        v += " with Illumination";
        v
    }
}

// 花デコレータ
struct FlowerHouseDecorator<'a> {
    hc: &'a dyn HouseComponent,
}

impl FlowerHouseDecorator<'_> {
    fn new(hc_arg: &dyn HouseComponent) -> FlowerHouseDecorator<'_> {
        FlowerHouseDecorator{ hc: hc_arg }
    }
}

impl HouseComponent for FlowerHouseDecorator<'_> {
    fn view(&self) -> String {
        let mut v = self.hc.view();
        v += " with Flower";
        v
    }
}

// デコレータの有無に依存しない関数
fn do_view( hc_arg: &dyn HouseComponent) {
    println!("{}", hc_arg.view());
}

fn test_func1() {
    let house1 = StrawHouse::new();
    let house2 = WoodHouse::new();
    let house3 = StoneHouse::new();
    let deco2 = IlluminationHouseDecorator::new(&house2);
    let deco31 = IlluminationHouseDecorator::new(&house3);
    let deco32 = FlowerHouseDecorator::new(&deco31);

    do_view(&house1);
    do_view(&deco2);
    do_view(&deco32);
    // expected result:
    // StrawHouse
    // WoodHouse with Illumination
    // StoneHouse with Illumination with Flower
}

fn test_func2() {
    let house1 = Box::new(StrawHouse::new());
    let house2 = Box::new(WoodHouse::new());
    let house3 = Box::new(StoneHouse::new());
    let deco2 = Box::new(IlluminationHouseDecorator::new(&*house2));
    let deco31 = Box::new(IlluminationHouseDecorator::new(&*house3));
    let deco32 = Box::new(FlowerHouseDecorator::new(&*deco31));

    do_view(&*house1);
    do_view(&*deco2);
    do_view(&*deco32);
    // expected result:
    // StrawHouse
    // WoodHouse with Illumination
    // StoneHouse with Illumination with Flower
}

fn main() {
    test_func1();
    test_func2();
}
