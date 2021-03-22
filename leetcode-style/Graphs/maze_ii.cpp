#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

// 505. The Maze II
//There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by
// rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball
// stops, it could choose the next direction.
//
// Given the ball's start position, the destination and the maze, find the shortest distance for
// the  ball to stop at the destination. The distance is defined by the number of empty spaces
// traveled by the ball from the start position (excluded) to the destination (included).  If the
// ball cannot stop at the destination, return -1.
//
//The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space.
// You may assume that the borders of the maze are all walls.
// The start and destination coordinates are represented by row and column indexes.

class Solution {
    //Runtime: O(n*m*log(m*n)) - Worse case all elements in the grid are traversed and for each cell
    // visit the priority_queue operation cost is O(log(m * n)), where m*n is the pq size.
    //
    //Space: O(m*n) - The priority_queue can grow up to m*n elements.

    const vector <vector<int>> Dirs = {{0,  -1},
                                       {0,  1},
                                       {1,  0},
                                       {-1, 0}};

    bool isValid(int x, int y, const vector <vector<int>> &maze) {
        return x >= 0 && x < maze.size() &&
               y >= 0 && y < maze[0].size() &&
               maze[x][y] <= 0;
    }

    // each element has x, y, and the total distance
    using P = vector<int>;

    struct Comparator {
        bool operator()(const P &a, const P &b) {
            return a[2] > b[2]; // need a min heap based on distance
        }
    };

public:
    int shortestDistance(vector <vector<int>> &maze, vector<int> &start, vector<int> &dest) {
        if (maze.empty()) { return false; }

        priority_queue <P, vector<P>, Comparator> q;
        q.push({start[0], start[1], 0});

        while (!q.empty()) {
            auto p = q.top();
            q.pop();

            if (p[0] == dest[0] && p[1] == dest[1]) {
                return p[2];
            }

            if (maze[p[0]][p[1]] == -1) { continue; }
            // maze is modifiable and since we will never use this position again, we mark it as visited (-1)
            maze[p[0]][p[1]] = -1;


            for (const auto &d : Dirs) {
                int steps = 0;
                int x = p[0];
                int y = p[1];
                while (isValid(x + d[0], y + d[1], maze)) {
                    x += d[0];
                    y += d[1];
                    steps++;
                }

                if (maze[x][y] == 0) {
                    q.push({x, y, p[2] + steps});
                }
            }
        }

        return -1;
    }
};

struct TestCase {
    string id;
    int numCourses;
    vector<vector<int>> prerequisites;
};

int main() {
//    vector <TestCase> cases;
//    cases.push_back({"basic", {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2});
//    for (const auto &c : cases) runTestCase(c);
    return 0;
}