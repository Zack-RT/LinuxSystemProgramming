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

__sighandler_t my_signal(int sig, __sighandler_t handler)
{
    struct sigaction act, oldact;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGINT, &act, &oldact) < 0)
        return SIG_ERR;
    return oldact.sa_handler;
}

int main()
{
    // struct sigaction act;
    // act.sa_handler = handler;
    // sigemptyset(&act.sa_mask);
    // act.sa_flags = 0;
    // if(sigaction(SIGINT, &act, NULL) < 0){
    //     ERR_EXIT("sigaction error");
    // }
    my_signal(SIGINT, handler);
    while(1){
        pause();
    }
    return 0;
}