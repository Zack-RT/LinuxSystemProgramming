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

void handler(int, siginfo_t *, void *);

int main()
{
    struct sigaction act;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO; // 接受数据的设置
    if(sigaction(SIGINT, &act, NULL) < 0){
        ERR_EXIT("sigaction");
    }
    while(1){
        pause();
    }
    return 0;
}

void handler(int sig, siginfo_t *info, void *ctx)
{
    printf("recv a sig=%d, data=%d\n", sig, info->si_int);
}