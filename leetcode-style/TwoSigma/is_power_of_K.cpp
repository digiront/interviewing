#include <iostream>

using namespace std;

bool isPowerOf(int n, int K) {
    if (n == 0) return false;
    while (n % K == 0) n /= K;
    return n == 1;
}

int main() {
    int K = 4;
    for (int i = 0; i < 20; ++i) {
        if (isPowerOf(i, K)) {
            cout << i << " is a power of " << K << endl;
        }
    }
    return 0;
}

