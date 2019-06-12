/*************************************************************************
	> File Name: p_03_sharedfork.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月12日 星期三 19时01分28秒
    > 父子进程之间的用户空间是独立的，原则：写时复制，读时共享
 ************************************************************************/
#include <stdlib.h>
#include <unistd.h>
#include<stdio.h>
// 用于测试：全局变量不共享
int a = 100;

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0) //子进程
    {
        a = 1;
        printf("这是子进程，id = %d, a = %d\n", getpid(), a);
    }
    else
    {
        printf("这是父进程，id = %d, a = %d\n", getpid(), a);
    }
    return 0;
}

