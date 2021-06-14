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
    if(sig == SIGINT)
        printf("recv a sig=%d\n", sig);
    else if(sig == SIGQUIT){
        sigset_t uset;
        sigemptyset(&uset);
        sigaddset(&uset, SIGINT);
        sigprocmask(SIG_UNBLOCK, &uset, NULL);
    }
}

void print_sigset(sigset_t *pset){
    int i;
    for(i=1; i<NSIG; i++){
        if(sigismember(pset, i)){
            putchar('1');
        }
        else{
            putchar('0');
        }
    }
    printf("\n");
}

int main()
{
    sigset_t pset;
    sigset_t bset;
    sigemptyset(&bset);
    sigaddset(&bset, SIGINT);
    if(signal(SIGINT, handler) == SIG_ERR)
        ERR_EXIT("signal SIGINIT");
    if(signal(SIGQUIT, handler) == SIG_ERR)
        ERR_EXIT("signal SIGQUIT");
    // 先将SIGINT信号设为阻塞，收到SIGQUIT信号后将其取消阻塞
    sigprocmask(SIG_BLOCK, &bset, NULL);
    while (1)
    {
        sigpending(&pset);
        print_sigset(&pset);
        sleep(1);
    }
    return 0;
}