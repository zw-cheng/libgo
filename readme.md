# Current progress

We implemted a simple channel based on [concurrentQueue](https://github.com/cameron314/concurrentqueue)

We used the sample code from [official tutorial](https://tour.golang.org/concurrency/2) to test it (file included in /goexample).

A comprison of go grammar and ours:

| operation                     | golang                                 | libgo                                    |
|-------------------------------|----------------------------------------|------------------------------------------|
| create a goroutine            | go func()                              | TODO :(                                  |
| create an unbuffered channel  | ch := make(chan int)                   | auto ch = chan<int>();                   |
|                               |                                        | auto ch = make<int>();                   |
| create a buffered channel     | ch := make(chan int, 2)                | auto ch = chan<int>(2);                  |
|                               |                                        | auto ch = make<int>(2);                  |
| send value x into the channel | ch <- x                                | ch.send(x);                              |
| receive x from the channel    | x <- ch                                | x = ch.receive();                        |
| discard x from the channel    | <- ch                                  | ch.receive();                            |
| sender close the channel      | v, ok := <-ch  // check is ok is false | try{ch.receive()}  catch(exception e){ } |

# Todo

1. Make function calls concurrent via boost::coroutine.

2. Make grammar looks better using operater overlaoding.

3. Unbuffered channels need blocking mechanism.

4. evaluation of performance.
