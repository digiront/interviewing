#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <numeric>
#include <map>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

//TokenGenerator(int period, int capacity)
//Period: time needed to generate one token
//Capacity: max number of tokens the generator can hold

//Implement the function to get tokens from the generator:
//Int acquire(int n) : acquires n tokens, this should return:
//min(num tokens currently in the generator, n)

//Hint: So you remember the start time and the last time acquire() is called
//      to keep track of how many tokens the generator is currently holding

chrono::seconds now() {
    return chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch());
}

class TokenGenerator {

    int d_period;
    int d_capacity;
    int d_tokensRemaining;
    chrono::seconds d_lastCalled;
    thread d_generatorThread;
    atomic_bool d_stopped;
    mutex d_mutex;

    void generatorFunc() {
        while (!d_stopped) {
            this_thread::sleep_for(std::chrono::milliseconds (2000));
            auto nowSecs = now();
            auto diffSecs = (nowSecs - d_lastCalled).count();
            if (diffSecs >= d_period) {
                int numPeriods = diffSecs / d_period;
                
                lock_guard<mutex> lockGuard(d_mutex);
                int sum = d_tokensRemaining + numPeriods;
                d_tokensRemaining = sum > d_capacity ? d_capacity : sum;
                d_lastCalled = nowSecs;
            }
        }
    }

public:
    TokenGenerator(int period, int capacity)
    : d_period(period)
    , d_capacity(capacity)
    , d_tokensRemaining(capacity)
    , d_lastCalled(now())
    , d_stopped(false)
    , d_mutex()
    {
        d_generatorThread = thread(&TokenGenerator::generatorFunc, this);
    };

    ~TokenGenerator() {
        stop();
    }

    // returns the number of tokens currently in the generator
    pair<int, int> acquire(int n) {
        int taken = 0;
        lock_guard<mutex> lockGuard(d_mutex);
        if (d_tokensRemaining > n) {
            taken = n;
            d_tokensRemaining -= n;
        }
        else {
            taken = d_tokensRemaining;
            d_tokensRemaining = 0;
        }
        return {taken, d_tokensRemaining};
    }

    void stop() {
        d_stopped = true;
        if (d_generatorThread.joinable()) { // should be here
            d_generatorThread.join();
        }
    }

};

int main() {
    TokenGenerator tg(1, 100);
    vector<pair<int, int>> a = {{1, 0}, {3, 0}, {100, 3}, {1, 1}};
    for (const auto& p : a) {
        auto[taken, remaining] = tg.acquire(p.first);
        cout << "taken: " << taken << ", remaining: " << remaining << endl;
        this_thread::sleep_for(std::chrono::seconds(p.second));
    }
    return 0;
}