#include <vector>
#include "channel.h"
#include "goroutine.h"

template <typename T>
void sum(vector<int> nums, chan<T> &ch){
    int res=0;
    for(auto n : nums)
        res += n;
    ch.send(res); // ch <- res
}

int main(){
    coroutine<void>::pull_type source{cooperative};
    cout << ", ";
    source();
    cout << "!\n";
    
    // ------------- above is just some test code of boost::coroutine
    
    // todo: go sum()
    
    auto ch = make<int>(2); // my_chan := make(chan int)
    
    vector<int> nums{1,2,3,4};
    
    // it should be called by adding go, but for now we call them sequencially
    sum(vector<int>(nums.begin(), nums.begin() + nums.size()/2), ch);
    sum(vector<int>(nums.begin() + nums.size()/2, nums.end()), ch);
    
    int res1 = ch.receive();
    int res2 = ch.receive();
    
    cout<< "sum" << res1 << " + sum" << res2 << " = result"<< res1+res2 <<endl;
    
    return 0;
}

