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

//Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
//
//Integers in each row are sorted in ascending from left to right.
//Integers in each column are sorted in ascending from top to bottom.
//Example:
//
//Consider the following matrix:
//
//[
//[1,   4,  7, 11, 15],
//[2,   5,  8, 12, 19],
//[3,   6,  9, 16, 22],
//[10, 13, 14, 17, 24],
//[18, 21, 23, 26, 30]
//]
//Given target = 5, return true.
//
//Given target = 20, return false.

// Runtime: O(lg(N!)) or O(NlogN), Space: O(1)

class Solution1 {

    static bool binarySearch(const vector<vector<int>> &matrix, int target, int start,
                             bool vertical) {
        int lo = start;
        int hi = vertical ? matrix[0].size() - 1 : matrix.size() - 1;

        while (lo < hi) {
            int mid = (lo + hi) / 2;
            int v = vertical ? matrix[start][mid] : matrix[mid][start];
            if (v < target) {
                lo = mid + 1;
            }
            else if (v > target) {
                hi = mid - 1;
            }
            else {
                return true;
            }
        }

        return false;
    }

public:
    static bool searchMatrix(vector<vector<int>> &matrix, int target) {
        // an empty matrix obviously does not contain `target`
        if (matrix.empty()) {
            return false;
        }

        // iterate over matrix diagonals
        int shorterDim = min(matrix.size(), matrix[0].size());
        for (int i = 0; i < shorterDim; i++) {
            bool verticalFound = binarySearch(matrix, target, i, true);
            bool horizontalFound = binarySearch(matrix, target, i, false);
            if (verticalFound || horizontalFound) {
                return true;
            }
        }

        return false;
    }
};

// Runtime: O(M+N), Space: O(1)
class Solution2 {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        const int N = matrix.size();
        if (N == 0) { return false; }
        const int M = matrix[0].size();

        int row = N - 1;
        int col = 0;

        while (row >= 0 && col < M) {
            if (matrix[row][col] > target) {
                row--;
            }
            else if (matrix[row][col] < target) {
                col++;
            }
            else {
                return true;
            }
        }
        return false;
    }
};

int main(int argc, char **argv) {
    return 0;
}