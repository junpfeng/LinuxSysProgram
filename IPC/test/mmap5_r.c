/*************************************************************************
	> File Name: mmap5_无血缘关系.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月01日 星期六 16时33分20秒
 ************************************************************************/

#include<stdio.h>


#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

// 无血缘关系的进程之间使用mmap的方法
//
struct STU
{
    int id;
    char name[20];
    char sex;
};

// 输入的参数是作为磁盘映射的文件
int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("请输入参数\n");
        exit(0);
    }

    // 打开文件
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("open error");
        exit(0);
    }

    struct STU stud;
    struct STU *mm = NULL;
    // 建立磁盘映射区
    mm = mmap(NULL, sizeof(stud), PROT_READ, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
    {
        perror("mmap error\n");
        exit(0);
    }
    close(fd);

    while(1)
    {
        printf("id=%d\tname=%s\n%c\n", mm->id, mm->name, mm->sex);
        sleep(1);
    }

    // 解除磁盘映射
    munmap(mm, sizeof(stud));
    return 0;

}


