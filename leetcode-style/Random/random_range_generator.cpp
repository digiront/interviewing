#include <iostream>
#include <string>
#include <random>
#include <unordered_set>

using namespace std;

class RandomGenerator {
    int d_min;
    int d_max;

    unordered_set<int> d_blacklist;

    int nextRandom() {
        static random_device rd; // obtain a random number from hardware
        static default_random_engine eng(rd()); // seed the generator
        uniform_int_distribution<> dist(d_min, d_max); // generate a number between 0 and N
        return dist(eng);
    }

public:
    RandomGenerator(int min, int max)
    : d_min(min)
    , d_max(max)
    , d_blacklist()
    {
    }

    int getRandom() {
        if (d_blacklist.size() == (d_max - d_min + 1)) {
            d_blacklist.clear();
            cout << "Cleared" << endl;
        }

        // Cannot repeat a number in the range, until all numbers are picked once
        int r;
        do {
            r = nextRandom();
        } while (d_blacklist.count(r) == 1);
        d_blacklist.insert(r);
        return r;
    }

};

// Follow up:
// Can change the range anytime

class RandomGenerator2 {
    int d_min;
    int d_max;

    unordered_set<int> d_whitelist;
    unordered_set<int> d_blacklist;

    int nextRandom() {
        static random_device rd; // obtain a random number from hardware
        static default_random_engine eng(rd()); // seed the generator
        uniform_int_distribution<> dist(0, d_whitelist.size() - 1); // generate a number between 0
        // and N
        return dist(eng);
    }

public:
    void setRange(int min, int max) {
        cout << "Set range: [" << min << ", " << max << "]" << endl;
        d_min = min;
        d_max = max;

        unordered_set<int> newWhiteList;
        for (const auto& it : d_whitelist) {
            int v = it;
            if (v >= min && v <= max)
                newWhiteList.insert(v);
        }

        for (int i = min; i <= max; ++i) {
            if (d_blacklist.count(i) == 0) {
                newWhiteList.insert(i);
            }
        }

        swap(d_whitelist, newWhiteList);
    }
    int getRandom() {
        if (d_whitelist.empty()) {
            for (int i = d_min; i <= d_max; ++i) {
                d_whitelist.insert(i);
            }
            d_blacklist.clear();
            cout << "Cleared" << endl;
        }

        int randIdx = nextRandom();
        auto it = d_whitelist.begin();
        while (--randIdx > 0) it++;

        int v = *it;
        d_whitelist.erase(it);
        d_blacklist.insert(v);
        return *it;
    }

};

int main()
{
    RandomGenerator2 g;
    g.setRange(1, 3);

    cout << "---" << endl;
    for (int i = 0; i < 9; ++i) {
        cout << g.getRandom() << endl;
    }

    cout << "---" << endl;
    cout << g.getRandom() << endl;
    cout << g.getRandom() << endl;

    cout << "---" << endl;
    g.setRange(1,5);
    for (int i = 0; i < 5; ++i) {
        cout << g.getRandom() << endl;
    }
    cout << "---" << endl;
    g.setRange(8, 12);
    for (int i = 0; i < 9; ++i) {
        cout << g.getRandom() << endl;
    }
    return 0;
}
