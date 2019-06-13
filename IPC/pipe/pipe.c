#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    pid_t pid;
    char buf[1024];
    int fd[2];
    char *p = "test for pipe\n";
    
   if (pipe(fd) == -1) 
       sys_err("pipe");

   pid = fork();
   if (pid < 0) {
       sys_err("fork err");
   } else if (pid == 0) { // 子进程
        close(fd[1]); // 子进程关闭写端
        int len = read(fd[0], buf, sizeof(buf)); // 读取管道另一边的数据
        write(STDOUT_FILENO, buf, len); // 将数据写入到标准输出--屏幕
        close(fd[0]);
   } else { // 父进程
       close(fd[0]); // 子进程关闭读端
       write(fd[1], p, strlen(p)); // 向写端写入长度为strlen(p)的数据
       wait(NULL); // 等待子进程变僵尸进程
       close(fd[1]);
   }
    
    return 0;
}
