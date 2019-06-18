#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    char *mem;
    int len = 0;
    // 打开文件"hello244",以读写权限，没有则创建，权限为644,同时将文件大小截断为0
    int fd = open("hello244", O_RDWR|O_CREAT|O_TRUNC, 0644);
    //int fd = open("dict.txt", O_RDWR);
    if (fd < 0)
        sys_err("open error");
    // 设置文件的大小为20
    ftruncate(fd, 20);
/*
    len = lseek(fd, 3, SEEK_SET);   //获取文件大小,根据文件大小创建映射区
    write(fd, "e", 1);              //实质性完成文件拓展
    */
    printf("The length of file = %d\n", len);
    // 映射区首地址由内核自定义，大小为20字节，权限为写，标志位共享，磁盘映射文件为fd，
    // 内存偏移0.
    //映射区大小应当不大于文件大小
    mem = mmap(NULL, 20, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED)            //出错判断
        sys_err("mmap err: ");
    close(fd);

    strcpy(mem, "xxx");
    printf("%s\n", mem);

    // 为什么释放的内存大小不是上面开辟的20字节????
    if (munmap(mem,  20) < 0)
        sys_err("munmap");

    return 0;
}

//思考：
//0. 可以open的时候O_CREAT一个新文件来创建映射区吗?
//1. 如果mem++，munmap可否成功？
//2. 如果open时O_RDONLY, mmap时PROT参数指定PROT_READ|PROT_WRITE会怎样？
//3. 如果文件偏移量为1000会怎样？
//4. 如果不检测mmap的返回值，会怎样？
//5. mmap什么情况下会调用失败？
//6. 对mem越界操作会怎样？
//7. 文件描述符先关闭，对mmap映射有没有影响？
