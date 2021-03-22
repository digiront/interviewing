#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

// 743. https://leetcode.com/problems/network-delay-time/
class Solution {
    using P = pair<int, int>;
    struct Comparator {
        bool operator()(const P& a, const P& b) {
            return a.second > b.second; // need a minheap
        }
    };

public:
    int NetworkDelayTime(const vector<vector<int>>& times, int N, int K) {
        // build a graph
        unordered_map<int, unordered_map<int, int>> graph = {};
        for (int i = 1; i <= N; ++i) graph[i] = {};
        for (const auto& e : times) {
            const int u = e[0];
            const int v = e[1];
            graph[u][v] = e[2];
        }

        // BFS
        unordered_set<int> visited;

        priority_queue<P, vector<P>, Comparator> q;
        q.push({K, 0});

        int ans = 0;
        while(!q.empty()) {
            auto [u, w] = q.top();
            q.pop();
            if (visited.count(u) == 1) continue;

            ans = w;
            visited.insert(u);

            for (const auto& it : graph[u]) {
                q.push({it.first, w + it.second});
            }
        }
        return visited.size() == N ? ans : -1;
    }
};

struct TestData {
    string id;
    vector<vector<int>> times;
    int N;
    int K;
    int expectedRes = 2;
};

void RunTestCase(const TestData& c) {
    cout << "Running test: " << c.id << endl;
    Solution s;
    int actualRes = s.NetworkDelayTime(c.times, c.N, c.K);
    cout << "Result: " << actualRes << endl;
    assert(actualRes == c.expectedRes);
}
int main() {
    vector<TestData> cases;
    cases.push_back({"basic", {{2,1,1},{2,3,1},{3,4,1}}, 4, 2});
    for (const auto& c : cases) RunTestCase(c);
    return 0;
}