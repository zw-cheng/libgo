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
    
    // simply call the constructor
    chan<T> make(int bs);

    // put value x into channel
    void send (T x);
    
    // get an x from channel
    T receive ();
    
    // a sender close the channel, meaning there is no more producers
    void close ();

private:
    // members
    int buffer_size;
    bool closed = false;
    ConcurrentQueue<T> q;
};


// class channel_closed : public runtime_error{
//     public:
//     explicit channel_closed(string &s) : runtime_error(s) {}
// };


// constructors
template <typename T>
chan<T>::chan() : buffer_size(0){
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
    q.enqueue(x);
    // cout << "send called, approximate q size: " << q.size_approx()<<endl;
}


template <typename T>
T chan<T>::receive(){
    T top;

    // block and try
    while(!q.try_dequeue(top)){
        if(closed){
            throw runtime_error("channel closed");
        }
    }
    
    return top;
}

// channel operations
template <typename T>
void chan<T>::close(){
    closed = true;
    cout << "this channel is closed" <<endl;
}


#endif /* channel_h */
