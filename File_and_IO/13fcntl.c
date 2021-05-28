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
    int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if(fd < 0){
        ERR_EXIT("open");
    }
    struct flock lock;
    memset(&lock, 0, sizeof(struct flock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; // 0表示start后所有的字节都锁定
    if(fcntl(fd, F_SETLKW, &lock) == 0){
        printf("lock success\n");
        printf("press any key to unlock\n");
        getchar();
        lock.l_type = F_UNLCK;
        if(fcntl(fd, F_SETLK, &lock) == 0){
            printf("unlock sucess\n");
        }
        else{
            ERR_EXIT("fcntl unlock");
        }
    }
    else{
        ERR_EXIT("fcntl lock");
    }
    return 0;
}