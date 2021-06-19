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

void handler(int);

int main()
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigaddset(&s, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &s, NULL);
    printf("pid=%d\n", getpid());

    if(sigaction(SIGINT, &act, NULL) < 0){
        ERR_EXIT("sigaction");
    }
    if(sigaction(SIGRTMIN, &act, NULL) < 0){
        ERR_EXIT("sigaction");
    }
    if(sigaction(SIGUSR1, &act, NULL) < 0){
        ERR_EXIT("sigaction");
    }
    while(1){
        pause();
    }
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d", sig);
    if(sig == SIGUSR1){
        sigset_t s;
        sigemptyset(&s);
        sigaddset(&s, SIGINT);
        sigaddset(&s, SIGRTMIN);
        sigprocmask(SIG_UNBLOCK, &s, NULL);
    }
}