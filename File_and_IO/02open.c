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
    int fd;
    fd = open("test.txt", O_RDONLY);
    if(fd < 0){
        ERR_EXIT("open");
    }
    printf("open succ");
    return 0;
}