#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    //Time: O(M*N) and space: O(N)
    int shortestWay1(string source, string target) {
        const int N = source.size();
        const int M = target.size();
        unordered_set<char> s(source.begin(), source.end());

        int res = 1;
        int i = 0;
        int srcPtr = 0;
        while (i < M) {
            char c = target[i];
            if (s.count(c) == 0) return -1;

            while (srcPtr < N && source[srcPtr] != c) {
                srcPtr++;
            }

            if (srcPtr == N) {
                srcPtr = 0;
                res++;
            }
            else {
                i++;
                srcPtr++;
            }
        }
        return res;
    }

    // Time: O(M*N) and space: O(1)
    int shortestWay2(string source, string target) {
        const int N = source.size();
        const int M = target.size();

        int res = 0;
        for (int j = 0; j < M;) {
            int tmp = j;
            for (int i = 0; i < N; ++i) {
                if (j < M && source[i] == target[j]) {
                    j++;
                }
            }
            if (j == tmp) return -1;
            res++;
        }
        return res;
    }

    // Time: O(N * logM + M) and space: O(1)
    int shortestWay3(string source, string target) {
        // Store all idxs and do a binary search
        vector<vector<int>> charIdx(26, vector<int>());
        for (int i = 0; i < source.size(); ++i) {
            charIdx[source[i] - 'a'].push_back(i);
        }

        int res = 1;
        int i = 0;
        int j = -1;
        while (i < target.size()) {
            const auto& idxs = charIdx[target[i] - 'a'];
            if (idxs.empty()) return -1;
            auto it = upper_bound(idxs.begin(), idxs.end(), j);
            if (it == end(idxs)) {
                res++;
                j = -1;
            }
            else {
                j = *it;
                i++;
            }
        }
        return res;
    }
};