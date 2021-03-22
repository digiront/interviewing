#include <iostream>
#include <unordered_map>
#include <memory>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

// Git version control system uses SHA hash to represent each commit.
// Create a service that keeps track of commit hashes and returns shortest prefix that uniquely identifies all commits.

// For example, after inserting 2 commits:
// a3b512eeb8
// b302425f42

// The service should return 2 short hashes with length 1:
// a, b

// After inserting 2 more commits:
// a3b5b71bb4
// a3b5b79288
// The service should return 4 short hashes with length 7:
// a3b512e
// b302425
// a3b5b71
// a3b5b79

struct Node {
    unordered_map<char, unique_ptr<Node>> nodes;
    int freq = 1;
};

class Solution {


    Node root;
    int shaSize = numeric_limits<int>::min();

    void traverse(vector<string> *out, Node *n, string *partialSha) {
        if (partialSha->size() == shaSize) {
            out->push_back(*partialSha);
            return;
        }

        for (const auto& it : n->nodes) {
            partialSha->push_back(it.first);
            traverse(out, it.second.get(), partialSha);
            partialSha->pop_back();
        }
    }

public:
    void insert(const string& sha) {
        Node *n = &root;
        int len = 1;
        for (char c : sha) {
            auto it = n->nodes.find(c);
            if (it == n->nodes.end()) { // node doesn't exist yet
                n->nodes[c] = make_unique<Node>();
                n = n->nodes[c].get();

                shaSize = max(shaSize, len);
            }
            else {
                len++;
                n = it->second.get();
                n->freq++;
            }
        }
    }

    vector<string> find() {
        vector<string> shas;
        string partialSha;
        cout << "shaSize: " << shaSize << endl;
        traverse(&shas, &root, &partialSha);
        sort(shas.begin(), shas.end());
        return shas;
    }

};

void printResults(const vector<string>& results) {
    cout << "Found: " << endl;
    for (const string& sha : results) {
        cout << sha << endl;
    }
    cout << "Done.\n" << endl;
}

int main() {
    Solution s;
    s.insert("a3b512eeb8");
    s.insert("b312425f42");
    printResults(s.find());

    s.insert("a325b71bb4");
    s.insert("a335b79288");
    printResults(s.find());

    return 0;
}
