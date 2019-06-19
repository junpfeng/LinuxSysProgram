#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define N 5
int main(void)
{
    int i;
    pid_t pid, q;
    
    //-------下面两个信号，会终止当前进程------------
    // raise函数，用于给当前所在进程发送信号(参数)
//    raise(SIGSEGV); // 给自己发送了一个端错误信号,默认处理方式为终止进程
//
//    // 给自己发送一个异常终止信号
//    abort(); // 默认处理方式是终止进程

    // 循环创建5个进程
    for (i = 0; i < N; i++) {
        pid = fork();
        if (pid == 0) // 如果是子进程就退出循环，创建进程的任务交给父进程
            break;
        if (i == 2)
            q = pid;
    }
    if (i < 5) {
        while(1) {
            printf("I'm child %d, getpid = %u\n", i, getpid());
            sleep(1);
        }

    } else {
        // 父进程
        sleep(1);
        // 给指定的进程发送无条件终止信号
        kill(q, SIGKILL);
        while (1);
    }

    return 0;
}








#if 0
int main(void)
{
	int i;				//默认创建5个子进程

	for(i = 0; i < N; i++)	//出口1,父进程专用出口
		if(fork() == 0)
			break;			//出口2,子进程出口,i不自增

    if (i == 3) {
        sleep(1);
        printf("-----------child ---pid = %d, ppid = %d\n", getpid(), getppid());
        kill(getppid(), SIGKILL);

    } else if (i == N) {
        printf("I am parent, pid = %d\n", getpid());
        while(1);
    }

	return 0;
}
#endif 
