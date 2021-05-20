#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main(void)
{
    umask(0); // 设置umask值，计算公式newmode = mode & ~umask, 未设置默认从运行的shell中继承，一般是022
    int fd;
    fd = open("test.txt", O_WRONLY | O_CREAT, 0666);
    if(fd < 0){
        ERR_EXIT("open");
    }
    printf("open succ\n");
    return 0;
}