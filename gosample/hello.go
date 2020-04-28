package main

import "fmt"

func sum(s []int, ch chan int) {
	sum := 0
	for _, v := range s {
		sum += v
	}
	ch <- sum // send sum to ch
}

func main() {
	s := []int{1, 2, 3, 4}

	ch := make(chan int)
	go sum(s[:len(s)/2], ch)
	go sum(s[len(s)/2:], ch)

	x, y := <-ch, <-ch // receive from ch

	fmt.Println("sum", x, " + sum", y, " = result", x+y)
}
