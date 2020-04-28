#include <boost/coroutine/all.hpp>

#ifndef goroutine_h
#define goroutine_h

using namespace boost::coroutines;

void cooperative(coroutine<void>::push_type &sink){
    cout << "Hello";
    sink();
    cout << "world";
}

#endif /* goroutine_h */
