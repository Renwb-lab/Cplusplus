/*
 * 知识点：  线程安全的队列 
 *
 */

#ifndef __THREADSAFE_QUEUE_H_
#define __THREADSAFE_QUEUE_H_

#include <mutex>
#include <memory>
#include <functional>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {

public:
    ThreadSafeQueue(): head(new node), tail(head.get()) {}
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue operator= (const ThreadSafeQueue&) = delete;
    ~ThreadSafeQueue() = default;

    std::shared_ptr<T> try_pop() {
        std::unique_lock<std::mutex> ulm(hm);
        if (head.get() == get_tail())
            return nullptr;

        auto old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head->data;
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> ulk(hm);
        {
            std::unique_lock<std::mutex> ulk(tm);
            cond.wait(ulk, [&](){ return head.get() != tail; });
        }
        auto old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head->data;
    }

    void push(T &&t) {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::forward<T>(t)));
        //std::shared_ptr<T> new_data(std::make_shared<T>(t));
        std::unique_ptr<node> new_tail(new node);
        node *p = new_tail.get();
        {
            std::unique_lock<std::mutex> ulk(tm);
            tail->data = new_data;
            tail->next = std::move(new_tail);
            tail = p;
        }
        cond.notify_one();
    }

private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex hm;
    std::mutex tm;

    std::unique_ptr<node> head;
    node *tail;
    std::condition_variable cond;

    node* get_tail() {
        std::unique_lock<std::mutex> ulkt(tm);
        return tail;
    }
};

#endif

