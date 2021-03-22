#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

//Given a blacklist B containing unique integers from [0, N), write a function to return a uniform random integer from [0, N) which is NOT in B.
//
//Optimize it such that it minimizes the call to system’s Math.random().
//
//Note:
//
//1 <= N <= 1000000000
//0 <= B.length < min(100000, N)
//[0, N) does NOT include N. See interval notation.

class Solution {

    int nextRandom(int max) {
        // obtain a random number from hardware
        static random_device rd;
        // seed the generator
        static default_random_engine eng(rd());
        // generate a number between 0 and N
        uniform_int_distribution<> dist(0, max - 1);
        return dist(eng);
    }

    // N: [0, N)
    // B: blacklist
    // B1: < N
    // B2: >= N
    // M: N - B1
    int M;
    unordered_map<int, int> map;

public:

    Solution(int N, const vector<int> &blacklist) : map()
    {
        cout << "N: " << N << endl;
        for (int b : blacklist) {// O(B)
            if (b < N) map[b] = -1;
        }
        cout << "map.size(): " << map.size() << endl;

        M = N - map.size();
        cout << "M: " << M << endl;
        for (int b : blacklist) { // O(B)
            if (b < M) { // re-mapping
                while (map.count(N - 1) == 1) {
                    N--;
                }
                map[b] = N - 1;
                N--;
            }
        }

        for (const auto& [k,v] : map) {
            cout << "Mapped " << k << " to " << v << endl;
        }

    }

    int pick() {
        int p = nextRandom(M);
        if (map.count(p) == 1) {
            return map[p];
        }
        return p;
    }
};

int main() {
    vector<int> blacklist = {2, 3};
    Solution s(6, blacklist);


    // Test
    unordered_set<int> blacklistSet(blacklist.begin(), blacklist.end());
    for (int i = 0; i < 40; ++i) {
        int v = s.pick();
        assert(blacklistSet.count(v) == 0);
    }
    return 0;
}

