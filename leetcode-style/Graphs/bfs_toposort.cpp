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
private:
    typedef vector<vector<int>> MatrixGraph;

    static MatrixGraph buildGraph(int numCourses, const vector<pair<int, int>> &prerequisites) {
        MatrixGraph g(numCourses);
        for (const auto p : prerequisites) {
            g[p.second].push_back(p.first);
        }
        return g;
    }

    static vector<int> buildIncomingDegreeVec(MatrixGraph &g) {
        vector<int> degrees(g.size(), 0);
        for (const auto& nodes : g) {
            for (int v : nodes) {
                degrees[v]++;
            }
        }
        return degrees;
    }

public:
    static vector<int> findOrder(int numCourses, const vector<pair<int, int>> &prerequisites) {
        MatrixGraph g = buildGraph(numCourses, prerequisites);
        vector<int> degrees = buildIncomingDegreeVec(g);
        vector<int> out;
        for (int i = 0; i < numCourses; i++) {
            int j = 0;
            for (; j < numCourses; j++) {
                if (degrees[j] == 0) {
                    out.push_back(j);
                    break;
                }
            }

            // Cycle detection
            if (j == numCourses) {
                return {};
            }

            degrees[j]--;
            for (int neighbor : g[j]) {
                degrees[neighbor]--;
            }
        }
        return out;
    }
};


struct TestData {
    string id;
    int numCourses;
    vector<pair<int, int>> prerequisites;
    vector<int> expectedRes;
};

void RunTestCase(const TestData &c) {
    cout << "Running test: " << c.id << endl;
    Solution s;
    vector<int> actualRes = s.findOrder(c.numCourses, c.prerequisites);

    cout << "Result: \n";
    if (actualRes.empty()) {
        cout << "Cycle detected" << endl;
    }
    else {
        for (int i : actualRes) {
            cout << i << " ";
        }
        cout << endl;
    }
    // TODO accept multiple toposort results
    assert(actualRes == c.expectedRes);
}

int main() {
    vector<TestData> cases;
    cases.push_back({"basic", 2, {{1, 0}}, {0, 1}});
    cases.push_back({"four courses", 4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, {0, 1, 2, 3}});
    cases.push_back({"cycle", 4, {{1, 0}, {0, 1}, {3, 1}, {3, 2}}, {}});

    for (const auto &c : cases) RunTestCase(c);
    return 0;
}