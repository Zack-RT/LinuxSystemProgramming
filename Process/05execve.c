#include <sys/types.h>
#include <sys/stat.h>

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

int main(int argc, char **argv)
{
    signal(SIGCHLD, SIG_IGN);
    printf("before fork pid = %d\n", getpid());
    pid_t pid = vfork();
    if(pid < 0){
        ERR_EXIT("fork");
    }
    if(pid > 0){ // parent
        sleep(1);
        printf("this is parent, pid=%d, child pid = %d\n", getpid(), pid);
    }
    else if(pid == 0){
        char *const args[] = {"ps", NULL};
        execve("/bin/ps", args, NULL);
        printf("this is child, pid = %d, parent pid = %d\n", getpid(), getppid());
    }
    else{
        fprintf(stderr, "error path.");
    }
    return 0;
}
