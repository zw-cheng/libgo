#include <boost/coroutine/all.hpp>
#include <functional>
#include <iostream>
#include "../goroutine.h"
#include "../channel.h"

using namespace boost::coroutines;
using namespace std::chrono; 

chan<int> ch = make<int>();

int main()
{
    int res = 0;


    auto start = high_resolution_clock::now(); 

    go ([]() mutable {
        for(int i =0;i<50000;i++)
            ch <<i;
    });

    int recv;
    int sum = 0;
    for(int i =0;i<50000;i++){
        ch >> recv;
        sum += recv;
    }

    auto stop = high_resolution_clock::now(); 

    std::cout << res << std::endl;

    auto duration = duration_cast<nanoseconds>(stop - start); 
  
    std::cout << "coroutine cpp:"  << duration.count() << " nanoseconds" << std::endl; 

    return 0;
}
