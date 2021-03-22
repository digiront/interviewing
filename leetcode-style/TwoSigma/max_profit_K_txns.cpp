#include <vector>
#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

int maxProfit(vector<int>& prices, int K) {
    const int N = prices.size();
    if (N == 0) return 0;

    // Kth transaction, Nth day
    vector<vector<int>> dp(K + 1, vector<int>(N));
    for (int t = 1; t <= K; ++t) {
        int maxProfit = INT_MIN;
        for (int d = 1; d < N; ++d) {
            // prev max OR whatever we had minus buy at previous price
            maxProfit = max(maxProfit, dp[t - 1][d - 1] - prices[d - 1]);
            // Don't do txn OR sell with current price
            dp[t][d] = max(dp[t][d - 1], maxProfit + prices[d]);
        }
    }
    return dp[K][N-1];
}

/* ULTRA OPTIMIZED */
int quickSolve(const vector<int>& prices) {
    int len = prices.size(), profit = 0;
    for (int i = 1; i < len; i++)
        // as long as there is a price increase, we gain a profit.
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    return profit;
}

int maxProfitOptimized(vector<int>& prices, int K) {
    const int N = prices.size();
    if (N == 0) return 0;
    if (K >= N/2) {
        return quickSolve(prices);
    }

    //             - dp[t][d-1] i.e. we don't transact on day d
    // dp[t][d] = -
    //             - prices[d] + max(-prices[x] + dp[t - 1][x]) for each x in [0, d)
    //               i.e. sell on d and max profit but taking into account one buy

    vector<int> oddProfits(N);
    vector<int> evenProfits(N);
    vector<int> *curProfits;
    vector<int> *prevProfits;

    for (int t = 1; t <= K; ++t) {
        int maxProfit = INT_MIN;
        if (t % 2 == 1) {
            curProfits = &oddProfits;
            prevProfits = &evenProfits;
        }
        else {
            curProfits = &evenProfits;
            prevProfits = &oddProfits;
        }

        for (int d = 1; d < N; ++d) {
            // prev max OR whatever we had minus buy price
            maxProfit = max(maxProfit, (*prevProfits)[d - 1] - prices[d - 1]);
            // Don't do txn OR sell with current price
            (*curProfits)[d] = max((*curProfits)[d - 1], maxProfit + prices[d]);
        }

    }
    return K % 2 == 0 ? evenProfits[N - 1] : oddProfits[N - 1];
}
/* END OF OPTIMIZED SOLUTION */

int main() {
    vector<int> vector1;
    vector<int> vector2{1};
    vector<int> vector3{1, 10};
    vector<int> vector4{1, 10};
    vector<int> vector5{3, 2, 5, 7, 1, 3, 7};
    vector<int> vector6{5, 11, 3, 50, 60, 90};
    vector<int> vector7{5, 11, 3, 50, 60, 90};
    vector<int> vector8{5, 11, 3, 50, 40, 90};
    vector<int> vector9{5, 11, 3, 50, 40, 90};
    vector<int> vector10{50, 25, 12, 4, 3, 10, 1, 100};
    vector<int> vector11{100, 99, 98, 97, 1};
    vector<int> vector12{1, 100, 2, 200, 3, 300, 4, 400, 5, 500};
    vector<int> vector13{1, 100, 101, 200, 201, 300, 301, 400, 401, 500};
    vector<int> vector14{1, 25, 24, 23, 12, 36, 14, 40, 31, 41, 5};
    vector<int> vector15{1, 25, 24, 23, 12, 36, 14, 40, 31, 41, 5};

    assert(maxProfit(vector1, 1) == 0);
    assert(maxProfit(vector2, 1) == 0);
    assert(maxProfit(vector3, 1) == 9);
    assert(maxProfit(vector4, 3) == 9);
    assert(maxProfit(vector5, 1) == 6);
    assert(maxProfit(vector6, 2) == 93);
    assert(maxProfit(vector7, 3) == 93);
    assert(maxProfit(vector8, 2) == 97);
    assert(maxProfit(vector9, 3) == 103);
    assert(maxProfit(vector10, 2) == 106);
    assert(maxProfit(vector11, 5) == 0);
    assert(maxProfit(vector12, 5) == 1485);
    assert(maxProfit(vector13, 5) == 499);
    assert(maxProfit(vector14, 4) == 84);
    assert(maxProfit(vector15, 2) == 62);

    return 0;
}

