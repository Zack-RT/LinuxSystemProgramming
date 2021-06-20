#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

void handler(int sig);

int main(int argc, char** argv)
{
    if(signal(SIGALRM, handler) == SIG_ERR){
        ERR_EXIT("signal");
    }
    struct timeval tv_internal = {1, 0}; // 第一次产生信号的时间
    struct timeval tv_value = {2, 0}; // 第一次之后产生信号的间隔
    struct itimerval it = {tv_internal, tv_value};
    setitimer(ITIMER_REAL, &it, NULL);
    
    for(int i = 0; i < 10000; i++);

    struct itimerval oit;
    setitimer(ITIMER_REAL, &it, &oit);
    printf("%ld_%ld\t%ld_%ld\n", oit.it_interval.tv_sec, oit.it_interval.tv_usec, oit.it_value.tv_sec, oit.it_value.tv_usec);
    return 0;
}

void handler(int sig)
{
    printf("recv a sig=%d\n", sig);
    fflush(stdout);
}