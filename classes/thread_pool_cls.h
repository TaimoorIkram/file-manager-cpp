#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

class thread_pool_cls {
public:
    thread_pool_cls(size_t num_threads) : _stop(false) {
        for (size_t i = 0; i < num_threads; i++) {
            _threads.emplace_back([this] {
                while (true) {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _condition.wait(lock, [this] { return _stop || !_tasks.empty(); });
                    if (_stop && _tasks.empty()) {
                        return;
                    }
                    auto task = std::move(_tasks.front());
                    _tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    ~thread_pool_cls() {
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _stop = true;
        }
        _condition.notify_all();
        for (auto& thread : _threads) {
            thread.join();
        }
    }

    template<typename Func, typename... Args>
    void enqueue(Func&& func, Args&&... args) {
        auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _tasks.emplace(std::move(task));
        }
        _condition.notify_one();
    }

private:
    std::vector<std::thread> _threads;
    std::queue<std::function<void()>> _tasks;
    std::mutex _mutex;
    std::condition_variable _condition;
    bool _stop;
};