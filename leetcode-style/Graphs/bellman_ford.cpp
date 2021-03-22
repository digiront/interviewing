#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>
#include <climits>

using namespace std;

// 743. https://leetcode.com/problems/network-delay-time/
//There are N network nodes, labelled 1 to N.
//
//Given times, a list of travel times as directed edges times[i] = (u, v, w),
// where u is the source node, v is the target node, and w is the time it takes for
// a signal to travel from source to target.
//
//Now, we send a signal from a certain node K.
// How long will it take for all nodes to receive the signal? If it is impossible, return -1.

//N will be in the range [1, 100].
//K will be in the range [1, N].
//The length of times will be in the range [1, 6000].
//All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
//

class Solution {
    bool IsReachable(int d) {
        return d != INT_MAX;
    }

    void PrintPath(const vector<int>& pred, int max_id, int source_id) {
        int v = max_id;
        while (v != source_id) {
            cout << v << ", ";
            v = pred[v];
        }
        cout << v << endl;
    }
public:
    int NetworkDelayTime(const vector<vector<int>> &times, int N, int source_id) {

        // * dist(i) represents the minimum distance from K to i
        // initialize all distances to MAX value as initial minimum distance from K to every point
        vector<int> dist(N + 1, INT_MAX); // for convenience, index 0 isn't used
        // demonstrate how to preserve the path
        vector<int> pred(N + 1, INT_MAX);

        // source_id has 0 distance from itself
        dist[source_id] = 0;

        // * Repeat edge relaxation N times
        for (int i = 0; i < N; i++) {
            for (vector<int> e : times) {
                int u = e[0], v = e[1], w = e[2];
                // if u can be reached from source_id and
                // new distance from u to v is smaller than previous saved distance
                if (IsReachable(dist[u]) && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w; // relaxation
                    pred[v] = u;
                }
            }
        }

        // * Apply relaxation again to check for negative-weight cycles
        for (int i = 0; i < N; i++) {
            for (vector<int> e : times) {
                int u = e[0], v = e[1], w = e[2];
                const int new_cost = dist[u] + w;
                if (IsReachable(dist[u]) && dist[u] + w < dist[v]) {
                    cout << "Graph contains a negative-weight cycle:\n U: " << u << ", V:" << v << ", previous cost: "
                         << dist[v] << ", new cost: " << new_cost << endl;
                    return -1;
                }
            }
        }

        // get the max of the minimum distances, if it is INT_MAX it means there is no path
        int maxDelay = 0;
        int maxIdx = 0;
        for (int i = 1; i <= N; i++) {
            if (maxDelay < dist[i]) {
                maxIdx = i;
                maxDelay = dist[i];
            }
        }

        PrintPath(pred, maxIdx, source_id);

        return maxDelay == INT_MAX ? -2 : maxDelay;
    }
};

struct TestData {
    string id;
    vector<vector<int>> times;
    int N;
    int K;
    int expectedRes = 2;
};

void RunTestCase(const TestData &c) {
    cout << "Running test: " << c.id << endl;
    Solution s;
    int actualRes = s.NetworkDelayTime(c.times, c.N, c.K);
    cout << "Result: " << actualRes << endl;
    assert(actualRes == c.expectedRes);
}

int main() {
    vector<TestData> cases;
    cases.push_back({"basic", {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2});
    cases.push_back({.id ="negative cycle", .times={{2, 1, 1}, {1, 2, -2}}, .N=2, .K=1,.expectedRes= -1});
    for (const auto &c : cases) RunTestCase(c);
    return 0;
}