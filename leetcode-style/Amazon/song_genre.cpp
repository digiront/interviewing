#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <queue>
#include <cassert>
#include <limits>

using namespace std;

unordered_map<string, vector<string>> songsAndGenre(unordered_map<string, vector<string>> &users,
                                                    unordered_map<string, vector<string>> &genres) {
    unordered_map<string, string> songToGenre;
    unordered_map<string, unordered_map<string, int>> userToGenre;
    unordered_map<string, vector<string>> result;
    unordered_map<string, int> maxGenre;

    for (const auto &genre : genres) {
        for (const auto &song: genre.second) {
            songToGenre[song] = genre.first;
        }
    }

    for (const auto &user : users) {
        for (const auto &song : user.second) {
            userToGenre[user.first][songToGenre[song]]++;
            auto tempMax = userToGenre.at(user.first).at(songToGenre[song]);
            maxGenre[user.first] = max(tempMax, maxGenre[user.first]);
        }
    }

    for (const auto &user : userToGenre) {
        for (const auto &genre : user.second) {
            if (genre.second == maxGenre.at(user.first)) {
                result[user.first].push_back(genre.first);
            }
        }
    }

    return result;
}

void printResult(const unordered_map<string, vector<string>>& result) {
    cout << "---\nResults:" << endl;
    for (auto x: result) {
        cout << x.first << " : ";
        for (auto song:x.second) {
            cout << song << " ";
        }
        cout << endl;
    }
}

int main() {
    {
        unordered_map<string, vector<string>> users;
        users["David"] = {"song1", "song2", "song3", "song4", "song8"};
        users["Emma"] = {"song5", "song6", "song7"};

        unordered_map<string, vector<string>> songs;
        songs["Rock"] = {"song1", "song3"};
        songs["Dubstep"] = {"song7"};
        songs["Techno"] = {"song2", "song4"};
        songs["Pop"] = {"song5", "song6"};
        songs["Jazz"] = {"song8", "song9"};

        auto result = songsAndGenre(users, songs);
        printResult(result);
    }

    {
        unordered_map<string, vector<string>> users;

        users["David"] = {"song1", "song2"};
        users["Emma"] = {"song3", "song4"};

        unordered_map<string, vector<string>> songs;

        auto result = songsAndGenre(users, songs);
        printResult(result);
    }
}