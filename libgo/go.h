#ifndef go_h
#define go_h

#include "scheduler.h"

class go
{
public:
    template <typename Func>
    go (Func f)
    {
        scheduler::spawn(f);
    }
};

#endif