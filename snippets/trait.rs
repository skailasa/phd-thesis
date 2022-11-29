// Custom type declaration, with its own set of attributes
// and methods
pub struct MyType {
    pub attribute String;

    pub fn bar() {
        println!("I'm a default implementation defined on this type.")
    }
};

// Traits specify an interface
pub trait MyTrait {
    fn foo(&self) -> String;
};

pub trait MyOtherTrait {
    fn baz(&self) -> String;
}

// We can implement this interface for our type
impl MyTrait for MyType {
    pub fn foo() {
        format!("I'm a required method for this trait.")
    }
};

impl MyOtherTrait for MyType {
    pub fn baz() {
        format!("I'm a required method for this trait.")
    }
}

fn main () {
    let mytype = MyType{attribute: "boz"};

    // Use behaviour from MyTrait
    println!(mytype.foo());
    
    // Use behaviour from MyOtherTrait
    println!(mytype.baz());

    // Use behaviour defined by MyType itself
    println!(mytype.bar());
}
