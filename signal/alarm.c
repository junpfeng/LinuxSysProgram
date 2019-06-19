#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int i;
	alarm(1); // 1s后产生闹钟信号，默认动作是终止当前进程
	for(i = 0; ; i++)
    // io（输入输出)操作需要等待设备，因此效率较低
    // 对于ＩＯ的优化方法之一，可以将输出重定向到文件，
    // 优化的结果，就是观察1s内打印的数字的多少，越多说明优化效果越好

		printf("%d\n", i); // 优化方法 ./alarm > tmp.txt

	return 0;
}
