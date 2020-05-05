#include <boost/coroutine/all.hpp>
#include "channel.h"

#ifndef goroutine_h
#define goroutine_h

using namespace boost::coroutines;

// namespace goroutine
// {
//     char go;

//     template <typename T>
//     inline void operator + (go, T f)
//     {
//         // scheduler::spawn(f);
//     }
// }

void cooperative(coroutine<void>::push_type &sink){
    cout << "Hello";
    sink();
    cout << "world";
}

#endif /* goroutine_h */
