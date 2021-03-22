#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
    static int traverse(const string &word, const unordered_set<string> &dictionary, unordered_map<string, int> &memo) {
        if (memo.count(word)) return memo[word];

        int count = 0;
        for (int i = 0; i < word.size(); i++) {
            // remove a char at position i
            string tmp = word;
            tmp.erase(i, 1);

            // traverse if new word is in the dictionary
            if (dictionary.count(tmp)) {
                count = max(count, traverse(tmp, dictionary, memo));
            }
        }

        const int chain_length = 1 + count;
        return (memo[word] = chain_length);
    }

public:
    static int LongestStringChain(vector<string> &words) {
        sort(words.begin(), words.end());
        unordered_set<string> dictionary;
        for (const auto &w : words) {
            dictionary.insert(w);
        }

        int ans = 0;
        // word to chain length
        unordered_map<string, int> memo;
        for (const string &w : words) {
            ans = max(ans, traverse(w, dictionary, memo));
        }
        return ans;
    }
};

int main() {
    vector<string> words{"a", "b", "ba", "bca", "bda", "bdca"};
    cout << Solution::LongestStringChain(words) << endl;
    // Explanation: One of the longest word chain is "a","ba","bda","bdca".
    return 0;
}
