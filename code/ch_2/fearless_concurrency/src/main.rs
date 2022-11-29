fn create_vec() -> Vec<i32> {
    // Create a vector, and pass ownership to caller
    let mut vec = Vec::new();
    let n = 5;
    for i in 1..n {
        vec.push(i)
    }
    vec
}

fn processor_borrows(vec: &Vec<i32>) {
    // Function doesn't take ownership of vector

    for i in vec.iter() {
        println!("i: {}", i);
    }
}

fn  processor_borrows_mut(vec: &mut Vec<i32>) {
    // Function doesn't take ownership of vector,
    // but can mutate it via a mutable reference

    for i in 0..vec.len() {
        vec[i] = vec[i]*2;
    }
}

fn processor_owns(vec: Vec<i32>) {
    
    for i in vec.iter() {
        println!("i: {}", i);
    } 
}


fn main() {
    let vec = create_vec();
    processor_owns(vec);

    // Calling functions below now will cause an error, as ownership of vec has been passed
    processor_borrows(&vec);
    processor_borrows_mut(&mut vec);
    // to 'processor_owns', resulting in error message:
    // 43 |     processor_borrows(&vec)
    //                       ^^^^ value borrowed here after move

    // The below is valid, as there is still only one mutable reference
    let mut vec2 = create_vec();
    processor_borrows_mut(&mut vec2);
    processor_borrows(&vec2);

    // The following will not work, as we create two mutable references,
    let r1 = &mut vec2;
    let r2 = &mut vec2;
    processor_borrows_mut(r1);
    processor_borrows_mut(r2);
    // obtaining the following error:
    // 53 |     let r1 = &mut vec2;
    //    |              --------- first mutable borrow occurs here
    // 54 |     let r2 = &mut vec2;
    //    |              ^^^^^^^^^ second mutable borrow occurs here    
}
