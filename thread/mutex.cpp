/*
 * 知识点：  学习 pthread 知识
 * 编译命令：gcc mutex.cpp -o mutex.o -pthread
 */

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sched.h>

void *product_f(void *arg);
void *consumer_f(void *arg);

int buffer_has_item = 0;
pthread_mutex_t mutex;

int running = 1;

int main(void) {
	pthread_t consumer;
	pthread_t product;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&product, NULL, product_f, NULL);
	pthread_create(&consumer, NULL, consumer_f, NULL);

	usleep(200);
	running = 0;
	pthread_join(product, NULL);
	pthread_join(consumer, NULL);
	pthread_mutex_destroy(&mutex);

	return 0;
}

void* product_f (void *arg) {
	while (running) {
		pthread_mutex_lock(&mutex);
		buffer_has_item ++;
		usleep(1);
		printf("生产， 总数量: %d\n", buffer_has_item);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void* consumer_f(void* arg) {
	while (running) {
		pthread_mutex_lock(&mutex);
		buffer_has_item --;
		usleep(1);
		printf("消费，总数量: %d\n", buffer_has_item);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

