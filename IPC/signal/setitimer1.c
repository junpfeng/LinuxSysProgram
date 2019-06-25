#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

void myfunc(int signo)
{
	printf("hello world\n");
    ////
    ////
    //
    //
 //   raise(SIGALRM); 
}

int main(void)
{
	struct itimerval it, oldit;
	signal(SIGALRM, myfunc);   //注册SIGALRM信号的捕捉处理函数。自定义信号捕捉为执行自定义函数

    // 定时时间5s
	it.it_value.tv_sec = 5;
	it.it_value.tv_usec = 0;

    // 定时间隔1s，所谓周期模式，是指首次定时按照上面的，之后周期定时按照下面的
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &it, &oldit) == -1){
		perror("setitimer error");
		return -1;
	}

	while(1);

	return 0;
}
