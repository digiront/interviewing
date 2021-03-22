#include <vector>
#include <iostream>

using namespace std;

namespace {
    void PrintMatrix(const vector<vector<int>> &matrix) {
        for (const auto & row : matrix) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

    void HorizontalFlip(vector<vector<int>> &matrix) {
        for (auto & row : matrix) {
            size_t left = 0;
            size_t right = row.size() - 1;
            while (left < right) {
                swap(row[left], row[right]);
                row[left] ^= 1;
                row[right] ^= 1;
                left++;
                right--;
            }
        }
    }
}

int main() {
    vector<vector<int>> matrix = {{1, 1, 0, 0},
                                  {1, 0, 0, 1},
                                  {0, 1, 1, 1},
                                  {1, 0, 1, 0}};
    HorizontalFlip(matrix);
    PrintMatrix(matrix);
    return 0;
}