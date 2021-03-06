#include <boost/coroutine/all.hpp>
#include <unordered_map>
#include <deque>

#ifndef scheduler_h
#define scheduler_h

#include "channel.h"
#include "goroutine.h"


class scheduler {
public:
	// choose a coroutine to execute
    static void schedule(int my_id){
        while (true)
        {
            goroutine* first_coroutine = coroutine_queue.front();
            coroutine_queue.pop_front();
            int id = first_coroutine->id;
            if (done_m[id])
            {
                continue;
            }

            // ignore the caller coroutine itself
            if (my_id != id)
            {
                // identify which is the coroutine that will be exeucted to find its context
                coroutine_id_queue.push_back(id);
                first_coroutine->execute();
                coroutine_queue.push_back(first_coroutine);
                break;
            }
        }
    }

	// spawn a new coroutine
    template <typename Func>
    static void spawn(Func f){
        count++;
        done_m[count] = false;
        int id = count;
        coroutine_queue.emplace_back(new goroutine((
            [f, id](boost::coroutines::coroutine<void>::push_type& sink) mutable {
                // record the caller context
                sink_m[id] = std::move(sink);
                coroutine_id_queue.push_back(id);
                f();
                // this coroutine's task is finished
                done_m[id] = true;
                return;
            }
        ), id));
    }

    // all the running coroutines, the scheduler will pick a coroutine from the pool to resume
    static deque<goroutine*> coroutine_queue;
    // record the execution of coroutines in order which ressembles the stack
    static deque<int> coroutine_id_queue;
    // whether the coroutine has finished
    static unordered_map<int, bool> done_m;
    // record the coroutine's corresponding context (sink), used to resume
    static unordered_map<int, boost::coroutines::coroutine<void>::push_type> scheduler::sink_m;
    // the number of coroutines
    static int count;
};

deque<goroutine*> scheduler::coroutine_queue;
deque<int> scheduler::coroutine_id_queue;
unordered_map<int, bool> scheduler::done_m;
unordered_map<int, boost::coroutines::coroutine<void>::push_type> scheduler::sink_m;
int scheduler::count = 0;

template <typename Function /*, typename... Arguments */>
void go(Function func /*, Arguments... parameters*/)
{
    scheduler::spawn(func);
}

#endif // scheduler_h