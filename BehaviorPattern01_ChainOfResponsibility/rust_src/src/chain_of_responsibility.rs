//! Chain of Responsibility pattern trait
//! 
//! Copyright (c) 2022, PFA03027@nifty.com

////////////// trait of request handler //////////////
pub trait RequestHandler {
    fn handle(&mut self, req_str: &String) -> bool;
}

pub fn handle_chain( hdler_list: &mut Vec<Box<dyn RequestHandler>>, req_str: &String ) {
    for rh in hdler_list {
        let ret = rh.handle(req_str);
        if ret == false {
            break;
        }
    }
}
