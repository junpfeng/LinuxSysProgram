/*************************************************************************
	> File Name: mmap3_父子进程.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月01日 星期六 13时30分41秒
 ************************************************************************/

#include<stdio.h>

#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

// 测试使用mmap在父子进程之间通信：全局变量和映射区地址变量
// 注意其中需要一个unlink()函数
int var = 2100;
int main(void)
{
    char *p;
    pid_t pid;

    int fd;
    // 将"temp"文件的长度截断为0
    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open error");
        exit(0);
    }
    // 删除temp文件目录项:当所有使用该文件的进程结束后，该文件被删除
    unlink("./temp");
    const int size = 4;
    int ret =  ftruncate(fd, size);
    if (ret == -1)
    {
        perror("ftruncate error");
        exit(0);
    }
    // 建立内存映射
    p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
//    p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0); // MAP_PRIVATE
    if (p == MAP_FAILED)
    {
        perror("mmap error");
        exit(0);
    }
    // 内存映射一旦完成，就不需要文件描述符了
    close(fd);


    pid = fork();
    // 子进程
    if (pid == 0)
    {
        strcpy(p, "200");
        var = 2000;
        printf("chile var is %d, p is %s\n", var, p);
    }
    else
    {
        sleep(1);
        // 全局变量读时共享
        printf("parent var is %d, p is %s\n", var, p);
        wait(NULL); // 
        
        int ret = munmap(p, 4);
        if (ret == -1)
        {
            perror("munmap error");
            exit(1);
        }
    }

}
