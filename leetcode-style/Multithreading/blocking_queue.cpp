#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>

using namespace std;

template<typename T>
class BlockingQueue {
    size_t max_size_;
    mutex mutex_;
    condition_variable cv_;
    queue<T> queue_;

public:
    explicit BlockingQueue(size_t maxSize) : max_size_(maxSize), mutex_(), cv_(), queue_() {}

    void push(const T &e) {
        std::unique_lock<std::mutex> lk(mutex_);
        cv_.wait_for(lk, 1s, [this] { return queue_.size() != max_size_; });
        queue_.push(e);
        cout << "Pushed: " << e << endl;
        // see notify_one() docs
        lk.unlock();
        cv_.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lk(mutex_);
        cv_.wait_for(lk, 100ms, [this] { return !queue_.empty(); });

        // get local copy and extract from queue
        T val = queue_.front();
        queue_.pop();
        cout << "Popped: " << val << endl;

        lk.unlock();
        cv_.notify_all();
        return val;
    }
};

int main() {
    int maxSz = 4;
    BlockingQueue<int> q(maxSz);

    thread producer1([&]() {
        for (int i = 0; i < 10 * maxSz; ++i) q.push(i);
    });

    thread producer2([&]() {
        for (int i = 0; i < 2 * maxSz; ++i) q.push(i);
    });

    thread consumer1([&]() {
        for (int i = 0; i < 2 * maxSz; ++i) q.pop();
    });

    producer1.join();
    producer2.join();
    consumer1.join();
    return 0;
}