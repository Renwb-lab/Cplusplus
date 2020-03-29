
线程
----

1. pthread.cpp 使用Linux 下的pthread_create 创建线程并运行。
2. mutex.cpp   使用Linux 下的pthread_mutex_t 创建锁并运行。 
3. threadsafe_queue_v1.h 使用c++11中thread, mutex 和 condition_variable 创建线程进行操作。其中，内部封装了一个queue，读取都需要对整个queue加锁。
4. threadsafe_queue_v2.h 使用c++11中thread, mutex 和 condition_variable 创建线程进行操作。其中，内部自定义了list, 读取的话只会对head进行加锁，加入的话只会对tail进行加锁。
5. test_queue.cpp 为测试程序。
