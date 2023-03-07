use std::cmp::max;

fn main(){
    const C: usize = 14;
    const N: usize = 3;
    let mut P: [usize; C+1] = [0; C+1];

    println!("<< C = 14 and n = 3 >>\n");

    println!("------(1)------\n");
    let mut w: [usize; 3] = [4, 6, 8];
    let p: [usize; 3] = [7, 6, 9];
    println!("w | 4 | 6 | 8 |");
    println!("  -------------");
    println!("p | 7 | 6 | 9 |\n");

    for i in 0..N {
        for weight in w[i]..C+1 {
            P[weight] = max(P[weight], P[weight - w[i]] + p[i]);
        }
    }

    println!("The result is: {}\n", P[C]);


    println!("------(2)------\n");
    w[0] = 5;
    println!("w | 5 | 6 | 8 |");
    println!("  -------------");
    println!("p | 7 | 6 | 9 |\n");

    //Initialisation of P
    for i in 0..C+1 {
        P[i] = 0;
    }

    for i in 0..N {
        for weight in w[i]..C+1 {
            P[weight] = max(P[weight], P[weight - w[i]] + p[i]);
        }
    }

    println!("The result is: {}\n", P[C]); 
}
