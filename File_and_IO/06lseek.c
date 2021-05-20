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
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0){
        ERR_EXIT("open");
    }
    char buf[1024] = {0};
    int ret = read(fd, buf, 5);
    if (ret < 0){
        ERR_EXIT("read");
    }
    ret = lseek(fd, 0, SEEK_CUR);
    if (ret < 0){
        ERR_EXIT("lseek");
    }
    printf("current file pointer=%d\n", ret);
    return 0;
}