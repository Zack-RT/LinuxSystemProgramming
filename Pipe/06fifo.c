#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int main()
{
//    int fd = open("/tmp/p1", O_RDONLY);
    int fd = open("/tmp/p1", O_RDONLY | O_NONBLOCK);
    if(fd == -1){
        ERR_EXIT("open error");
    }
    printf("open success.");
    return 0;
}
