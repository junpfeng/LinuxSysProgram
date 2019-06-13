#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// > dup2(newfd, oldfd),将oldfd指向newfd,比如dup2(3, 0);就是将标准输入
// > 指向3号文件描述符，结果就是，从标准输入设备读取的数据都到了3号文件描述符指向的文件
// > 比如当键盘输入数据时，系统寻找标准输入设备时，就会找到3号，而不是0号
//---------------------------------------------------------------------------------------
// > 程序功能：子进程1将标准输入设备的文件描述符绑定到管道的写端，子进程2将标准输出设备的
// > 文件描述符帮顶到管道的读端；然后子进程1调用ls，输出的信息被传给子进程2,而子进程2调用
// > wc -l 获取标准输入设备中数据的行数.

int main(void)
{
    int fd[2];
    pid_t  pid;
    int i;

    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error:");
        exit(1);
    }

    // 循环创建两个子进程
    for (i = 0; i < 2; i++){
        pid = fork();
        if (pid == -1) {
            perror("pipe error:");  //ls | wc -l
            exit(1);
        }
        if (pid == 0)
            break;
    }
    // 第一个子进程
    if (i == 0) {  //兄  ls 
        close(fd[0]);
        printf("这个是第一个子进程\n");
        dup2(fd[1], STDOUT_FILENO); // 将标准输出文件描述符指向fd[1](写端)
        execlp("ls", "ls", NULL); // ls的输出被管道传送给进程2
    } 
    else if 
    // 第二个子进程
    (i == 1) { // 弟 wc -l 
        close(fd[1]);
        printf("这个是第二个子进程\n");
        dup2(fd[0], STDIN_FILENO); // 将标准输入文件描述符指向fd[0](读端)
        execlp("wc", "wc", "-l", NULL); // 进程2统计标准输入内的数据的行数
    } else if (i == 2) {  //父 
        close(fd[0]);
        close(fd[1]);
        for(i = 0; i < 2; i++)
            wait(NULL); // 每个wait处理一个子进程
    }

    return 0;
}
