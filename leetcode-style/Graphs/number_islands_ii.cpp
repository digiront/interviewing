#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

// 694. https://leetcode.com/problems/number-of-distinct-islands/

//Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land)
// connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are
// surrounded by water.
//
//Count the number of distinct islands. An island is considered to be the same as another if and
// only if one island can be translated (and not rotated or reflected) to equal the other.
//
//Example 1:
//11000
//11000
//00011
//00011
//Given the above grid map, return 1.
//Example 2:
//11011
//10000
//00001
//11011
//Given the above grid map, return 3.
//
//Notice that:
//11
//1
//and
//1
//11
//are considered different island shapes, because we do not consider reflection / rotation.
//Note: The length of each dimension in the given grid does not exceed 50.

class Solution {
    const vector<vector<int>> Dirs = {{0, -1}, {0, 1}, {1, 0}, {-1, 0} };
    const vector<char> DirKey = {'l', 'r', 'd', 'u'};

    void dfs(vector<vector<int>>& grid, int i, int j, string& path) {
        const int N = grid.size();
        const int M = grid[0].size();

        if (i < 0 || i >= N || j < 0 || j >= M || grid[i][j] == 0) {
            path += 'f';
            return;
        }

        grid[i][j] = 0;
        for (int d = 0; d < Dirs.size(); ++d) {
            path += DirKey[d];

            int i2 = i + Dirs[d][0];
            int j2 = j + Dirs[d][1];
            dfs(grid, i2, j2, path);
        }
    }

public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;

        const int N = grid.size();
        const int M = grid[0].size();

        unordered_set<string> paths;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (grid[i][j] == 1) {
                    string curPath = "s";
                    dfs(grid, i, j, curPath);
                    paths.insert(curPath);
                }
            }
        }
        return paths.size();
    }
};

int main() {
    return 0;
}