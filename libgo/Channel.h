#include "concurrentqueue.h"
#include <iostream>
#include <string>
using namespace std;
using namespace moodycamel;

#ifndef channel_h
#define channel_h

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


    void operator<<(T &x);
    bool operator>>(T &x);

private:
    int current_size;
    int buffer_size;
    bool closed = false;
    ConcurrentQueue<T> q;
};


// constructors
template <typename T>
chan<T>::chan() : buffer_size(INT_MAX), current_size(0){
    // this should be special - an unbuffered channel should block
    cout << "Unbuffered channel initialized" << endl;
}

template <typename T>
chan<T>::chan(int bs) : buffer_size(bs), current_size(0){
    cout << "Buffered channel initialized" << endl;
}

template <typename T>
chan<T> make(int bs = 0) {
    return bs == 0 ? chan<T>() : chan<T>(bs);
};


// channel operations
template <typename T>
void chan<T>::send(T x){
    while(current_size >= buffer_size);
    current_size++;
    q.enqueue(x);
    // cout << "send called, approximate q size: " << q.size_approx()<<endl;
}

// return bool instead and don't throw exception
template <typename T>
bool chan<T>::receive(T &x){
    // block and try
    while(!q.try_dequeue(x)){
        if(closed){
            return false;
        }
    }
    current_size--;
    return true;
}

// channel operations
template <typename T>
void chan<T>::close(){
    closed = true;
    cout << "this channel is closed" <<endl;
}

template<typename T>
void chan<T>::operator<<(T &x){
    return this->send(x);
}

template<typename T>
bool chan<T>::operator>>(T &x){
    // todo : Exception
    return this->receive(x);
}

#endif /* channel_h */
