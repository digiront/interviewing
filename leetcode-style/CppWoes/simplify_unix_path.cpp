// Example program
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string simplifyPath(const string& path, char delim = '/') {
    string token;
    vector<string> tokens;
    stringstream ss(path);
    while(getline(ss, token, delim)) {
        if (token.empty()) continue;
        if (token == ".") continue;
        if (token == "..") {
            if (!tokens.empty()) tokens.pop_back();
        }
        else {
            tokens.push_back(token);
        }
    }

    if (tokens.empty()) return "/";

    string out;
    for (const auto& t : tokens) {
        out += "/" + t;
    }
    return out;
}

int main()
{
    simplifyPath("/a/b/..///c/");
    return 0;
}

