/*************************************************************************
	> File Name: p_01_fork.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月11日 星期二 21时21分45秒
    > 一个简单的创建新进程的代码
 ************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>

int var = 40;

int main()
{
    pid_t pid;
    printf("---------\n");
    if ((pid=fork()) == -1){
         perror("fork error");
        exit(1);
    }else if (pid == 0){
        var = 19;
        printf("这是子进程，pid=%d, parentID=%d, var=%d\n", getpid(), getppid(), var);
    }else if (pid > 0){
        var = 100;
        printf("这是父进程，pid=%d, parentID=%d, var=%d\n", getpid(),getppid(), var);
    }
        printf("var=%d\n", var);

        return 0;
}
