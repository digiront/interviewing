#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>

using namespace std;

void foo(int secs)
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(secs));
}
 
 
int main()
{
    vector<thread> v(10);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = thread([] { return foo(1); });
    }
 
    for (int i = 0; i < v.size(); ++i) {
        v[i].join();
    }
 
    std::cout << "done!\n";
}
