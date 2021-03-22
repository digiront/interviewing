// Example program
#include <iostream>
#include <string>

#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>

using Job = std::function<int()>;

class ThreadPool {
  private:
    std::vector<std::thread> workers; 
    std::queue<Job>         jobs;
    std::mutex              mutex;
    std::condition_variable cv;
    bool                    stopped;
    
    // PRIVATE MANIPULATORS
    void stopImp();
    
  public:
    // CONSTRUCTORS
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    // PUBLIC MANIPULATORS
    std::future<int> enqueue(const Job& job);
    void stop();
};

void ThreadPool::stopImp() {
    std::unique_lock<std::mutex> lock(mutex);
    if (stopped) return;
    stopped = true;
    cv.notify_all();
}

ThreadPool::ThreadPool(size_t numThreads)
: workers(numThreads)
, jobs()
, mutex()
, cv()
, stopped(false)
{
    for (size_t i = 0; i < numThreads; ++i) {
        // create numThreads that consume the queue until stop is called
        workers.emplace_back([this]() {
            while(true) {
                Job newJob;
                {
                    std::unique_lock<std::mutex> lock(mutex);
                    cv.wait(lock, [this]() { return stopped; });
                    if (stopped) return;
                    newJob = jobs.front(); // bonus points for std::move, std::forward etc.
                    jobs.pop();
                }
                
                newJob();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stopImp();
}

std::future<int> ThreadPool::enqueue(const Job& job)
{
    std::future<int> f = std::async(job);
    {
        std::unique_lock<std::mutex> lock(mutex);
        if (stopped) {
            return std::async([]() {return -777;});
        }
        jobs.push(job);
    }
    cv.notify_one();
    return f;
}

void ThreadPool::stop()
{
    stopImp();
}

int main()
{
    
    ThreadPool pool(4);
    std::vector<std::future<int>> results;

    for(int i = 0; i < 10; ++i) {
        results.push_back(
            pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                return i;
            })
        );
    }

    for(auto& result : results) {
        std::cout << result.get() << std::endl;
    }
    
    return 0;
}