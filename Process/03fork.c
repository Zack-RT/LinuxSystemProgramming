#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


#define ERR_EXIT(m) \
    do{ \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

int gval = 100;

int main(int argc, char **argv)
{
    signal(SIGCHLD, SIG_IGN);
    printf("before fork pid = %d\n", getpid());
    int fd = open("test.txt", O_WRONLY);
    if(fd < 0){
        ERR_EXIT("open");
    }
    // pid_t pid = fork();
    pid_t pid = vfork();
    if(pid < 0){
        ERR_EXIT("fork");
    }
    if(pid > 0){ // parent
        sleep(1);
        printf("this is parent, pid=%d, child pid = %d, gval=%d\n", getpid(), pid, gval);
        sleep(1);
    }
    else if(pid == 0){
        gval++;
        printf("this is child, pid = %d, parent pid = %d, gval=%d\n", getpid(), getppid(), gval);
    }
    else{
        fprintf(stderr, "error path.");
    }
    return 0;
}
