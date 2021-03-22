#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>
#include <limits>

using namespace std;

// 787. Cheapest Flights Within K Stops
// There are n cities connected by m flights.
// Each flight starts from city u and arrives at v with a price w.
// Now given all the cities and flights, together with starting city src and the destination dst,
// your task is to find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.

//The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
//The size of flights will be in range [0, n * (n - 1) / 2].
//The format of each flight will be (src, dst, price).
//The price of each flight will be in the range [1, 10000].
//k is in the range of [0, n - 1].
//There will not be any duplicated flights or self cycles.

class Solution {

public:
    // Since we are now considering the flights with up to K stops, it is natural to use
    // Bellman-Ford algorithm and relax up to K + 1 times.
    int findCheapestPrice(int n, const vector<vector<int>> &flights, int start, int end, int K) {
        const int INF = 1e9;
        // cities between [0, n-1], so n will do
        vector<vector<int>> dp(K + 2, vector<int>(n, INF));

        dp[0][start] = 0;
        for (int i = 1; i <= K + 1; ++i) {
            dp[i][start] = 0;
            for (const auto &x : flights) {
                const int source = x[0];
                const int dest = x[1];
                const int cost = x[2];
                dp[i][dest] = min(dp[i][dest], dp[i - 1][source] + cost);
            }
        }
        return dp[K + 1][end] >= INF ? -1 : dp[K + 1][end];

    }
};

struct TestData {
    string id;
    int N;
    vector<vector<int>> flights;
    int src;
    int dst;
    int K;
    int expectedRes;
};

void RunTestCase(const TestData &c) {
    cout << "Running test: " << c.id << endl;
    Solution s;
    int actualRes = s.findCheapestPrice(c.N, c.flights, c.src, c.dst, c.K);
    cout << "Result: " << actualRes << endl;
    assert(actualRes == c.expectedRes);
}

int main() {
    vector<TestData> cases;
    cases.push_back({"basic", 3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 1, 200});
    cases.push_back({"basic2", 3, {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}}, 0, 2, 0, 500});

    for (const auto &c : cases) RunTestCase(c);
    return 0;
}