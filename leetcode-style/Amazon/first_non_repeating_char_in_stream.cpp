#include <vector>
#include <list>
#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

// Write a program to find first non-repeating character from a stream of characters

struct Node {
    char value;
    Node *next;
    Node *prev;

    Node(char c) : value(c), next(nullptr), prev(nullptr) {}
};

class DLL {
    Node* head;
    Node* tail;

public:
    DLL() : head(nullptr), tail(nullptr) {}

    Node *push_back(char c) {
        Node *newNode = new Node(c);

        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        return newNode;
    }

    void remove(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node == head) {
            head = head->next;
        }
        if (node == tail) {
            tail = tail->prev;
        }

        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }

        delete node;
    }

    bool empty() {
        return head == nullptr;
    }

    Node *front() {
        return head;
    }
};


class Solution {
    DLL nonRepeatedList;
    unordered_map<char, Node *> ptrToNode;
    vector<int> seen;

public:
    Solution()
    : nonRepeatedList()
    , ptrToNode()
    , seen(256, 0)
    {
    }
    char firstNonRepeated() {
        if (nonRepeatedList.empty()) {
            return '!';
        }
        return nonRepeatedList.front()->value;
    }

    void insert(char c) {
        if (seen[c] > 1) {
            return;
        }
        // seen for the first time
        if (seen[c] == 0) {
            ptrToNode[c] = nonRepeatedList.push_back(c);
            seen[c] = 1;
            return;
        }

        // seen second time
        auto it = ptrToNode.find(c);
        nonRepeatedList.remove(it->second);
        ptrToNode.erase(it);
    }
};

int main() {
    Solution s;

    assert(s.firstNonRepeated() == '!');

    s.insert('a');
    assert(s.firstNonRepeated() == 'a');
    s.insert('b');
    assert(s.firstNonRepeated() == 'a');
    s.insert('a');
    assert(s.firstNonRepeated() == 'b');
    s.insert('b');
    assert(s.firstNonRepeated() == '!');

    s.insert('c');
    s.insert('d');
    s.insert('e');
    s.insert('c');
    assert(s.firstNonRepeated() == 'd');

    return 0;
}