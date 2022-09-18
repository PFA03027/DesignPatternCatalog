trait HouseComponent {
    //! コンポジットパターンを実現するためのI/Fを定義するトレイト
    //! 
    //! 子のコレクションをトラバースするI/Fは、トレイトを実装する構造体側で実現する方式。

    fn add_component(&mut self, c: Box<dyn HouseComponent>);
    fn what_have(&self, depth: i8);
}

// 具象化クラス
struct House {
    children: Vec<Box<dyn HouseComponent>>,
}

// 具象化クラスに対応するI/Fの実装
impl House {
    fn new() -> House
    {
        House {
            children: Vec::new(),
        }
    }
}

// 具象化クラスに対応するコンポジットパターンを実現するためのI/Fの実装
impl HouseComponent for House {
    fn add_component(&mut self, c: Box<dyn HouseComponent>)
    {
        self.children.push(c)
    }

    fn what_have(&self, depth: i8)
    {
        let mut _i: i8;
        for _i in 0..depth {
            print!("  ")
        }
        println!("House");

        let next_depth = depth + 1;
        for e in &self.children {
            e.what_have(next_depth);
        }
    }
}


// 具象化クラス
struct Room {
    children: Vec<Box<dyn HouseComponent>>,
}

// 具象化クラスに対応するI/Fの実装
impl Room {
    fn new() -> Room
    {
        Room {
            children: Vec::new(),
        }
    }
}

// 具象化クラスに対応するコンポジットパターンを実現するためのI/Fの実装
impl HouseComponent for Room {
    fn add_component(&mut self, c: Box<dyn HouseComponent>)
    {
        self.children.push(c)
    }

    fn what_have(&self, depth: i8)
    {
        let mut _i: i8;
        for _i in 0..depth {
            print!("  ")
        }
        println!("Room");

        let next_depth = depth + 1;
        for e in &self.children {
            e.what_have(next_depth);
        }
    }
}


// 具象化クラス
struct Window {
    children: Vec<Box<dyn HouseComponent>>,
}

// 具象化クラスに対応するI/Fの実装
impl Window {
    fn new() -> Window
    {
        Window {
            children: Vec::new(),
        }
    }
}

// 具象化クラスに対応するコンポジットパターンを実現するためのI/Fの実装
impl HouseComponent for Window {
    fn add_component(&mut self, c: Box<dyn HouseComponent>)
    {
        self.children.push(c)
    }

    fn what_have(&self, depth: i8)
    {
        let mut _i: i8;
        for _i in 0..depth {
            print!("  ")
        }
        println!("Window");

        let next_depth = depth + 1;
        for e in &self.children {
            e.what_have(next_depth);
        }
    }
}

fn main() {
    let w1 = Box::new(Window::new());
    let mut room1 = Box::new(Room::new());
    room1.add_component(w1);
    let w21 = Box::new(Window::new());
    let w22 = Box::new(Window::new());
    let mut room2 = Box::new(Room::new());
    room2.add_component(w21);
    room2.add_component(w22);
    let mut house1 = House::new();
    house1.add_component(room1);
    house1.add_component(room2);

    house1.what_have(0);
    // expected result:
    // House
    //   Room
    //     Window
    //   Room
    //     Window
    //     Window
}
