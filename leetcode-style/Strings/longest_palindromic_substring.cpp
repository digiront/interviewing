#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <limits>
#include <algorithm>

using namespace std;

//Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
//
//Example 1:
//
//Input: "babad"
//Output: "bab"
//Note: "aba" is also a valid answer.
//Example 2:
//
//Input: "cbbd"
//Output: "bb"

class Solution {
    int expandAround(const string& s, int i, int j) {
        int len = 0;
        while (i >= 0 && j < s.size()) {
            if (s[i] == s[j]) {
                len = j - i + 1;
                i--;
                j++;
            }
            else {
                break;
            }
        }
        return len;
    }

public:
    string longestPalindrome(string s) {
        int maxLen = 0;
        int start = 0;
        for (int i = 0; i < s.size(); ++i) {
            int l1 = expandAround(s, i, i);
            int l2 = expandAround(s, i, i + 1);
            int len = max(l1 , l2);
            if (len > maxLen) {
                maxLen = len;
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, maxLen);
    }
};

int main(int argc, char **argv) {
    Solution s;
    assert(s.longestPalindrome("babad") == "bab");
    assert(s.longestPalindrome("cbbd") == "bb");
    return 0;
}