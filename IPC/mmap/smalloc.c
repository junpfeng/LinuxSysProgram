#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
// 由于mmao函数申请的内存映射区类似于malloc，同时也需要手动释放
// 故，自定义smalloc和sfree来管理共享内存。
void *smalloc(size_t size)
{
	void *p;
// NULL是指由内核自定义映射区的首地址，size是指映射区的大小（字节）,映射区的权限，
    // 标志位，-1 表示匿名映射区，0 地址偏移0字节
	p = mmap(NULL, size, PROT_READ|PROT_WRITE, 
			MAP_SHARED|MAP_ANON, -1, 0);
	if (p == MAP_FAILED) {		
		p = NULL;
	}

	return p;
}

void sfree(void *ptr, size_t size)
{
    // 释放从ptr向后的size大小的内存映射区
	munmap(ptr, size);
}

int main(void)
{
	int *p;
	pid_t pid;
	
	p = smalloc(4);

	pid = fork();				//创建子进程
	if (pid == 0) {
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	sfree(p, 4);

	return 0;
}
