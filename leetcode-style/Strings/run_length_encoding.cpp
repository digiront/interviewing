#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

string RLE(const string& s) {
    if (s.empty()) return "";

    string out;
    out += s[0];
    int count = 1;
    int first = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (s[i] != s[first]) {
            if (count > 1) {
                out += to_string(count);
            }
            out += s[i];
            count = 1;
            first = i;
        }
        else {
            count++;
        }
    }
    out += to_string(count);

    return out;
}

int inplaceRLE(string& A) {
    const int N = A.size();
    if (N == 0) return 0;

    int len = 0;
    int i = 0;
    while (i < N) {
        char c = A[i];
        int count = 0;
        while (i < N && c == A[i]) {
            i++;
            count++;
        }

        A[len++] = c;
        if (count > 1) {
            string cntStr = to_string(count);
            for (char c2 : cntStr) {
                A[len++] = c2;
            }
        }
    }
    return len;
}

bool isLowercase(char c) {
    return 'a' <= c && c <= 'z';
}

void duplicateLastChar(string *out, string *countStr) {
    int count = stoi(*countStr);
    *countStr = "0";
    char c = out->back();
    for (int n = 0; n < count - 1; ++n) {
        *out += c;
    }
}
string decode(const string& rle) {
    if (rle.empty()) return "";

    string out;

    string countStr = "0";
    out += rle[0];
    for (int i = 1; i < rle.length(); ++i) {
        if (!isLowercase(rle[i])) {
            countStr += rle[i];
        }
        else {
            duplicateLastChar(&out, &countStr);
            out += rle[i];
        }
    }
    duplicateLastChar(&out, &countStr);

    return out;
}

int main() {
    const string in = "heeelloooooooooooooooooooooo";
    string encoded = RLE(in);
    cout << encoded << endl;

    string decodedStr = decode(encoded);
    cout << decodedStr << endl;
    assert(in == decodedStr);
}