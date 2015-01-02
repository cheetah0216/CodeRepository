package main

import "fmt"

func case_for() {
    for i := 0; i < 3; i++ {
        fmt.Printf("%d\n", i)
    }   
}

func case_goto() {
    i := 0
Num:
    fmt.Println(i)
    if i < 3 {
        i++
        goto Num
    }
}

func case_array() {
    //var arr := [3]int{1, 2, 3} //Error
    arr := [3]int{1, 2, 3} //复合声明
    fmt.Printf("%v\n", arr);

    for i := 0; i < 3; i++  {
        arr[i] = i;
    }
    fmt.Printf("%v\n", arr);

}

func main() {
    fmt.Print("Hello, World!\n")
    case_for() 
    case_goto()
    case_array()
}
