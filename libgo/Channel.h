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
    
    // // simply call the constructor
    // chan<T> make(int bs);

    // put value x into channel
    void send (T x);
    
    // get an x from channel
    bool receive (T &x);
    
    // a sender close the channel, meaning there is no more producers
    void close ();

    //void operator<<(T &x);
    //bool operator>>(T &x);

    int current_size = 0;
    int buffer_size;
    bool closed = false;
    ConcurrentQueue<T> q;

    friend void operator >> (chan<T>& ch, T& x)
    {
        ch.send(x);
    }

    friend void operator << (chan<T>& ch, T& x)
    {
        ch.receive(x);
    }
};


// constructors
template <typename T>
chan<T>::chan() : buffer_size(INT_MAX){
    // this should be special - an unbuffered channel should block
    cout << "Unbuffered channel initialized" << endl;
}

template <typename T>
chan<T>::chan(int bs) : buffer_size(bs){
    cout << "Buffered channel initialized" << endl;
}

template <typename T>
chan<T> make(int bs = 0) {
    return bs == 0 ? chan<T>() : chan<T>(bs);
};


// channel operations
template <typename T>
void chan<T>::send(T x){
    // while(current_size >= buffer_size);
    current_size++;
    q.enqueue(x);
    // yield to main()
    cout << "send called, approximate q size: " << q.size_approx()<<endl;
    scheduler::current_sink();
}

// return bool instead and don't throw exception
template <typename T>
bool chan<T>::receive(T &x){
    if(!q.try_dequeue(x)){
        // yield to the scheduler
        if(closed){
            return false;
        }
        return false;
    } else {
        current_size--;
        scheduler::schedule();
        return true;
    }
}

// channel operations
template <typename T>
void chan<T>::close(){
    closed = true;
    cout << "this channel is closed" <<endl;
}

// template<typename T>
// void chan<T>::operator<<(T &x){
//     return this->send(x);
// }

// template<typename T>
// bool chan<T>::operator>>(T &x){
//     // todo : Exception
//     return this->receive(x);
// }

#endif /* channel_h */
