// This is a comment, and is ignored by the compiler
// You can test this code by clicking the "Run" button over there ->
// or if you prefer to use your keyboard, you can use the "Ctrl + Enter" shortcut

// This code is editable, feel free to hack it!
// You can always return to the original code by clicking the "Reset" button ->

// This is the main function
fn main(){
    // Statements here are executed when the compiled binary is called

    // Print text to the console
    println!("Hello World!");
    let a =5+2;
    let n=10;
    
    for i in 1..101 {
        if i < 10 {
            println!("fizzbuzz");
        } else {
            println!("{}", n);
        }
    }
    while n < 101 {
        if n -1 ==5  {
            println!("fizzbuzz");
        } else {
            println!("{}", n);
        }

    // Increment counter
    n= n+ 1;
    }
}
#EOF