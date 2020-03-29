/* 
 * 知识点：  线程安全的队列 
 * 编译命令：gcc test_queue.cpp -o test_queue.a -lstdc++ -std=c++11 -lpthread -Wc++11-extensions
 * 
 */

#ifndef __THREADSAFE_QUEUE_H_
#include <iostream>
#include <thread>
#include "threadsafe_queue.h"

using namespace std;

typedef ThreadSafeQueue<int> queue;
queue q;

void generator() {
    for(int i = 0; i < 100; ++i) {
        q.push(std::move(i));
        printf("gererate a product [%d]\n", i);
    }
}

void consumer() {
    for(int i = 0; i < 100; ++i) {
        auto t = q.wait_and_pop();
        printf("consume a product [%d]\n", *t);
    }
}

int main() {
    //queue q;
    //q.push(1);
    //q.push(1);
    //cout << "1" << endl;
    //auto t = q.wait_and_pop();
    //cout << *t << endl;
    thread t1(generator);
    thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
