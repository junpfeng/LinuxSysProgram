#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// > execlp 函数第一个参数可以在PATH环境变量中搜索，
// > 这是和execl唯一的区别

int main(int argc, char *argv[])
{
    printf("========================\n");

    char *argvv[] = {"ls", "-l", "-F", "R", "-a", NULL};
    

    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", "-F", "-a", NULL);
        execv("/bin/ls", argvv);
        perror("execlp");
        exit(1);

    } else if (pid > 0) {
        sleep(1);
        printf("parent\n");
    }


    return 0;
}
