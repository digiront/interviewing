// Example program
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

vector<string> parseSpaceDelim(const string& s) {
	vector<string> e;
	istringstream iss(s);
	for (string x; iss >> x; ) e.push_back(x);
	return e;
}

void parseWithFind() {
    std::string s = "gg|wp|noob";
    std::string delimiter = "|";
    size_t last = 0;
    size_t next = 0;
    while ((next = s.find(delimiter, last)) != string::npos) {
        cout << s.substr(last, next-last) << endl;
        last = next + delimiter.size();
    }
    cout << s.substr(last) << endl;
}

vector<string> SplitUsingGetline(const string& str) {
    stringstream ss(str);
    string token;

    vector<string> tokens;
    while (getline(ss, token, '|')) {
        if (token.empty()) continue;
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
//    parseSpaceDelim(" hello word ");
//    parseWithFind();
    auto res = SplitUsingGetline("|a|b|c|");
    cout << res.size() << " tokens:" << endl;
    for (const string& s : res) {
        cout << s << endl;
    }
    return 0;
}

