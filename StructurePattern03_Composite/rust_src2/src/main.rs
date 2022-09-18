use std::iter::Iterator;
use std::collections::VecDeque;

trait HouseComponent {
    //! コンポジットパターンを実現するためのI/Fを定義するトレイト
    //! 
    //! 以下のネット記事を参考に、
    //! 子のコレクションをトラバースするためのI/Fを、Iteratorトレイトを使って実現。
    //! get_children関数の戻り型のライフタイムの記載方法が味噌。
    //! https://qiita.com/wada314/items/0e53f564779ab1261ee2
    //! 
    //! 子のコレクションをトラバースするためのI/Fを、Iteratorトレイトを使って実現しているため、
    //! トレイトを実装する構造体が、子の保持に使用するコレクションには非依存となっている。
    //! 

    fn add_component(&mut self, c: Box<dyn HouseComponent>);
    
    // fn get_children_mut<'a>(&'a mut self) ->  Box<dyn Iterator<Item = &'a mut Box<dyn HouseComponent>> + 'a>;
    fn get_children(&mut self) ->  Box<dyn Iterator<Item = &mut Box<dyn HouseComponent>> + '_>;
    
    fn what_is(&mut self);

    fn scan_by_what_is(&mut self) {
        self.scan_by_what_is_internal(0);
    }

    fn scan_by_what_is_internal(&mut self, depth: i8) {
        let mut _i: i8;
        for _i in 0..depth {
            print!("  ")
        }
        self.what_is();

        let next_depth = depth + 1;
        for e in self.get_children() {
            e.scan_by_what_is_internal(next_depth);
        }
    }
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

    fn get_children(&mut self) ->  Box<dyn Iterator<Item = &mut Box<dyn HouseComponent>> + '_> {
        let it = (&mut self.children).into_iter();
        Box::new(it)
    }

    fn what_is(&mut self) {
        println!("House");
    }
}


// 具象化クラス
struct Room {
    children: VecDeque<Box<dyn HouseComponent>>,
}

// 具象化クラスに対応するI/Fの実装
impl Room {
    fn new() -> Room
    {
        Room {
            children: VecDeque::new(),
        }
    }
}

// 具象化クラスに対応するコンポジットパターンを実現するためのI/Fの実装
impl HouseComponent for Room {
    fn add_component(&mut self, c: Box<dyn HouseComponent>)
    {
        self.children.push_back(c)
    }

    fn get_children(&mut self) ->  Box<dyn Iterator<Item = &mut Box<dyn HouseComponent>> + '_> {
        let it = (&mut self.children).into_iter();
        Box::new(it)
    }

    fn what_is(&mut self) {
        println!("Room");
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

    fn get_children(&mut self) ->  Box<dyn Iterator<Item = &mut Box<dyn HouseComponent>> + '_> {
        let it = (&mut self.children).into_iter();
        Box::new(it)
    }

    fn what_is(&mut self) {
        println!("Window");
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

    house1.scan_by_what_is();
    // expected result:
    // House
    //   Room
    //     Window
    //   Room
    //     Window
    //     Window
}
