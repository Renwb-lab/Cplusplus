/*
 * 知识点：  线程安全的队列 
 *
 */

#ifndef __THREADSAFE_QUEUE_H_
#define __THREADSAFE_QUEUE_H_

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {

public:
    ThreadSafeQueue(){}
    ~ThreadSafeQueue() {}

    void push(T t) {
        std::lock_guard<std::mutex> ulk(m);
        q.push(std::move(t));
        cond.notify_one(); 
    }

    void wait_and_pop(T &val) {
        std::unique_lock<std::mutex> ulk(m);
        cond.wait(ulk, [this](){return !q.empty();});
        val = std::move(q.front());
        q.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> ulk(m);
        cond.wait(ulk, [this](){ return !q.empty();});
        std::shared_ptr<T> val(std::make_shared<T>(std::move(q.front())));
        q.pop();
        return val;
    }

    bool try_pop(T& val) {
        std::lock_guard<std::mutex> ulk(m);
        if (q.empty()) {
            return false;
        }
        val = std::move(q.front());
        q.pop();
        return true;
    }

    std::shared_ptr<T> try_pop() {
        std::shared_ptr<T> val;
        std::lock_guard<std::mutex> ulk(m);
        if (q.empty())
            return val;
        val = std::make_shared<T>(std::move(q.front()));
        q.pop();
        return val;
    }

    bool empty() {
        std::lock_guard<std::mutex> ulk(m);
        return q.empty();
    }

private:
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cond;
};

#endif 
