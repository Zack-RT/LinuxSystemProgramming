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
    int ret;
    printf("Entering main ...\n");
    printf("pid=%d\n", getpid());
    //int ret = execlp("./build/hello", "hello", NULL); // 将当前进程替换
    ret = fcntl(1, F_SETFD, FD_CLOEXEC); // exec时会关闭标准输出
    char * const envp[] = {"AA=11", "BB=22", NULL};
    ret = execle("./build/hello", "hello", NULL, envp);
    if(ret < 0){
        perror("exec error: ");
    }
    printf("Exiting main ... \n");
    return 0;
}
