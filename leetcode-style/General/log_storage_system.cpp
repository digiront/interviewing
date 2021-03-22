#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// id | ts
// ts = s, id = 1
// ts = s, id = 2
// ts = s, id = 1 INVALID

// strat = "2019:01:01:23:59:59",
// end = "2019:01:02:23:59:59"
// granularity = "Day"

void printResults(const vector<int> &res) {
    cout << "Ids: \n";
    for (int id : res) {
        cout << id << " ";
    }
    cout << endl;
}

class StorageSystem {
    map<string, vector<int>> logs;
    unordered_map<string, int> m;
    string minTs;
    string maxTs;
public:
    StorageSystem()
            : logs(), m(), minTs("2000:01:01:00:00:00"), maxTs("2050:12:31:23:59:59") {
        m["Year"] = 4;
        m["Month"] = 7;
        m["Day"] = 10;
        m["Hour"] = 13;
        m["Minute"] = 16;
        m["Second"] = 19;
    }

    void put(int id, string ts) {
        logs[ts].push_back(id);
    }

    vector<int> retrieve(const string &start, const string &end, const string &granularity) {
        int prefixLen = m[granularity];

        string searchStart = start.substr(0, prefixLen) + minTs.substr(prefixLen);
        string searchEnd = end.substr(0, prefixLen) + maxTs.substr(prefixLen);

        auto startIt = logs.lower_bound(searchStart); // will point to the first that's less than this key
//        if (startIt != logs.end()) startIt++;
        cout << "ts: " << startIt->first << endl;
//        printResults(startIt->second);

        auto endIt = logs.upper_bound(searchEnd);
        if (endIt != logs.end()) { cout << "ts: " << endIt->first << endl; }
//        if (endIt != logs.begin()) endIt--;
        vector<int> results;
        for (auto it2 = startIt; it2 != endIt; ++it2) {
            if (it2->first <= searchEnd) {
                for (int id : it2->second) {
                    results.push_back(id);
                }
            }
            else {
                // traversing in sorted order ascending
                break;
            }
        }

        return results;
    }
};

void runTests() {
    StorageSystem ss;
    ss.put(-1, "2000:01:01:00:00:01");
    ss.put(0, "2001:01:01:00:00:00");
    ss.put(1, "2001:01:01:00:00:00");
    ss.put(2, "2001:02:01:00:00:00");
    ss.put(3, "2001:02:02:00:00:00");
    ss.put(4, "2002:01:01:00:00:00");
    ss.put(5, "2002:02:01:00:00:00");
    ss.put(6, "2002:02:02:00:00:00");


    printResults(ss.retrieve("2000:01:01:00:00:00", "2002:02:02:00:00:00", "Year"));
    printResults(ss.retrieve("2000:01:01:00:00:01", "2002:02:02:00:00:00", "Second"));
    printResults(ss.retrieve("2001:01:01:00:00:00", "2001:02:01:00:00:00", "Month"));

    printResults(ss.retrieve("2000:01:01:00:00:01", "2001:01:01:00:00:01", "Second"));

    printResults(ss.retrieve("2000:01:01:00:00:01", "2000:01:01:00:00:01", "Second"));
}

int main() {


    map<int, string> m;
    m[0] = "a";
    m[1] = "b";
    m[2] = "c";
    m[3] = "d";
    m[4] = "e";
    cout << (m.lower_bound(-1) == begin(m)) << endl;

    auto endIt = m.upper_bound(15);
    cout << (endIt == end(m)) << endl;
    return 0;
}
