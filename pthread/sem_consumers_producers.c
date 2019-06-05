/*************************************************************************
	> File Name: sem_consumers_producers.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月05日 星期三 14时41分41秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define NUM 5
int queue[NUM];

// 信号量
sem_t blank_number, product_number;

void * producer(void * arg)
{
    int i = 0; 
    while(1)
    {
        // 给blank_number信号量减1。当信号量值为0时不减了，直接阻塞
        sem_wait(&blank_number);

        queue[i] = rand()%1000  + 1;
        printf("---produce----%d\n", queue[i]);
        // 给product_number信号量加一，同时唤醒阻塞在product_number上的信号
        sem_post(&product_number);
        
        i= (i+1)%NUM;
        sleep(rand()%3);
    }
}

void * consumer(void * arg)
{
    int i = 0;
    while(1)
    {
        // 给product_number信号量减一，当信号量值为0时阻塞
        sem_wait(&product_number);
            printf("consumerr --%d\n", queue[i]);
        queue[i] = 0;

        // 给blank_number信号量加一,同时唤醒阻塞在blank_number上的线程
        sem_post(&blank_number);
        i =  (i + 1)%NUM;
        sleep(rand()%3);
    }
}

int main(int argc, char *argv[])
{
    pthread_t pid, cid;
    // 初始化之后，信号量为NUM，先给生产者生存5次
    sem_init(&blank_number, 0, NUM);
    // 消费者至少等生产者生产完一个了再开
    sem_init(&product_number, 0, 0);

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}
