#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// > 程序功能：将进程信息输出到文件 ps.out
// > dup2函数用于文件描述法的重定向
// > dup2(oldfd, newfd),将newfd指向oldfd
// > 例如，文件描述法1本来是指向的屏幕，但是使用dup2(3,1),1就指向了文件描述法3指向的文件了

int main(void)
{
	int fd;

    // 只写、没有就创建、将普通文件截断到0(也就是将文件清空)、设置文件权限6=4+2,即读写权限
	fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(fd < 0){
		perror("open ps.out error");
		exit(1);
	}
    // 将标准输出文件描述符指向fd
	dup2(fd, STDOUT_FILENO);

	execlp("ps", "ps", "ax", NULL);
	//close(fd);

	return 0;
}
