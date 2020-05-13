# Libgo

libgo is a C++ library providing goroutine-like coroutine scheduling, and communication is done via channel.

The goroutines are similated by coroutines provided by boost::coroutine. 
The channel is based on [concurrentQueue](https://github.com/cameron314/concurrentqueue).

# Usage

A comprison of go grammar and ours:

| operation                     | golang                                 | libgo                               |
|-------------------------------|----------------------------------------|-------------------------------------|
| create a goroutine            | go func()                              | go(func);                           |
| create an unbuffered channel  | ch := make(chan int)                   | auto ch = chan<int>();              |
|                               |                                        | auto ch = make<int>();              |
| create a buffered channel     | ch := make(chan int, 2)                | auto ch = chan<int>(2);             |
|                               |                                        | auto ch = make<int>(2);             |
| send value x into the channel | ch <- x                                | ch.send(x);                         |
|                               |                                        | ch >> x;                            |
| receive x from the channel    | x <- ch                                | ch.receive(x);                      |
|                               |                                        | ch << x;                            |
| discard x from the channel    | <- ch                                  | ch.receive();                       |
| sender close the channel      | v, ok := <-ch  // check is ok is false | bool ok = ch.receive() // check ok  |

# Scheduling policy

1. The main function acts as the only receiver while other goroutines act as senders.
2. If the channel is full and the sender wants to send data, the sender will give up its control and transfer control to the receiver.
3. If the channel is empty and the receiver wants to receive data, the receiver will give up its control and transfer control to one of the senders.
4. After a goroutine sends/receives data, it will transfer the control to other goroutine.
5. The scheduler maintains a queue of goroutines and always resumes the header of the queue and puts the header goroutine to the back og the queue.
