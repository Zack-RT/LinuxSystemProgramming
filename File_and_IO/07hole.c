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
    int fd = open("/tmp/test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        ERR_EXIT("open");
    }
    write(fd, "ABCD", 5);
    int ret = lseek(fd, 1024*1024, SEEK_CUR); // 一个空洞文件
    if(ret == -1){
        ERR_EXIT("lseek");
    }
    write(fd, "hello", 5);
    close(fd);
    return 0;
}