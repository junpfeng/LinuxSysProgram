#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


/* setitimer函数的定时参数类型结构体
 * struct itimerval  {
        struct timeval{
            it_value.tv_sec;
            it_value.tv_usec;
        } it_interval;

        struct timeval {
            it_value.tv_sec;
            it_value.tv_usec;
        } it_value;

    } it, oldit;
*/

// 封装了一个自定义的定时器
unsigned int my_alarm(unsigned int sec)
{
	struct itimerval it, oldit;
    int ret;
    // 定时值
	it.it_value.tv_sec = sec;
	it.it_value.tv_usec = 0;

    // 定时间隔
	it.it_interval.tv_sec = 0; // 设置为0表示一次定时吗？？是的
	it.it_interval.tv_usec = 0; // 

    // 第一个参数设置自然定时
	ret = setitimer(ITIMER_REAL, &it, &oldit);
    if (ret == -1) {
        perror("setitimer");
        exit(1);
    }
	return oldit.it_value.tv_sec;
}

int main(void)
{
	int i;
	my_alarm(1);  //alarm(sec); 默认动作是结束进程

	for(i = 0; ; i++)
		printf("%d\n", i);

	return 0;
}
