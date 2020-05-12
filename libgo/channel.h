#include "concurrentqueue.h"
#include <iostream>
#include <string>
using namespace std;
using namespace moodycamel;

#ifndef channel_h
#define channel_h

#include "scheduler.h"

template <typename T>
class chan {
public:
    // constructors
    chan();

    chan(int bs);
    
    // simply call the constructor
    chan<T> make(int bs);

    // put value x into channel
    void send (T x);
    
    // get an x from channel
    void receive (T &x);
    
    // a sender close the channel, meaning there is no more producers
    void close ();

    void operator<<(T &x);
    void operator>>(T &x);

    int current_size = 0;
    int buffer_size;
    bool closed = false;
    ConcurrentQueue<T> q;
};

// when the number of elements stored in the queue is equal to the size of
// buffer, the senders cannot send data until the receiver receives data from
// the queue

// constructors
// unbuffered channel: only accept sends if there is a corresponding receive
template <typename T>
chan<T>::chan() : buffer_size(1){
    // this should be special - an unbuffered channel should block
#ifdef DEBUG
    cout << "Unbuffered channel initialized" << endl;
#endif
}

// buffered channel: accept a limited number of values without a corresponding receive
template <typename T>
chan<T>::chan(int bs) : buffer_size(bs){
#ifdef DEBUG
    cout << "Buffered channel initialized" << endl;
#endif
}

template <typename T>
chan<T> make(int bs = 0) {
    return bs == 0 ? chan<T>() : chan<T>(bs);
};

// channel operations
// push an element into the channel if the channel has some spare space
template <typename T>
void chan<T>::send(T x){
    // if the buffer is full, transfer to other coroutine to let the data be received
    int my_id = scheduler::coroutine_id_queue.back();
    while (current_size == buffer_size)
    {
        std::cout << "buffer full, transfer to main" << std::endl;
        std::cout << "my id is " << my_id << std::endl;
        scheduler::sink_m[my_id]();
    }

    current_size++;
    q.enqueue(x);
    if (current_size == buffer_size)
    {   
        scheduler::coroutine_id_queue.pop_back();
        scheduler::sink_m[my_id]();
    }
    else
        scheduler::schedule(my_id);
}

// pop an element from the channel
template <typename T>
void chan<T>::receive(T &x){
    // transfer control to other coroutines until the channel stores some data
    while (!q.try_dequeue(x)){
        scheduler::schedule(0);
    }
    current_size--;
}

// channel operations
template <typename T>
void chan<T>::close(){
    closed = true;
    cout << "this channel is closed" <<endl;
}

template<typename T>
void chan<T>::operator<<(T &x){
     this->send(x);
}

template<typename T>
void chan<T>::operator>>(T &x){
    this->receive(x);
}

template<typename T>
void operator << (chan<T>& ch, const T& x)
{
    ch.send(x);
}

template<typename T>
void operator >> (chan<T>& ch, const T& x)
{
    ch.receive(x);
}

#endif /* channel_h */
