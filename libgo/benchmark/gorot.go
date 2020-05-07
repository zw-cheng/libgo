package main

import (
	"fmt"
	"time"
)

func sum(ch chan int) {
	for i := 0; i < 50000; i++ {
		ch <- i
	}
}

func main() {

	start := time.Now()

	ch := make(chan int)
	go sum(ch)

	sum := 0
	for i := 0; i < 50000; i++ {
		x := <-ch
		sum += x
	}

	elapsed := time.Since(start)
	fmt.Println("time elapsed:  %s", elapsed.Nanoseconds())

	fmt.Println("sum=", sum)
}
