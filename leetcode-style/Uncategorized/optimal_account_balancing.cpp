#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

// 465. Optimal Account Balancing
// https://leetcode.com/problems/optimal-account-balancing/
//
//A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for
// $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means
// person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively
// (0, 1, 2 are the person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].
//
//Given a list of transactions between a group of people, return the minimum number of transactions required to settle
// the debt.
//
//Note:
//A transaction will be given as a tuple (x, y, z). Note that x ≠ y and z > 0.
//Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.


class Solution {
public:
    static int minTransfers(vector<vector<int>> &transactions) {
        unordered_map<int, int> owes;
        for (const auto &v : transactions) {
            int lender = v[0];
            int borrower = v[1];
            int amount = v[2];
            owes[lender] -= amount;
            owes[borrower] += amount;
        }

        vector<int> balances;
        for (const auto&[person, owe_amount] : owes) {
            if (owe_amount != 0) {
                balances.push_back(owe_amount);
            }
        }

        return solve(0, balances);
    }

private:
    static int solve(int start, vector<int> &balances) {
        if (start == balances.size()) return 0;
        while (start < balances.size() && balances[start] == 0) start++;

        int res = INT_MAX;
        for (long i = start + 1; i < balances.size(); ++i) {
            if (balances[i] * balances[start] < 0) {
                balances[i] += balances[start];
                res = min(res, 1 + solve(start + 1, balances));
                balances[i] -= balances[start];
            }
        }
        return res == INT_MAX ? 0 : res;
    }
};

int main() {
    // person i needs to pay debts[i][j] person j
    vector<vector<int>> lending = {{0, 1, 10}, {2, 0, 5}};
    cout << Solution::minTransfers(lending) << endl;
    return 0;
}