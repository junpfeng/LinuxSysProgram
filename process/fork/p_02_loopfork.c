/*************************************************************************
	> File Name: p_02_loopfork.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月11日 星期二 21时40分57秒
    > 循环创建N个子进程
    > 从shell允许该程序，那么shell就是这里父进程的父进程
 ************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

#define N 5
// argc保存输入参数的个数，至少是1,即该可执行程序名
int main(int argc, char **argv)
{
    int n = N;
    if (argc == 2)
    {
        // 输入的参数默认以字符串形式传入
        n = atoi(argv[1]); // 将数字字符串变为整型数字
    }

    int i = 0;
    for (i =0;i < n; ++i)
        if (fork() == 0) // 子进程就跳出循环，保证所有子进程都是有父进程创建
            break;

    // 父进程-----------
    if (n == i) // 由于父进程一直在创建子进程，因此n=i是父进程才有的
    {
        sleep(n);
        printf("l am parent, pid = %d\n", getpid());
    }
    else
    {
        sleep(i);
        printf("l am %dth child, pid = %d\n", i + 1, getpid());
    }
  // -----等同下面这个
//    sleep(i);
//    if (i == n)
//        printf("l am parent, pid = %d\n", getpid());
//    else
//        printf("l am %dth, pid = %d\n", i + 1, getpid());
//
//    return 0;
}

