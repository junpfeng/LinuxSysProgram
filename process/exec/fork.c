#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// > 父进程复制一个子进程，然后在子进程中执行ls程序
// > execl和execlp的区别在于，execl只能使用可执行程序的
// > 绝对地址，而不能搜索PATH变量里存放的值
// > 由于父进程没有等待子进程，导致父进程率先返回，
// > 那么终端显示的效果就是，子进程在终端后面显示了
int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid == -1 ) {
        perror("fork");
        exit(1);
    } else if (pid > 0) {
            printf("I'm parent pid = %d, parentID = %d\n", getpid(), getppid());

    }

    else if (pid == 0) // 子进程
    {
        sleep(3);
        printf("i am child\n");
        execl("/bin/ls", "ls", "-l",  NULL);
        perror("exec");
        exit(1);
    }

    printf("-------finish...%d\n", getpid());

    return 0;
}
