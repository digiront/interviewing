#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <numeric>
#include <map>
#include <chrono>
#include <thread>

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
    chrono::seconds d_lastCalled;
    int d_tokensRemaining;
public:
    TokenGenerator(int period, int capacity)
    : d_period(period)
    , d_capacity(capacity)
    , d_lastCalled(now())
    , d_tokensRemaining(capacity) {
    };

    // returns the number of tokens currently in the generator
    int acquire(int n) {
        auto nowSecs = now();
        auto diffSecs = (nowSecs - d_lastCalled).count();
        if (diffSecs > d_period) {
            int numPeriods = diffSecs / d_period;
            cout << "numPeriods: " << numPeriods << endl;
            int sum = d_tokensRemaining + numPeriods;
            d_tokensRemaining = sum > d_capacity ? d_capacity : sum;
        }

        cout << "1) d_tokensRemaining:" << d_tokensRemaining << endl;
        if (d_tokensRemaining > n) {
            d_tokensRemaining -= n;
        }
        else {
            d_tokensRemaining = 0;
        }

        cout << "2) d_tokensRemaining:" << d_tokensRemaining << endl;
        d_lastCalled = nowSecs;
        return d_tokensRemaining;
    }
};

int main() {
    TokenGenerator tg(1, 100);
    cout << "Tokens remaining: \n" << tg.acquire(101) << endl;
    this_thread::sleep_for(std::chrono::seconds (3));
    cout << "Tokens remaining: \n" << tg.acquire(2) << endl;
    return 0;
}