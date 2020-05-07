#include <boost/coroutine/all.hpp>
#include <functional>
#include <iostream>

using namespace boost::coroutines;
using namespace std::chrono; 

void cooperative(coroutine<int>::push_type &sink, int i)
{
    for(int i= 0; i<50000;i++){
        sink(i);
    }
}

int main()
{
    int res = 0;

    auto start = high_resolution_clock::now(); 

    using std::placeholders::_1;
    coroutine<int>::pull_type source{std::bind(cooperative, _1, 0)};
    for(int i= 0; i<50000;i++){
        res += source.get();
        source();
    }

    auto stop = high_resolution_clock::now(); 

    std::cout << res << std::endl;

    auto duration = duration_cast<nanoseconds>(stop - start); 
  
    std::cout << "coroutine cpp:"  << duration.count() << " nanoseconds" << std::endl; 

    return 0;
}
