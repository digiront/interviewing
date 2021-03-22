#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <limits>
#include <algorithm>

using namespace std;

//Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.
//
//Example 1:
//
//Input: "aacecaaa"
//Output: "aaacecaaa"
//Example 2:
//
//Input: "abcd"
//Output: "dcbabcd"

class Solution {
    const static int M = numeric_limits<int>::max();
    const static int Base = 26;

    static int code(char c) {
        return c - 'a';
    }

public:
    // Runtime: O(N^2), Space: O(N)
    static string shortestPalindromeSlow(string s) {
        int n = s.size();
        int i = 0;
        for (int j = n - 1; j >= 0; j--) {
            if (s[i] == s[j]) {
                i++;
            }
        }
        if (i == n) {
            return s;
        }
        string remain_rev = s.substr(i, n);
        reverse(remain_rev.begin(), remain_rev.end());
        return remain_rev + shortestPalindrome(s.substr(0, i)) + s.substr(i);
    }

    // Runtime: O(N), Space: O(N)
    static string shortestPalindrome(string s) {
        const int N = s.size();
        if (N == 0) { return s; }

        // For s = "abcd"
        // Normal hash:  code('a') * 26^3 + code('b') * 26^2  + code('c') * 26^1 + code('d') * 26^0
        // Reverse hash: code('a') * 26^0 + code('b') * 26^1  + code('c') * 26^2 + code('d') * 26^3

        long h = 0;
        long rh = 0;
        long P = 1;
        int pos = -1;
        for (int i = 0; i < N; ++i) {
            h = (h * Base + code(s[i])) % M;
            rh = (rh + code(s[i]) * P) % M;
            if (h == rh) {
                // Enhance the condition to:
                // if (h == rh && rev.substr(i + 1) == s.substr(0, j)) {
                // if you are asked for false positives
                pos = i;
            }

            P = (P * Base) % M;
        }

        string prefix = s.substr(pos + 1);
        reverse(prefix.begin(), prefix.end());
        return prefix + s;
    }
};

int main(int argc, char **argv) {
    Solution s;
    assert(s.shortestPalindrome("aacecaaa") == "aaacecaaa");
    assert(s.shortestPalindrome("abcd") == "dcbabcd");
    return 0;
}