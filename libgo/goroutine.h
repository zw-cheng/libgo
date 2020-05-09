#include <boost/coroutine/all.hpp>

#ifndef goroutine_h
#define goroutine_h

// the role type of a coroutine
enum coro_type
{
    sender,
    receiver
}; 

// template <typename Func>
class goroutine
{
public:
    template <typename Func>
    goroutine(Func f, int id) : source(f), id(id)
    {
    }

    void execute()
    {
        source = std::move(source());
    }

    // excluded from the scheduler if done
    bool done = false;
    int id;
    coro_type my_type;
    boost::coroutines::coroutine<void>::pull_type source;
};

#endif /* goroutine_h */
