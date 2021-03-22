// Example program
#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;

class WeightedRandomGenerator {
    vector<int> sums;
public:
    WeightedRandomGenerator(vector<int>& weights) : sums(weights.size()) {
        int acc = 0;
        for (int i = 0; i < weights.size(); ++i) {
            acc += weights[i];
            sums[i] = acc;
        }
    }

    int pickIndex() {
        static random_device rd; // obtain a random number from hardware
        static default_random_engine eng(rd()); // seed the generator
        uniform_real_distribution<> d(0, sums.back());

        auto it = upper_bound(sums.begin(), sums.end(), d(eng));
        return it - sums.begin();
    }
};

int main()
{
    vector<int> w(10);
    iota(w.begin(), w.end(), 0);
    WeightedRandomGenerator wrg(w);

    map<int, int> freq;
    for (int i = 0; i < 1000; ++i) {
        freq[wrg.pickIndex()]++;
    }

    for (const auto& [idx, times] : freq) {
        cout << "idx: " << idx << ", times: " << times << endl;
    }

    return 0;
}