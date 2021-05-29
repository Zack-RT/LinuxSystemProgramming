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

int main(int argc, char **argv)
{
    signal(SIGCHLD, SIG_IGN);
    printf("before fork pid = %d\n", getpid());
    int fd = open("test.txt", O_WRONLY);
    if(fd < 0){
        ERR_EXIT("open");
    }
    pid_t pid = fork();
    if(pid < 0){
        ERR_EXIT("fork");
    }
    if(pid > 0){ // parent
        printf("this is parent, pid=%d, child pid = %d\n", getpid(), pid);
        int ret = write(fd, "parent", 6);
        if(ret < 0){
            ERR_EXIT("write");
        }
        sleep(1);
    }
    else if(pid == 0){
        printf("this is child, pid = %d, parent pid = %d\n", getpid(), getppid());
        int ret = write(fd, "child", 6);
        if(ret < 0){
            ERR_EXIT("write");
        }
    }
    else{
        fprintf(stderr, "error path.");
    }
    return 0;
}
