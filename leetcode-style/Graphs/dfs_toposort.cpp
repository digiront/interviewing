#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>
#include <limits>

using namespace std;

//210. Course Schedule II

//There are a total of n courses you have to take, labeled from 0 to n-1.
//
//Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
//
//Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
//
//There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
//
//Note:
//The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
//You may assume that there are no duplicate edges in the input prerequisites.

class Solution {
public:
    using Graph = unordered_map<int, unordered_set<int>>;

    vector<int> findOrder(int numCourses, const vector<vector<int>> &prerequisites) {
        vector<int> result;
        for (int i = 0; i < numCourses; ++i) {
            graph_[i] = {};
        }

        for (const auto &p : prerequisites) {
            graph_[p[1]].insert(p[0]);
        }

        unordered_map<int, int> node_state;
        stack<int> topo_sorted_nodes;
        for (const auto&[n, edges] : graph_) {
            if (dfs(n, node_state, topo_sorted_nodes)) {
                return {}; // found cycle
            }
        }

        // Add courses that are completely independent
        for (int i = 0; i < numCourses; ++i) {
            if (node_state[i] == 0) {
                result.push_back(i);
            }
        }

        while (!topo_sorted_nodes.empty()) {
            result.push_back(topo_sorted_nodes.top());
            topo_sorted_nodes.pop();
        }
        return result;
    }

    const Graph &graph() const { return graph_; }

private:
    Graph graph_;

    bool dfs(int n, unordered_map<int, int> &node_state, stack<int> &topo) {
        // already visited
        if (node_state[n] == 2) return false;
        // cycle detection
        if (node_state[n] == 1) return true;
        // currently visit-ing
        node_state[n] = 1;
        for (const auto &edge_id : graph_[n]) {
            bool found_cycle = dfs(edge_id, node_state, topo);
            if (found_cycle) return true;
        }

        // found topological order for n
        topo.push(n);
        // visit-ed
        node_state[n] = 2;
        return false;
    }

};

bool ValidateToposortResult(const Solution::Graph &graph, const vector<int> &result) {
    unordered_map<int, int> result_map;
    for (int i = 0; i < result.size(); ++i) {
        result_map[result[i]] = i;
    }
    for (const auto&[node_id, edge_set] : graph) {
        for (int dependency_id : edge_set) {
            if (result_map[dependency_id] < result_map[node_id]) {
                cout << node_id << " appears before dependency " << dependency_id << endl;
                return false;
            }
        }
    }
    return true;
}

struct TestData {
    string id;
    int numCourses;
    vector<vector<int>> prerequisites;
    bool expect_cycle = false;
};

void RunTestCase(const TestData &c) {
    cout << "Running test: " << c.id << endl;
    Solution s;
    vector<int> actualRes = s.findOrder(c.numCourses, c.prerequisites);

    if (c.expect_cycle) {
        assert(actualRes.empty());
        return;
    }

    cout << "Result: \n";
    for (int i : actualRes) {
        cout << i << " ";
    }
    cout << endl;

    // TODO accept multiple toposort results
    assert(ValidateToposortResult(s.graph(), actualRes));
}

int main() {
    vector<TestData> cases;
    cases.push_back({"basic", 2, {{1, 0}}});
    cases.push_back({"four courses", 4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}});
    cases.push_back({"cycle", 4, {{1, 0}, {0, 1}, {3, 1}, {3, 2}}, true});

    for (const auto &c : cases) RunTestCase(c);
    return 0;
}