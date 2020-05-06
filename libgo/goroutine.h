#include <boost/coroutine/all.hpp>
#include "channel.h"

#ifndef goroutine_h
#define goroutine_h

using namespace boost::coroutines;

template <typename Function, typename... Arguments>
void go(Function func, Arguments... parameters)
{
    cout << "go called" << endl;
    func(parameters...);
}

void cooperative(coroutine<void>::push_type &sink)
{
    cout << "Hello";
    sink();
    cout << "world";
}

#endif /* goroutine_h */
