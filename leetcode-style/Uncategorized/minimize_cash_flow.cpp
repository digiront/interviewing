// Given a number of friends who have to give or take some amount of money from one another. Design an algorithm by
// which the total cash flow among all the friends is minimized.

// Assume the input is [-8,-4,5,7]. On each step, look for the number with the least absolute value (-4).
// Without loss of generality, assume this number is negative. Then ‘zero’ this number by cancelling it with the
// smallest number on the other side — so transfer $4 from 5 to 4, giving us [-8,1,7].
// Repeat this until all numbers are zero.

// How bad is this algorithm? Let’s say there are M negative numbers and N positive numbers. Then this algorithm
// requires at most M+N-1 transfers, since each step zeroes at least one number, and the last step zeroes
// two numbers.

// The optimal solution takes at least max(M,N) transfers. This proves that my greedy algorithm never takes
// more than 2 times the optimal number of transfers. Not too bad, but not great either.

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace {
    void RecursionHelper(vector<int> &balances, vector<vector<int>>& transactions) {
        int max_creditor = 0;
        int max_credit_amount = 0;
        for (int i = 1; i < balances.size(); ++i) {
            if (balances[i] > max_credit_amount) {
                max_credit_amount = balances[i];
                max_creditor = i;
            }
        }

        int max_debtor = 0;
        int max_debt_amount = 0;
        for (int i = 1; i < balances.size(); ++i) {
            // Keep in mind we compare against numbers <= 0
            if (balances[i] < max_debt_amount) {
                max_debt_amount = balances[i];
                max_debtor = i;
            }
        }

        // When all balances are 0 we can stop the recursion
        if (max_credit_amount == 0 && max_debt_amount == 0) return;

        int abs_min_amount = min(abs(max_debt_amount), abs(max_credit_amount));
        if (abs_min_amount == 0) return;
        balances[max_creditor] -= abs_min_amount; // decrease balance
        balances[max_debtor] += abs_min_amount; // reduce debt
        transactions.push_back({max_debtor, max_creditor, abs_min_amount});

        RecursionHelper(balances, transactions);
    }

    void MinimizeCashFlow(vector<vector<int >> &debts) {
        vector<int> balances(debts.size(), 0);
        for (int i = 0; i < debts.size(); ++i) {
            for (int j = 0; j < debts[0].size(); ++j) {
                balances[i] += debts[j][i] - debts[i][j];
            }
        }
        vector<vector<int>> transactions;
        RecursionHelper(balances, transactions);
        for (const auto& txn : transactions) {
            cout << txn[0] << " --> " << txn[1] << " " << txn[2] << endl;
        }
    }
}

int main() {
    // person i needs to pay debts[i][j] person j
    vector<vector<int>> debts = {
            {0, 1000, 2000},
            {0, 0,    5000},
            {0, 0,    0},
    };
    MinimizeCashFlow(debts);
    for (int i = 0; i < debts.size(); ++i) {
        for (int j = 0; j < debts[0].size(); ++j) {
            if (debts[i][j] != 0) {
                cout << i << " " << debts[i][j] << " to " << j << endl;
            }
        }
    }
    return 0;
}