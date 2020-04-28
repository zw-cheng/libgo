#include "concurrentqueue.h"
#include <iostream>
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
    
    chan<T> make(int bs);

    // put value x into channel
    void send (T x);
    
    // get an x from channel
    T receive ();

private:
    // members
    int buffer_size;\
    ConcurrentQueue<T> q;
};


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
    return chan<T>(bs);
};


template <typename T>
void chan<T>::send(T x){
    q.enqueue(x);
    cout << "send called, approximate q size: " << q.size_approx()<<endl;
}


template <typename T>
T chan<T>::receive(){
    T top;
    q.try_dequeue(top);
    return top;
}

#endif /* channel_h */
