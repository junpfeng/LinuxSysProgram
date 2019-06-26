#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * 由于屏蔽了所有信号，导致无法使用ctrl+c终止当前进程。
 * 但是使用ctrl+c之后，第二位，会产生未决信号，因为ctrl+c就是产生的编号2的信号
 * 通过查表可知
 */
void printset(sigset_t *ped)
{
	int i;
	for(i = 1; i < 32; i++){
		if((sigismember(ped, i) == 1)){
			putchar('1');
		} else {
			putchar('0'); // ped是未决信号集，0表示第i个信号不在未决信号集里
		}
	}
	printf("\n");
}

int main(void)
{
	sigset_t set, ped; // 信号集
#if 0
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGKILL);
	sigaddset(&set, SIGSEGV);
#endif
	sigfillset(&set); // 将set各个位置一
	sigprocmask(SIG_BLOCK, &set, NULL);	//不获取原屏蔽字，屏蔽所有信号（甚至将-9也屏蔽了）

	while(1){
		sigpending(&ped);       //获取未决信号集
		printset(&ped);
		sleep(1);
	}

	return 0;
}
