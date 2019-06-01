/*************************************************************************
	> File Name: mmap4_匿名映射.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月01日 星期六 15时48分02秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>


// 传统的mmmap先打开一个文件，再将文件映射到内存映射区，然后文件就没用了
// 如果能不打开文件，直接开辟一个内存映射区，岂不是很方便
// 因此，出现了匿名映射：只需要改mmap函数的两个地方：
// fd改成-1, flags里或上一个 MAP_ANON
//
// 值得注意的是，MAP_ANON这个宏只有在linux下有用，在其他类UNIX系统不能用


int main()
{
    int var = 1;
    char * p = NULL;
    const int size = 40;
    // 直接创建匿名映射区
    p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap error");
        exit(0);
    }
    // fork子进程
    pid_t pid = fork();

    // 子进程写
    if (pid == 0)
    {
        var = 2;
        strcpy(p, "nihao");
        printf("son var is %d, p is %s\n", var, p);
    }
    // 父进程读
    else
    {
        sleep(1);
        printf("parent var is %d, p is %s\n", var, p);

    }
}

