/*************************************************************************
	> File Name: mmap5_w.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月01日 星期六 17时09分11秒
 ************************************************************************/

#include<stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

struct STU
{
    int id;
    char name[20];
    char sex;
};

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("请输入参数\n");
        exit(0);
    }
    struct STU stud = {1, "xiaom", 'm'};
    // 打开文件,文件必须可读，否则无法映射
    int fd = open(argv[1], O_RDWR|O_CREAT, 0664);
    if (fd == -1)
    {
        perror("openen failed\n");
        exit(0);
    }
    int ret = ftruncate(fd, sizeof(stud));
    if (ret == -1)
    {
        perror("ftruncate\n");

    }
    // 建立mmap映射

    struct STU *mm;
    mm = mmap(NULL, sizeof(stud), PROT_WRITE|PROT_READ, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
    {
        perror("mmap failed");
        exit(0);
    }

    // 写数据
//    mm->id = 0;
//    strcpy(mm->name, "xiaom");
//    mm->sex = 'm';
    int num = 10;
    while(num--)
    {
        stud.id = num;
//        memcpy(mm, &stud, sizeof(stud));
        mm->id = num;
        mm->sex = 's';
        strcpy(mm->name, "num");
        sleep(1); 
    }


    // 解除映射
    munmap(mm, sizeof(stud));

    return 0;
}
