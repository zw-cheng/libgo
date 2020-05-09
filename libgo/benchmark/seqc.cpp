#include<iostream>
#include<go.h>

using namespace std; 
using namespace std::chrono; 

int main()
{
    int res = 0;

    // coroutine<void>::pull_type source{cooperative};

    auto start = high_resolution_clock::now(); 
    for (int i=0;i<50000;i++){
        int x =i;
        res += x;
    }
    auto stop = high_resolution_clock::now(); 

    cout << res << endl;

    auto duration = duration_cast<nanoseconds>(stop - start); 
  
    cout << "sequential cpp:"  << duration.count() << " nanoseconds" << endl; 

    return 0;
}
