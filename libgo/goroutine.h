#include <boost/coroutine/all.hpp>


#ifndef goroutine_h
#define goroutine_h


// template <typename Func>
class goroutine{
public:
    template <typename Func>
    goroutine(Func f, int id) : source(f), id(id)
    {
    }

    void execute()
    {
        source = std::move(source());
    }

    bool done = false;
    int id;
    boost::coroutines::coroutine<void>::pull_type source;
    // boost::coroutines::coroutine<void>::push_type sink;
};


void cooperative(boost::coroutines::coroutine<void>::push_type &sink)
{
    cout << "Hello";
    sink();
    cout << "world";
}

#endif /* goroutine_h */
