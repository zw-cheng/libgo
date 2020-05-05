#include <vector>
#include "channel.h"
#include "goroutine.h"

template <typename T>
void my_sum(vector<int> nums, chan<T> &ch)
{
    int res = 0;
    for (auto n : nums)
        res += n;
    ch << res; // ch <- res
}

void example1()
{
    auto ch = make<int>(0); // my_chan := make(chan int)

    vector<int> nums{1, 2, 3, 4};

    // it should be called by adding go, but for now we call them sequencially
    my_sum(vector<int>(nums.begin(), nums.begin() + nums.size() / 2), ch);
    my_sum(vector<int>(nums.begin() + nums.size() / 2, nums.end()), ch);

    int res1;
    ch >> res1;
    int res2;
    ch >> res2;

    cout << "sum" << res1 << " + sum" << res2 << " = result" << res1 + res2 << endl;
}

template <typename T>
void fib(int n, chan<T> &ch)
{
    int x = 0, y = 1;
    for (int i = 0; i < n; i++)
    {
        ch.send(x);
        int temp = x;
        x = y;
        y = temp + y;
    }
    ch.close();
}

void example2()
{
    auto ch = chan<int>(10); // my_chan := make(chan int)

    // it should be called by adding go, but for now we call them sequencially
    fib(10, ch);

    int x;
    // ch.receive() returns false when it is closed
    while ( ch.receive(x) )  {
        cout << x << endl;
    }
}

int main()
{
    coroutine<void>::pull_type source{cooperative};
    cout << ", ";
    source();
    cout << "!\n";

    // ------------- above is just some test code of boost::coroutine

    cout << "\nExample 1 :\n";
    example1();

    cout << "\nExample 2 :\n";
    example2();

    return 0;
}
