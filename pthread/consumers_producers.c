/*************************************************************************
	> File Name: Consumers_producers.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月05日 星期三 12时13分30秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// 这个链表上串着食物
struct msg{
    struct msg* next;
    int num;
};

struct msg *head;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER; // 全局的条件变量
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // 全局的互斥锁

// 线程函数：消费者
void * consumer(void *p)
{
    struct msg *mp;
    while(1)
    {
        pthread_mutex_lock(&lock);
        while(head == NULL){
            // 阻塞等待条件变量has_produc，释放互斥锁
            pthread_cond_wait(&has_product, &lock);
        }
        // 吃一个
        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&lock);
        
        printf("consume--%d\n", mp->num);
        free(mp);
        mp = NULL;
        sleep(rand()%5); // 随即休眠一会儿
    }
}

void *producer(void *p)
{
    struct msg * mp = NULL;
    while(1)
    {
        mp = malloc(sizeof(struct msg));
        // 随即生产一个值
        mp->num = rand()%1000 + 1;
        printf("product--%d\n", mp->num);
        // 加锁
        pthread_mutex_lock(&lock);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);
        // 发射信号
        pthread_cond_signal(&has_product);
        sleep(rand()%5);
    }
}

int main(int argc, char ** argv)
{
    pthread_t pid, cid;
    srand(time(NULL));
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid,NULL);
    pthread_join(cid, NULL);

    return 0;
}
