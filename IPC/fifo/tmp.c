/*************************************************************************
	> File Name: tmp.c
	> Author: 
	> Mail: 
	> Created Time: 2019年06月16日 星期日 16时07分07秒
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main()
{
    int ret = mkfifo("./myfifo2", 0666);
    if (ret == -1)
        perror("fifo error");
    return 0;
}
