#include <vector>
#include "channel.h"
#include "goroutine.h"
#include "scheduler.h"

chan<int> ch = make<int>();

// an example
int main()
{
    go ([]() mutable {
        std::cout << "send 1" << std::endl;
        ch << 1;
        std::cout << "send 2" << std::endl;
        ch << 2;
        std::cout << "send 3" << std::endl;
        ch << 3;
    });

    go([]() mutable {
        std::cout << "send 4" << std::endl;
        ch << 4;
        std::cout << "send 5" << std::endl;
        ch << 5;
    });

    int recv;
    int sum = 0;
    ch >> recv;
    sum += recv;
    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
    ch >> recv;
    sum += recv;
    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
    ch >> recv;
    sum += recv;

    go([]() mutable {
        std::cout << "send 6" << std::endl;
        ch << 6;
        std::cout << "send 7" << std::endl;
        ch << 7;
        std::cout << "send 8" << std::endl;
        ch << 8;
     });

    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
    ch >> recv;
    sum += recv;
    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
    ch >> recv;
    sum += recv;
    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
    ch >> recv;
    sum += recv;
    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
    ch >> recv;
    sum += recv;
    std::cout << "recv is " << recv << " sum is " << sum << std::endl;
}

/*
void my_sum(vector<int> nums, chan<int> *ch)
{
    int res = 0;
    for (auto n : nums)
        res += n;
    *ch << res; // ch <- res
}

void example1()
{
    vector<int> nums{1, 2, 3, 4};

    // it should be called by adding go, but for now we call them sequencially
    my_sum( vector<int>(nums.begin(), nums.begin() + nums.size() / 2), &ch);
    my_sum( vector<int>(nums.begin() + nums.size() / 2, nums.end()), &ch);

    int res1;
    ch >> res1;
    int res2;
    ch >> res2;

    cout << "sum" << res1 << " + sum" << res2 << " = result" << res1 + res2 << endl;
}

void fib(int n, chan<int>* ch)
{
    int x = 0, y = 1;
    for (int i = 0; i < n; i++)
    {
        ch->send(x);
        int temp = x;
        x = y;
        y = temp + y;
    }
    ch->close();
}

void example2()
{
    // it should be called by adding go, but for now we call them sequencially
    go(fib, 10, &ch);

    int x;
    // ch.receive() returns false when it is closed
    while (ch.receive(x))
    {
        cout << x << endl;
    }
}

void f(coroutine<void>::push_type &sink)
{
    cout << "f called, num =" << 122 << endl;
    sink();
}

int main()
{
    coroutine<void>::pull_type source{cooperative};
    cout << ", ";
    source();
    cout << "!\n";

    // -------- above is just some test code of boost::coroutine
    
    ch = chan<int>();

    go(f);
    coroutine<void>::pull_type fs{f};
    
    cout << "\nExample 1 :\n";
    example1();

    cout << "\nExample 2 :\n";
    example2();

    return 0;
}
*/