/*************************************************************************
	> File Name: mmap2_一些问题.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月01日 星期六 11时10分16秒
 ************************************************************************/

#include<stdio.h>
// mmap不能创建内存大小为0的映射区
// 不能随意改变mmap映射区的首地址（改了就得改回去）
// MAP——SHAERD下，映射区的权限要小于等于文件的权限
// 映射的过程有一次自发的读操作，即文件必须要有 读权限 
// mmap函数的最后一个参数 offset 的偏移量必须是 4k 的整数倍（因为磁盘的最小单位就是4k)
// 关闭文件描述符和mmap的的顺序是随意的，因为一旦将文件和内存区建立映射之后，就可以使用
// 映射区的指针来操作文件，故文件描述符可以不用了
// mmap容易出错，要记得检查返回值。

#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>


int main()
{
    // 打开或者新建文件
    int fd = open("./mytest.txt", O_CREAT|O_RDWR, 0600);
    if (fd == -1)
    {
        perror("open error");
        exit(0);
    }
    // 刚建立的文件内因为没有内容，故大小应当是0吧
    const int size =4;
    int ret = ftruncate(fd, size);
    

    // 建立映射
    char * p = NULL;
    p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap failed");
        exit(0);
    }

    strcpy(p, "234");
    munmap(p, size);
    close(fd);
    exit(0);
}

