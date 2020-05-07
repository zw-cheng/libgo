#include <boost/coroutine/all.hpp>
#include <unordered_map>
#include <deque>

#ifndef scheduler_h
#define scheduler_h

#include "channel.h"
#include "goroutine.h"


class scheduler {
public:
    static void schedule(){
        goroutine* first_coroutine = coroutine_queue.front();
        coroutine_queue.pop_front();
        first_coroutine->execute();
        coroutine_queue.push_back(first_coroutine);
    }

    template <typename Func>
    static void spawn(Func f){
        count++;
        done_m[count] = false;
        coroutine_queue.emplace_back(new goroutine((
            [f](boost::coroutines::coroutine<void>::push_type& sink) mutable {
                current_sink = std::move(sink);
                f(); 
                done_m[count] = true;
                return;
            }
        ), count));
    }

    static boost::coroutines::coroutine<void>::push_type current_sink;

private:
    static deque<goroutine*> coroutine_queue;
    static unordered_map<int, bool> done_m;
    static int count;
};


//template <typename Function /*, typename... Arguments */>

// void go(Function func /*, Arguments... parameters*/)
// {
//     cout << "go called" << endl;
//     scheduler::spawn();
//     // put this function into the queue 
//     func(/*parameters...*/);
// }


#endif // scheduler_h