#include <stdio.h>
#include <unistd.h>

// > execl 和 execlp的区别在于execl要使用可执行程序的绝对/相对地址
// > 而不能搜索PATH路径
//

int main(void)
{
    pid_t pid = fork();

    if (pid > 0) {
        execl("/home/itcast/0105_Linux/process_test/exec/output", "output", NULL);
    } else if (pid == 0) {
        printf("i'm parent pid = %d\n", getpid());
    }

    return 0;
}
