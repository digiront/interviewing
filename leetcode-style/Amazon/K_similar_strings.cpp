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

// Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions
// of two letters in A exactly K times so that the resulting string equals B.
// Given two anagrams A and B, return the smallest K for which A and B are K-similar.

//Note:
//
//1 <= A.length == B.length <= 20
//A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}

int kSimilarity(string A, string B) {
    if (A == B) { return 0; }

    queue<string> queue;
    unordered_set<string> visited;
    queue.push(A);
    visited.insert(A);

    int result = 0;
    while (!queue.empty()) {
        result++;
        int sz = queue.size();
        while (sz--) {
            string str = queue.front();
            queue.pop();
            int i = 0;
            while (str[i] == B[i]) i++;
            for (int j = i + 1; j < A.length(); j++) {
                if (str[j] != B[j] && str[j] == B[i]) {
                    swap(str[i], str[j]);
                    if (str == B) { return result; }
                    if (visited.insert(str).second) {
                        queue.push(str);
                    }
                    swap(str[i], str[j]);
                }
            }
        }
    }
    return result;
}

int main(int argc, char **argv) {
    return 0;
}

