#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */
class Solution {
    const int s_threadNum = 10;

    mutex d_mutex;
    condition_variable d_cv;
    queue<string> d_queue;
    unordered_set<string> d_visited;
    int d_waiting = 0;

    string getDomain(const string& url) {
        return url.substr(0, url.find("/", 7));
    }

    void work(HtmlParser *htmlParser, const string& startUrl) {
        while(true) {
            // start of critical section
            unique_lock<mutex> ul(d_mutex);

            d_waiting++;
            d_cv.wait(ul, [this]{
                return !d_queue.empty() || (d_queue.empty() && d_waiting == s_threadNum);
            });

            if (d_queue.empty()) {
                return;
            }
            d_waiting--;

            string curUrl = d_queue.front();
            d_queue.pop();
            d_visited.insert(curUrl);
            ul.unlock();
            // end of critical section

            vector<string> otherUrls = htmlParser->getUrls(curUrl);
            unique_lock<mutex> ul2(d_mutex);
            for (const auto& u : otherUrls) {
                if (d_visited.count(u) == 1) continue;

                const string prefix = getDomain(u);
                if (startUrl.find(prefix) == 0) {
                    d_queue.push(u);
                }
            }
            d_cv.notify_all();
        }
    }

public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        vector<thread> threads;

        // setup worker threads
        {
            lock_guard<mutex> lg(d_mutex);
            d_queue.push(startUrl);

            for (int i = 0; i < s_threadNum; ++i) {
                threads.emplace_back(&Solution::work, this, &htmlParser, getDomain(startUrl));
            }
        }

        for (int i = 0; i < s_threadNum; ++i) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }

        // no one should be modifying d_visited at this point
        vector<string> results(d_visited.begin(), d_visited.end());
        return results;
    }

};