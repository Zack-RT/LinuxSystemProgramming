#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <wait.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
}

int main()
{
    sig_t ret = signal(SIGINT, handler); // signal函数成功返回原来的处理函数，失败返回SIG_ERR
    if (ret == SIG_ERR){
        ERR_EXIT("signal error");
    }
    while (1){
        pause();
        printf("pause return");
    }
    return 0;
    
}