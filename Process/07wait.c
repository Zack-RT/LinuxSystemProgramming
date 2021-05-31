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

int main(int argc, char **argv)
{
    pid_t pid;
    pid = fork();
    if(pid < 0){
        ERR_EXIT("fork error");
    }
    if(pid == 0){
        sleep(2);
        printf("this is child, pid=%d\n", getpid());
        //exit(100);
        abort();
    }
    int status, ret;
    //ret = wait(&status);
    ret = waitpid(pid, &status, 0);
    printf("this is parent ret=%d\n", ret);
    if(WIFEXITED(status)){
        printf("child exited normal exit status=%d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)){
        printf("child exited abnormal signal number=%d\n", WTERMSIG(status));
    }
    else if(WIFSTOPPED(status)){
        printf("child stopped signal number=%d", WSTOPSIG(status));
    }
    else{
        printf("child exited abnormal.\n");
    }
    return 0;
}
