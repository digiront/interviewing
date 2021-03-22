#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <limits>
#include <cassert>

using namespace std;

//Given 2 lists a and b. Each element is a pair of integers where the first integer represents the
//unique id and the second integer represents a value. Your task is to find an element from a and an
//element form b such that the sum of their values is less or equal to target and as close to target
//as possible. Return a list of ids of selected elements. If no pair is possible, return an empty list.

vector<vector<int>> getPairs(vector<vector<int>> &A, vector<vector<int>> &B, int target) {
    auto comp = [](const vector<int> &lhs, const vector<int> &rhs) {
        return lhs[1] < rhs[1];
    };
    sort(A.begin(), A.end(), comp);
    sort(B.begin(), B.end(), comp);

    vector<vector<int>> results;
    int current_max = numeric_limits<int>::min();

    int left = 0;
    int right = B.size() - 1;
    while (left < A.size() && right >= 0) {
        int sum = A[left][1] + B[right][1];
        if (sum > target) { // skip lhs of B
            --right;
        }
        else { // we have A candidate solution
            if (sum >= current_max) {
                if (sum > current_max) { // we have found A better solution, clear previous one
                    current_max = sum;
                    results.clear();
                }

                results.push_back({A[left][0], B[right][0]});

                // index right only moves when sum > target. if sum == current_max and B[right] == B[right-1]
                // without the following 4 lines we would be incrementing left, losing C-1 solutions
                // where C is the number of consecutive repeated values equal to B[right].
                int prev = right - 1;
                while (prev >= 0 && B[prev][1] == B[right][1]) {
                    results.push_back({A[left][0], B[prev][0]});
                    prev--;
                }
                // fast forward to last position
                right = prev + 1;
            }
            ++left;
        }
    }
    return results;
}

int main() {
    // Example 1
    vector<vector<int>> a = {{1, 2},
                             {2, 4},
                             {3, 6}};
    vector<vector<int>> b = {{1, 2}};
    vector<vector<int>> expectedRes = {{2, 1}};
    assert(getPairs(a, b, 7) == expectedRes);

    // Example 2
    a = {{1, 3},
         {2, 5},
         {3, 7},
         {4, 10}};
    b = {{1, 2},
         {2, 3},
         {3, 4},
         {4, 5}};
    expectedRes = {{2, 4},
                     {3, 2}};
    assert(getPairs(a, b, 10) == expectedRes);

    // Example 3
    a = {{1, 8},
         {2, 7},
         {3, 14}};
    b = {{1, 5},
         {2, 10},
         {3, 14}};
    expectedRes = {{3, 1}};
    assert(getPairs(a, b, 20) == expectedRes);

    // Example 4
    a = {{1, 8},
         {2, 15},
         {3, 9}};
    b = {{1, 8},
         {2, 11},
         {3, 12}};
    expectedRes = {{1, 3},
                     {3, 2}};
    assert(getPairs(a, b, 20) == expectedRes);

    // Example 5
    a = {{1, 8},
         {2, 15},
         {3, 9}};
    b = {{1, 8},
         {2, 11},
         {3, 11},
         {4, 11},
         {5, 11},
         {6, 12}};
    expectedRes = {{1, 6},
                   {3, 5},
                   {3, 4},
                   {3, 3},
                   {3, 2}};
    assert(getPairs(a, b, 20) == expectedRes);
}