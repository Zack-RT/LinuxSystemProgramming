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
    sleep(5);
}

int main()
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT); // 如果没有这句，当信号处理函数在处理SIGINT信号时来了SIGQUIT的信号，那信号处理函数就会被中断
    // sigaction中的mask用于阻塞在信号处理函数时候来了其他的信号，处理函数结束之后就会接着处理之前未决的信号
    // 而sigpromask是完全阻塞，一直都不会抵达
    act.sa_flags = 0;
    if(sigaction(SIGINT, &act, NULL) < 0){
        ERR_EXIT("sigaction");
    }
    while(1){
        pause();
    }
    return 0;
}