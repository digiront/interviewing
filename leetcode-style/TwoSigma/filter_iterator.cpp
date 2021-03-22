#include <vector>
#include <iostream>
#include <functional>
#include <numeric>

using namespace std;


class FilterIterator {
    using FilterFn = function<bool(int)>;
    using It = vector<int>::iterator;

    bool initialized;
    It it;
    It end;
    FilterFn filterFn;

    void init() {
        if (!initialized) {
            initialized = true;
            findNext();
        }
    }

    bool findNext() {
        while (it != end) {
            if (filterFn(*it)) return true;
            it++;
        }
        return false;
    }

public:
    FilterIterator(It vit, It vend, FilterFn filterFunction)
    : it(vit)
    , end(vend)
    , filterFn(filterFunction)
    , initialized(false)
    {
    };

    int next() {
        init();

        int v = *it;
        ++it;
        findNext();
        return v;
    }

    bool hasNext() {
        init();
        return it != end;
    }
};

bool dividedBy5(int n) {
    return n % 5 == 0;
}

int main() {
    vector<int> v(6);
    iota(v.begin(), v.end(), 0);
    FilterIterator fIt(v.begin(), v.end(), bind(&dividedBy5, placeholders::_1));

    while (fIt.hasNext()) {
        cout << fIt.next() << endl;
    }
    return 0;
}