/*************************************************************************
	> File Name: mmap1.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月01日 星期六 10时01分57秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
// 将文件映射到内存，往内存中写数据，观察文件的变化
int main()
{
    // 打开文件
    const char * filename = "./mytest1.txt";
    // 最后一个设置文件权限为读和写：0200和0400
    // 当第二个参数指定了O_CREAT，就需要指定权限（即第三个参数）
    // 如果文件已经存在，就不能使用O_CREAT
    int fd = open(filename, O_CREAT|O_RDWR, 0600);
    if (fd == -1)
    {
        perror("open error");
        exit(0);
    }

    // 设在mmap映射区
    // 获取文件的大小---其实是设置文件的大小
    int size = 4;
    // 将p指针作为mmap映射区的首地址
    char * p = NULL; 
    int ret = ftruncate(fd, size);
    if (ret == -1)
    {
        perror("ftruncate error");
        exit(1);
    }
    // mmap映射成功会返回指向该映射区的指针
    p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap error");
        exit(0);
    }
    strcpy(p, "123");

    // 关闭映射区和文件描述符
    ret = munmap(p, size);
    if (ret == -1)
    {
        perror("ret error");
        exit(0);
    }
    close(fd);
    exit(0);

}
