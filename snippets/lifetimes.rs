fn main() {
    let r;

    // Lifetimes are defined by scope.
    {
        let x = 5;
        r = &x
    }
    println!("r: {}", r);
    // Results in error
    // 6 |         r = &x;
    // |             ^^ borrowed value does not live long enough
    // 7 |     }
  
}