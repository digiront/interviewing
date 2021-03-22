//116. Populating Next Right Pointers in Each Node
//You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:
//
//struct Node {
//    int val;
//    Node *left;
//    Node *right;
//    Node *next;
//}
//        Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to nullptr.
//
//Initially, all next pointers are set to nullptr.
//
//
//
//Follow up:
//
//You may only use constant extra space.
//Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.

#include <queue>

using namespace std;

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
            : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node *connectIterative(Node *root) {
        if (!root) { return root; }

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            for (int n = 0; n < sz; ++n) {
                Node *cur = q.front();
                q.pop();

                if (n < sz - 1) {
                    cur->next = q.front();
                }

                if (cur->left) { q.push(cur->left); }
                if (cur->right) { q.push(cur->right); }
            }
        }
        return root;
    }

    // Alternative solution
    // For each node, create two links, one for each child
    void helper(Node *root) {
        if (!root) { return; }

        if (root->left) {
            root->left->next = root->right;
        }
        if (root->right && root->next) {
            root->right->next = root->next->left;
        }

        helper(root->left);
        helper(root->right);
    }

    Node *connectRecursively(Node *root) {
        helper(root);
        return root;
    }
};