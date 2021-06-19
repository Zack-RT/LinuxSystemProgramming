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

int main(int argc, char** argv)
{
    if(argc != 2){
        fprintf(stderr, "Usage %s <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    pid_t pid = atoi(argv[1]);
    union sigval v;
    sigqueue(pid, SIGINT, v);
    sigqueue(pid, SIGINT, v);
    sigqueue(pid, SIGINT, v);
    sigqueue(pid, SIGRTMIN, v);
    sigqueue(pid, SIGRTMIN, v);
    sigqueue(pid, SIGRTMIN, v);
    sleep(3);
    kill(pid, SIGUSR1);
    return 0;
}