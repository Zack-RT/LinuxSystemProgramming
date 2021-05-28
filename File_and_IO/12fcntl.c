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

void set_flag(int fd, int flag)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags < 0){
        ERR_EXIT("fcntl get");
    }
    flags |= flag;
    if(fcntl(fd, F_SETFL, flags) < 0){
        ERR_EXIT("fcntl");
    }
}

void rm_flag(int fd, int flag)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if(flags < 0){
        ERR_EXIT("fcntl");
    }
    flags &= ~flag;
        if(fcntl(fd, F_SETFL, flags) < 0){
        ERR_EXIT("fcntl set");
    }
}

int main(void)
{
    char buf[1024] = {0};
    // int flags;
    // flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    // if(flags < 0){
    //     ERR_EXIT("fcntl");
    // }
    // flags |= O_NONBLOCK;
    // fcntl(STDIN_FILENO, F_SETFL, flags);
    set_flag(STDIN_FILENO, O_NONBLOCK);
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    if(ret < 0){
        ERR_EXIT("read");
    }
    printf("buf=%s\n", buf);
    return 0;
}