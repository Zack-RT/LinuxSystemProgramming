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
    sig_t ret = signal(SIGUSR1, handler); // signal函数成功返回原来的处理函数，失败返回SIG_ERR
    if (ret == SIG_ERR){
        ERR_EXIT("signal error");
    }
    pid_t pid = fork();
    if (pid < -1){
        ERR_EXIT("fork error");
    }
    if(pid == 0){
        pid = getpgrp();
        kill(-pid, SIGUSR1);
        exit(EXIT_SUCCESS);
    }
    unsigned sleeptime = 5U;
    do{
        sleeptime = sleep(sleeptime);
    }while(sleeptime > 0U);
    return 0;
}