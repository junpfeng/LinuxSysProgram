#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// > 程序功能：观察子进程死亡前后，父进程输出的子进程ID的变换

int main(void)
{
    pid_t pid, wpid;
    pid = fork();

    if (pid == 0) {
            printf("---child, my parent= %d, going to sleep 10s\n", getppid());
            sleep(10);
            printf("-------------child die--------------\n");
    } else if (pid > 0) {
        while (1) {
            printf("I am parent, pid = %d, myson = %d\n", getpid(), pid);
            sleep(1);
        }
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
