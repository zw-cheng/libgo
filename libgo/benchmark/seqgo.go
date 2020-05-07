package main

import (
	"fmt"
	"time"
)

func main() {
	start := time.Now()

	sum := 0
	for i := 0; i < 50000; i++ {
		x := i
		sum += x
	}

	elapsed := time.Since(start)
	fmt.Println("time elapsed:  %s", elapsed.Nanoseconds())

	fmt.Println("sum =", sum)

}
